/**
 * @file boot_dx.c
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 3.7
 * @date 2023-11-30
 *
 * @copyright Copyright (c) 2023 askn37 at github.com
 *
 */

/***

+++ OVERVIEW +++

This bootstrap loader firmware for moderAVR is based on the ATMEL STK500
version 1 protocol and is fully compatible with Arduino bootloaders.

When the firmware boots, the RESET information flag is checked and, in the
case of a WDT or software reset, the application code (starting at 0x200)
starts executing immediately. Otherwise, if a valid STK500 version 1
command is received within the timeout period, the UART will open and he
will start NVM operations.

Builds are possible with AVR-GCC and AVR-LIBC, but other compilers are not
considered. Binary code fits within 512 bytes.

Previously, the source code was a clone of "Optiboot", but this is no longer
the case. They, as a rule, only support older generation devices. For these
reasons, the source code published here has been rewritten.

Licensing and redistribution are subject to the MIT License.

***/

#include <avr/io.h>
#include "boot_dx.h"

#ifndef UART_BASE
  #warning UART is ignored for this chip (use UART=<TxD-PortPin> instead)
#endif

#ifndef USART
/*** For an asynchronous UART, perform the following settings. ***/

/***
  All AVR_Dx Series products are reset to run on a 4 MHz internal oscillator.
  Calculating the division ratio is therefore simple.
***/
  #define BAUD_SETTING ((F_CPU * 64) / (16L * BAUD_RATE))
  #if (BAUD_SETTING < 64)
    /* max BAUD_RATE 250000 bps (4 Mhz) */
    #error Unachievable baud rate (too fast) BAUD_RATE
    #include "BUILD_STOP"
  #elif (BAUD_SETTING > 65535)
    /* min BAUD_RATE 245 bps (4 Mhz) */
    #error Unachievable baud rate (too slow) BAUD_RATE
    #include "BUILD_STOP"
  #endif
#endif /* not USART */

/***
  This section provides an auxiliary capability
  for self-modifying the flash area.

  $0000 : Started Bootloader (POR)
  $0002 : nvm_spm function : magicnumber $95F8
  $0004 : ret              :             $9508
  $0006 : nvm_cmd function : magicnumber $E99D, $BF94
  $0200 : appcode
***/

__attribute__((naked))
__attribute__((noreturn))
__attribute__((section (".init0")))
void vector_table (void) {
  __asm__ __volatile__ (
  R"#ASM#(
    RJMP  main
    SPM   Z+
    RET
  )#ASM#"
  );
  /* next is nvm_cmd */
}

/* The SPM snippet consists of two functions.
   One is to simply execute an SPM instruction.
   The next step is to write CMD to her NVMCTRL and check the STATUS. */

__attribute__((used))
__attribute__((noinline))
__attribute__((section (".init1")))
void nvm_cmd (uint8_t _nvm_cmd) {
  /* This function occupies 18 bytes of space. */
  _PROTECTED_WRITE_SPM(NVMCTRL_CTRLA, _nvm_cmd);
  while (NVMCTRL.STATUS & 3);
}

__attribute__((noinline))
void putch (uint8_t ch) {
  /* Put-Character will not send the character unless the buffer is empty. */
  loop_until_bit_is_set(UART_BASE.STATUS, USART_DREIF_bp);
  UART_BASE.TXDATAL = ch;
}

__attribute__((noinline))
uint8_t pullch (void) {
  /* Pull-Character blocks if buffer is empty.
     If nothing is received, WDT will eventually work. */
  uint8_t ch, er;
  loop_until_bit_is_set(UART_BASE.STATUS, USART_RXCIF_bp);
  er = UART_BASE.RXDATAH;
  ch = UART_BASE.RXDATAL;
  /* If there are no frame errors, pet the dog. */
  if ((er & USART_FERR_bm) == 0) wdt_reset();
#ifdef LED_PORT
  LED_PORT.IN |= _BV(LED_PIN);
#endif
  return ch;
}

__attribute__((noinline))
void end_of_packet (void) {
  if (pullch() != CRC_EOP) {
    /* If the End of Packet marks do not match, the system will be reset. */
    __asm__ __volatile__ ( "RJMP vector_table" );
  }
  putch(STK_INSYNC);
}

__attribute__((noinline))
void drop_packet (uint8_t count) {
  /* Closes the received packet by discarding
     the indicated number of characters. */
  do pullch(); while (--count);
  end_of_packet();
}

#if defined(LED_BLINK) && defined(LED_PORT)
inline static
void blink (void) {
  /* Makes the LED blink at a different rate than normal.
     This code uses about 10 bytes of extra space. */
  uint8_t count = LED_BLINK;
  do {
    LED_PORT.IN |= _BV(LED_PIN);
    /* delay assuming 4Mhz */
    uint16_t delay = 4000000U / 200;
    do {
      if (bit_is_set(UART_BASE.STATUS, USART_RXCIF_bp)) return;
    } while (--delay);
  }
  while (--count);
}
#endif

/* main program starts here */
__attribute__((OS_main))
int main (void) {
  /* It is preferable that these variables be allocated directly to registers. */
  register addr16_t address;
  register addr16_t length;
  register uint8_t ch;

  /* This is the first code that is executed.
     According to modernAVR specifications,
     interrupts are disabled and SP points to RAMEND. */

  /* Known-zero required by avr-libc. */
  __asm__ __volatile__ ( "CLR __zero_reg__" );

  /* Get the reset reason. The value is also copied to GPR0. */
  ch = RSTCTRL_RSTFR; /* get reset cause */
  RSTCTRL_RSTFR = ch; /* clear flags */
  GPR_GPR0 = ch;      /* Backup so user code can be referenced */

  /* If the register is zero, consider it a user call and perform a software
     reset. This is just in case, so it consumes extra code space. */
  if (ch == 0) _PROTECTED_WRITE(RSTCTRL_SWRR, 1);

  /* WDT or soft reset executes user code */
  if (bit_is_set(GPR_GPR0, RSTCTRL_WDRF_bp) || ch < 4) {
    __asm__ __volatile__ ( "RJMP appcode" );
  }

  /* Set LED pin as output */
#ifdef LED_PORT
  LED_PORT.DIR |= _BV(LED_PIN);
#endif

#ifdef FREQSEL
  _PROTECTED_WRITE(CLKCTRL_MCLKCTRLA, 0);         // CLKCTRL_CLKSEL_OSCHF_gc
  _PROTECTED_WRITE(CLKCTRL_OSCHFCTRLA, FREQSEL);  // CLKCTRL_FREQSEL_4M_gc
#endif

#ifdef UART_PMUX_VAL
  /* PORTMUX setting.
     Should be omitted if no alternate is set. */
  UART_PMUX_REG = UART_PMUX_VAL;
#endif

#ifndef USART
/*** For an asynchronous UART, perform the following settings. ***/

/* BAUDH is zero, so if you don't need it, just write BAUDL */
#if (BAUD_SETTING < 256)
  UART_BASE.BAUDL = BAUD_SETTING;
#else
  UART_BASE.BAUD = BAUD_SETTING;
#endif

#endif /* not USART */

#ifdef RS485
  /*** For RS485 mode ***/
  #ifdef UART_XDIRPIN
    #ifdef RS485_INVERT
  UART_XDIRCFG = PORT_INVEN_bm;
    #endif
    #ifdef RS485_SINGLE
  UART_BASE.CTRLA = USART_RS485_ENABLE_gc|_BV(1)|USART_LBME_bm;
    #else
  UART_BASE.CTRLA = USART_RS485_ENABLE_gc|_BV(1);
    #endif
  #else
    #error RS485 XDIR pin not USART exists
    #include "BUILD_STOP"
  #endif
#endif

#ifdef USART
  /*** For synchronous USART ***/
  #ifdef UART_XCKCFG
    #ifdef USART_INVERT
  UART_XCKCFG = PORT_INVEN_bm;
    #endif
  #else
    #error USART XCK pin not USART exists
    #include "BUILD_STOP"
  #endif
#endif

#if defined(RS485) && defined(UART_XDIRPIN)
  UART_TXPORT.DIR |= UART_XDIRPIN;
#elif defined(RS485) && defined(RS485_SINGLE)
  UART_TXPORT.DIR |= UART_TXPIN;
  UART_TXCFG = PORT_PULLUPEN_bm;
#elif defined(PULLUP_RX)
  /* RX pin pullup (RX is TX next GPIO).
     Normally, the TxD side is push-pull, so it is not required. */
  UART_RXCFG = PORT_PULLUPEN_bm;
#endif

#ifdef USART
  /* For synchronous USART */
  UART_BASE.CTRLC = USART_CHSIZE_8BIT_gc|USART_CMODE_SYNCHRONOUS_gc;
#else
  /* For asynchronous UART */
  UART_BASE.CTRLC = USART_CHSIZE_8BIT_gc;
#endif

  /* not interrupt, polling read-write UART started */
  #if defined(RS485) && defined(RS485_SINGLE)
  UART_BASE.CTRLB = USART_RXEN_bm|USART_TXEN_bm|USART_ODME_bm;
  #else
  UART_BASE.CTRLB = USART_RXEN_bm|USART_TXEN_bm;
  #endif

  /* At this stage, the UART only acts as a receiver.
     TxD pin is not configured as an output yet and remains Hi-Z */

#if defined(LED_BLINK) && defined(LED_PORT)
  /* LED flashing time is not included in WDT limit. */
  blink();
#elif defined(LED_PORT)
  /* Set noinit SRAM as a flag and make the LED blink
     alternately every time the WDT restarts. */
  if (++_SFR_MEM8(RAMEND - 767) & 1) LED_PORT.IN |= _BV(LED_PIN);
#endif

  /* This probably isn't necessary since WDT isn't started yet. */
  // loop_until_bit_is_clear(WDT_STATUS, WDT_SYNCBUSY_bp);

  /* Start WDT monitoring */
  _PROTECTED_WRITE(WDT_CTRLA, WDTPERIOD);

  /*** Forever loop: exits by causing WDT reset ***/
  for (;;) {
    /* get STK Command */
    ch = pullch();
    if (ch == STK_GET_PARAMETER) {
      ch = pullch();
      end_of_packet();
      if (ch == PAR_SW_MINOR)
        ch = BOOT_MINVER;
      else if (ch == PAR_SW_MAJOR)
        ch = BOOT_MAJVER;
      else
        ch = BOOT_HW_VER;
      putch(ch);
    }
    else if (ch == STK_SET_DEVICE) {
      /* SET_DEVICE is ignored */
      /* drop 20bytes */
      drop_packet(20);
    }
    else if (ch == STK_SET_DEVICE_EXT) {
      /* SET_DEVICE EXT is ignored */
      /* drop 5bytes */
      drop_packet(5);
    }
    else if (ch == STK_LOAD_ADDRESS) {
      /* LOAD_ADDRESS little endian */
      address.bytes[0] = pullch();
      address.bytes[1] = pullch();
      /* byte addressed mode */
      end_of_packet();
    }
  #ifdef RAMPZ
    /***
      RAMPZ - Extended Z Pointer Register
      This register is only present on AVRs with FLASH greater than 128KiB.
      For lower-level varieties, even if you write to it, it will always
      be treated as zero and will not function.
    ***/
    else if (ch == STK_UNIVERSAL) {
    #if ENABLE_MORE_ACCURATELY
      if (pullch() == PAR_LOAD_EXT_ADDR) {
        /* get address (24bit-wide, 3bytes) */
        pullch();         /* drop ADDR1 */
        RAMPZ = pullch(); /* get the ADDR2 and put it in RAMPZ */
        drop_packet(1);   /* drop ADDR3 */
      }
      else {
        drop_packet(3);   /* drop 3bytes */
      }
    #else
      /* STK_UNIVERSAL should not be used except for PAR_LOAD_EXT_ADDR */
      pullch();           /* drop PAR_LOAD_EXT_ADDR */
      pullch();           /* drop ADDR1 */
      RAMPZ = pullch();   /* get the ADDR2 and put it in RAMPZ */
      /* This value should indicate the 17th bit of the direct address */
      drop_packet(1);     /* drop ADDR3 */
    #endif
      putch(0x00);        /* STK_UNIVERSAL response '0' */
    }
  #endif
    else if (ch == STK_PROG_PAGE) {
      /* Flash or EEPROM */
      /* Write memory block mode, length is big endian. */
      length.bytes[1] = pullch();
      length.bytes[0] = pullch();
      ch = pullch();
      register uint16_t len = length.word;

      /* Any chip has at least 1KiB of SRAM,
         so buffers are reserved in fixed locations. */
      uint8_t* _buff = RAMEND - 767;
      addr16_t buff = {_buff};
      do *buff.bptr++ = pullch(); while (--len);
      buff.bptr = _buff;

      if (ch == 'E') {
        /* Supports EEPROM writing. */
        /* You can pass the file with
           'avrdude -U eeprom:w:Sketch.eep:i' option. */
        address.word += MAPPED_EEPROM_START;
        ch = length.bytes[0];
        __asm__ __volatile__ (
          R"#ASM#(
              LDI   R24, %[flp] ; R24 <- NVMCTRL_CMD_EEERWR
              RCALL nvm_cmd     ; Change NVMCTRL command
          1:  LD    R0, X+      ; R0 <- X+
              ST    Z+, R0      ;
              DEC   %[len]      ; Decrement
              BRNE  1b          ; Branch if Not Equal
          )#ASM#"
          : [len] "=d" ((uint8_t)ch)    /* byte length counter */
          :       "0"  ((uint8_t)ch),
                  "z"  (address.bptr),  /* Z <- to eeprom.ptr   */
            [ptr] "x"  (buff.bptr),     /* X <- from sram.ptr  */
            [flp] "I"  ((uint8_t)NVMCTRL_CMD_EEERWR_gc)
          : "r24", "r25"
        );
      }
      else /* if (ch == 'F') */ {
        /***
          Please set the RAMPZ IO register (0x003B) correctly before calling.
          The counter is in “WORD” units.
          Out of range is initialized to 0xFF and rewritten for each page block.
          Do not add MAPPED_PROGMEM_START as you are using absolute addresses.
        ***/
        ch = length.word >> 1;
        __asm__ __volatile__ (
          R"#ASM#(
              LDI   R24, %[flp]   ; R24 <- NVMCTRL_CMD_FLPER
              RCALL nvm_cmd       ; Change NVMCTRL command
              SPM                 ; DS(RAMPZ:Z) <- 0xFFFF dummy write
              LDI   R24, %[flw]   ; R24 <- NVMCTRL_CMD_FLWR
              RCALL nvm_cmd       ; Change NVMCTRL command
          1:  LD    R0, X+        ; R0 <- X+
              LD    R1, X+        ; R1 <- X+
              SPM   Z+            ; DS(RAMPZ:Z+) <- R1:R0
              DEC   %[len]        ; Decrement
              BRNE  1b            ; Branch if Not Equal
              CLR   __zero_reg__  ; R1 <- 0
          )#ASM#"
          : [len] "=d" ((uint8_t)ch)    /* word length counter */
          :       "0"  ((uint8_t)ch),
                  "z"  (address.bptr),  /* Z <- to flash.ptr   */
            [ptr] "x"  (buff.bptr),     /* X <- from sram.ptr  */
            [flp] "I"  ((uint8_t)NVMCTRL_CMD_FLPER_gc),
            [flw] "I"  ((uint8_t)NVMCTRL_CMD_FLWR_gc)
          : "r24", "r25"
        );
      }
      end_of_packet();
    }
    else if (ch == STK_READ_PAGE) {
      /* Read memory block mode, length is big endian.  */
      length.bytes[1] = pullch();
      length.bytes[0] = pullch();
      ch = pullch();
      end_of_packet();

      /* the entire flash does not fit in the same address space
         so we call that helper function. */
      if (ch == 'F') {
        /* Read the code space using ELPM. */
        __asm__ __volatile__ (
          R"#ASM#(                ; Z <- address.bptr
          1:  ELPM  R24, Z+       ; R24 <- (RAMPZ:Z)
              RCALL putch         ; putch(R24)
              SUBI  %A[len], 0x01 ; Decrement R16:R17
              SBC   %B[len], R1   ;
              BRNE  1b            ; Branch if Not Equal
          )#ASM#"
          : [len] "=d" (length.word)
          :        "z" (address.bptr),
                   "0" (length.word)
          : "r24", "r25"
        );
      }
      else /* if (ch == 'E') */ {
        /* It's not an absolute address, so add the EEPROM offset. */
        address.word += MAPPED_EEPROM_START;
        do putch(*(address.bptr++)); while (--length.word);
      }
    }
    else if (ch == STK_READ_SIGN) {
      /* READ SIGN - return actual device signature from SIGROW
         this enables the same binary to be ued on multiple chips. */
      end_of_packet();

      /* SIGROW_DEVICEID0 : This value is always fixed. */
      putch(0x1E);

      /* This value indicates the flash size and indicates
         whether or not there is a RAMPZ register. */
      putch(SIGROW_DEVICEID1);

      /* Inconsistent values to avoid duplicate SIGROW */
      putch(SIGROW_DEVICEID2);
    }
    else {
      #ifndef RS485_SINGLE
      /* The TxD pin is set to output only after passing here. */
      /* Normally STK_GET_SYNC executes this for the first time. */
      UART_TXPORT.DIR |= UART_TXPIN;
      #endif
      end_of_packet();
    }
    putch(STK_OK);
  } /* Forever loop */
}   /* End of main */

/*** This is a dummy application. It is not included in the output file. ***/

__attribute__((naked))
__attribute__((noreturn))
__attribute__((section( ".appcode")))
void appcode (void) {
  __asm__ __volatile__ ( "RJMP vector_table" );
}

/* end of code */
