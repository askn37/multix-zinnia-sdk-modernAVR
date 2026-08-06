/**
 * @file boot_dx.c
 * @author askn (K.Sato) multix.jp
 * @brief Arduino-compatible serial bootloader for AVR_Ex/Lx
 * @version 3.73
 * @date 2026-08-01
 * @copyright Copyright (c) 2026 askn37 at github.com
 */
// MIT License : https://askn37.github.io/LICENSE.html

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
considered.

Previously, the source code was a clone of "Optiboot", but this is no longer
the case. They, as a rule, only support older generation devices. For these
reasons, the source code published here has been rewritten.

Licensing and redistribution are subject to the MIT License.

+++ AVR Sx Family Special +++

This bootloader is highly experimental. In other words,
while it is technically feasible to implement, it is not practical.

This variant rewrites non-volatile memory with the AVR Sx family's specific
memory protection features disabled (except where protection is enforced by
FUSE bits).　It has been tuned to keep the code size within 1 KiB, while
accounting for the additional logic required to implement this functionality.
However, as there is sufficient free space, it does not employ the aggressive
optimizations seen in `boot_dx`.

The NVMCTRL version is `6`.　It returns `6` for HW_VER.

Rewriting the Flash "code" area using SPM-based "word" access is more
cumbersome than using NVMCTRL::V2. Therefore, we adopt a more direct
approach here using FLMAP and ST.

***/

#include <avr/io.h>
#include "boot_sx.h"

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

void nvm_cmd (uint8_t _nvm_cmd);  /* prototype */

/***
  This section provides an auxiliary capability
  for self-modifying the flash area.

  $0000 : Started Bootloader (POR)       $C02F
  $0002 : nvm_stz function : magicnumber $95089361
  $0006 : nvm_ldz function : magicnumber $95089181
  $000A : nvm_spm function : magicnumber $950895F8
  $000E : nvm_cmd function : magicnumber $BF94E99D
  $0200 : appcode
***/

__attribute__((used))
__attribute__((naked))
__attribute__((noinline))
__attribute__((section (".vectors")))
void vector_table (void) {
  __asm__ __volatile__ (
  R"#ASM#(
    RJMP  bootload  ; $0000
    ST    Z+, R22   ; $0002 nvm_stz
    RET
    LD    R24, Z+   ; $0006 nvm_ldz
    RET
    SPM   Z+        ; $000A nvm_spm
    RET
  )#ASM#"
  );
  /* next is watchdog nvm_cmd */
}

/* The SPM snippet consists of two functions.
   One is to simply execute an SPM instruction.
   The next step is to write CMD to her NVMCTRL and check the STATUS. */

__attribute__((used))
__attribute__((noinline))
__attribute__((section (".vectors")))
void nvm_cmd (uint8_t _nvm_cmd) {
  /* This function occupies 18 bytes of space. */
  _PROTECTED_WRITE_SPM(NVMCTRL_CTRLA, _nvm_cmd);
  while (NVMCTRL_STATUS & 3);
}

__attribute__((used))
__attribute__((naked))
__attribute__((section (".vectors")))
void vector_TCA0_CMP_before (void) {
  /* Fill with zeros up to the address of TCA0_CMP0_vect. */
  #define __QUOTE__(S) #S
  #define __QUOTE(S) __QUOTE__(S)
  __asm__ __volatile__ (".ORG " __QUOTE(TCA0_CMP0_vect_num * _VECTOR_SIZE));
}

/* Since the WDTCTRL in the AVR-Sx series operates with a clock 32 times
   faster than that of previous generations, the effective processing period
   is limited to a maximum of 250 ms. As this does not provide sufficient
   time for the bootloader to wait for commands from the host,
   the TCA0_CMP0 interrupt is used instead. */

   __attribute__((used))
__attribute__((naked))
__attribute__((section (".vectors")))
void watchdog (void) {
  _PROTECTED_WRITE(CPUINT_CTRLA, 0);
  _PROTECTED_WRITE(WDT_CTRLA, WDT_PERIOD_8CLK_gc);

  /* The interrupt-disabled state does not affect the WDT reset. */
  for (;;);
}

__attribute__((noinline))
void putch (uint8_t ch) {
  /* Put-Character will not send the character unless the buffer is empty. */
  loop_until_bit_is_set(UART_BASE.STATUS, USART_DREIF_bp);
  UART_BASE.TXDATAL = ch;
  #ifdef RS485_SINGLE
  /* drop loopback */
  pullch();
  #endif
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
  if ((er & USART_FERR_bm) == 0) TCA0_SINGLE_CNT = 0;
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

#if defined(LED_BLINK) && defined(LED_PORT) && (LED_BLINK >= 2)
inline static
void blink (void) {
  /* Makes the LED blink at a different rate than normal.
     This code uses about 10 bytes of extra space. */
  uint8_t count = LED_BLINK;
  do {
    LED_PORT.IN |= _BV(LED_PIN);
    /* delay assuming 4Mhz */
    uint16_t delay = 4000000U / 150;
    do {
      if (bit_is_set(UART_BASE.STATUS, USART_RXCIF_bp)) return;
    } while (--delay);
  }
  while (--count);
}
#endif

// MARK: bootload (main) function

__attribute__((used))
__attribute__((naked))
__attribute__((noinline))
__attribute__((noreturn))
void bootload (void) {
  /* It is preferable that these variables be allocated directly to registers. */
  addr16_t address;
  addr16_t length;
  uint8_t ch;

  /* This is the first code that is executed.
     According to modernAVR specifications,
     interrupts are disabled and SP points to RAMEND. */

  /* Known-zero required by avr-libc. */
  __asm__ __volatile__ ( "CLR __zero_reg__" );

  /* Get the reset reason. The value is also copied to GPR0. */
  ch = RSTCTRL_RSTFR; /* get reset cause */
  RSTCTRL_RSTFR = ch; /* clear flags */
  GPR_GPR0 = ch;      /* Backup so user code can be referenced */

  /* If register is zero, perform software reset */
  if (ch == 0) _PROTECTED_WRITE(RSTCTRL_SWRR, 1);

  #ifdef PORSTRAP
  /* WDT reset executes user code */
  if (bit_is_set(GPR_GPR0, RSTCTRL_WDRF_bp))
  #else
  /* WDT and hardware restart causes user code to execute */
  if (ch & (RSTCTRL_WDRF_bm | RSTCTRL_BORF_bm | RSTCTRL_PORF_bm))
  #endif
  {
    __asm__ __volatile__ ( "RJMP appcode" );
  }

  /* To facilitate debugging, all ERRCTRL functions are disabled. */
  /* This section must be removed before final productization.    */
  if (ERRCTRL_ESF) ERRCTRL_ESF = ~0;
  _PROTECTED_WRITE(ERRCTRL_CTRLA, ERRCTRL_STATE_CONFIG_gc);
  uint16_t _reg = (uint16_t)&ERRCTRL_ESCVREGFAIL;
  do {
    _SFR_MEM8(_reg) = ERRCTRL_ERRLVL_NOTIFICATION_gc;
    _reg++;
  } while (_reg <= (uint16_t)&ERRCTRL_ESCEVSYS1);
  _PROTECTED_WRITE(ERRCTRL_CTRLA, ERRCTRL_STATE_NORMAL_gc);

  /* Move the interrupt vector to the beginning of the boot area. */
  _PROTECTED_WRITE(CPUINT_CTRLA, CPUINT_IVSEL_bm);

  /* Relaxation of ECC checks for uninitialized flash regions */
  _PROTECTED_WRITE(NVMCTRL_CTRLC, NVMCTRL_ECCALL1_DISALL_gc);

  /* Clear FLMAP bits field */
  _PROTECTED_WRITE(NVMCTRL_CTRLB, 0);

#ifdef FREQSEL
  _PROTECTED_WRITE(CLKCTRL_MCLKCTRLA, 0);         // CLKCTRL_CLKSEL_OSCHF_gc
  _PROTECTED_WRITE(CLKCTRL_OSCHFCTRLA, FREQSEL);  // CLKCTRL_FREQSEL_4M_gc
#endif

  /* Set LED pin as output */
#ifdef LED_PORT
  LED_PORT.DIR |= _BV(LED_PIN);
#endif

#ifdef UART_PMUX_VAL
  /* PORTMUX setting.
     Should be omitted if no alternate is set. */
  UART_PMUX_REG = UART_PMUX_VAL;
#endif

#if defined(PULLUP_RX) && !defined(RS485_SINGLE) && !defined(USART)
  /* RX pin pullup (RX is TX next GPIO).
     Normally, the TxD side is push-pull, so it is not required. */
  UART_RXCFG = PORT_PULLUPEN_bm;
#endif

/* Communication Mode Setup */
#if defined(RS485) || defined(RS485_SINGLE)
  /*** For RS485 client mode ***/
  /* This is intended solely for synchronous.
     It can also be configured for open-drain single-wire driving. */

  #if defined(RS485_INVERT)
  UART_XDIRCFG = PORT_INVEN_bm;
  #endif
  UART_TXPORT.DIR |= UART_XDIRPIN;

  UART_BASE.CTRLC = USART_CHSIZE_8BIT_gc | USART_CMODE_SYNCHRONOUS_gc;

  #if defined(RS485_SINGLE)
  UART_TXCFG = PORT_PULLUPEN_bm;
  UART_BASE.CTRLA = USART_RS485_ENABLE_gc | _BV(1) | USART_LBME_bm;
  UART_BASE.CTRLB = USART_RXEN_bm | USART_TXEN_bm | USART_ODME_bm;
  #else
  UART_BASE.CTRLA = USART_RS485_ENABLE_gc | _BV(1);
  UART_BASE.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
  #endif

#elif defined(USART)
  /*** For synchronous client USART ***/
  #ifdef USART_INVERT
  UART_XCKCFG = PORT_INVEN_bm;
  #endif

  UART_BASE.CTRLC = USART_CHSIZE_8BIT_gc | USART_CMODE_SYNCHRONOUS_gc;
  UART_BASE.CTRLB = USART_RXEN_bm | USART_TXEN_bm;

#else /* UART */
  /* For standard asynchronous UART */

  /* BAUDH is zero, so if you don't need it, just write BAUDL */
  #if (BAUD_SETTING_16 < 256)
  UART_BASE.BAUDL = BAUD_SETTING;
  #else
  UART_BASE.BAUD = BAUD_SETTING;
  #endif

  /* This is the same as the default value for CTRLC, so it can be omitted. */
  // UART_BASE.CTRLC = USART_CHSIZE_8BIT_gc | USART_CMODE_ASYNCHRONOUS_gc;
  UART_BASE.CTRLB = USART_RXEN_bm | USART_TXEN_bm;

#endif  /* Communication Mode Setup */

/* At this stage, the UART only acts as a receiver. */
/* TxD pin is not configured as an output yet and remains Hi-Z. */

#if defined(LED_BLINK) && defined(LED_PORT) && (LED_BLINK >= 2)
  /* LED flashing time is not included in WDT limit. */
  blink();
#elif defined(LED_PORT)
  /* Set noinit SRAM as a flag and make the LED blink
     alternately every time the WDT restarts. */
  if (++_SFR_MEM8(RAMEND - 767) & 1) LED_PORT.IN |= _BV(LED_PIN);
#endif

  /* Start watch-dog-timer monitoring */
  /* Since the AVR-Sx WDT cannot provide a sufficiently
     long duration, the TCA0_CMP interrupt is used instead. */

  TCA0_SINGLE_INTCTRL = TCA_SINGLE_CMP0_bm;
  TCA0_SINGLE_CMP0 = WDTPERIOD;
  TCA0_SINGLE_CTRLA = TCA_SINGLE_ENABLE_bm | TCA_SPLIT_CLKSEL_DIV1024_gc;

  __builtin_avr_sei();

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
    else if (ch == STK_UNIVERSAL) {
      /***
        This code path is executed only when the Flash code area is 128 KiB.
        Since the AVR Sx is planned to have a maximum of 64 KiB,
        this section will likely never be used.
      ***/
      if (pullch() == PAR_LOAD_EXT_ADDR) {
        /* get address (24bit-wide, 3bytes) */
        pullch();         /* drop ADDR1 */
        ch = 0;
        if (pullch()) {   /* get the ADDR2 and put it in FLMAP high-bit */
          ch = NVMCTRL_FLMAP_1_bm;
        }
        nvm_cmd(NVMCTRL_CMD_NOOP_gc);
        _PROTECTED_WRITE(NVMCTRL_CTRLB, ch);
        drop_packet(1);   /* drop ADDR3 */
      }
      else {
        drop_packet(3);   /* drop 3bytes */
      }
      putch(0x00);        /* STK_UNIVERSAL response '0' */
    }
    else if (ch == STK_PROG_PAGE) {
      /* Flash or EEPROM */
      /* Write memory block mode, length is big endian. */
      length.bytes[1] = pullch();
      length.bytes[0] = pullch();
      ch = pullch();
      uint16_t len = length.word;

      /* Any chip has at least 1KiB of SRAM,
         so buffers are reserved in fixed locations. */
      uint8_t* _buff = RAMEND - 767;
      addr16_t buff = {_buff};
      do *buff.bptr++ = pullch(); while (--len);
      buff.bptr = _buff;

      if (ch == 'E') {
        /* Supports EEPROM writing. */
        /* You can pass the file with
          'avrdude -U eeprom:w:Sketch.eep:a' option. */
        address.word += MAPPED_EEPROM_START;
        nvm_cmd(NVMCTRL_CMD_EEERWR_gc);
      }
      else {
        if (ch == 'F') {
          /* Supports APPCODE writing. */
          ch = NVMCTRL_CTRLB;
          if (bit_is_set(address.bytes[1], 7)) {
            ch |= NVMCTRL_FLMAP_0_bm;
          }
          else {
            ch &= ~NVMCTRL_FLMAP_0_bm;
          }
          nvm_cmd(NVMCTRL_CMD_NOOP_gc);
          _PROTECTED_WRITE(NVMCTRL_CTRLB, ch);
          address.word |= MAPPED_PROGMEM_START;
        }
        else {
          /* Supports BOOTROW/USERROW writing. */
          /* You can pass the file with
            'avrdude -U userrow:w:data.hex:a' option. */
          /* (This cannot be done with standard AVRDUDE.) */
        }
        nvm_cmd(NVMCTRL_CMD_FLPER_gc);
        *(address.bptr) = 0;

        /* This line was unnecessary in NVMCTRL::V2.
           In V6, the time required for memory operations
           involving ECC is longer than before. */
        nvm_cmd(NVMCTRL_CMD_NOOP_gc);

        nvm_cmd(NVMCTRL_CMD_FLWR_gc);
      }
      __asm__ __volatile__ (
        R"#ASM#(
        1:  LD    R0, X+  ; R0 <- X+
            ST    Z+, R0  ;
            SBIW  %0, 1   ; Decrement
            BRNE  1b      ; Branch if Not Equal
        )#ASM#"
        :
        : "w" (length.word)
        , "z" (address.bptr)  /* Z <- to eeprom.ptr */
        , "x" (buff.bptr)     /* X <- from sram.ptr */
      );
      nvm_cmd(NVMCTRL_CMD_NOOP_gc);
      end_of_packet();
    }
    else if (ch == STK_READ_PAGE) {
      /* Read memory block mode, length is big endian. */
      length.bytes[1] = pullch();
      length.bytes[0] = pullch();
      ch = pullch();
      end_of_packet();
      nvm_cmd(NVMCTRL_CMD_NOOP_gc); /* Stalling for memory access time */

      /* the entire flash does not fit in the same address space
         so we call that helper function. */
      if (ch == 'F') {
        /* Read the code space using ELPM. */
        __asm__ __volatile__ (
          R"#ASM#(            ; Z <- address.bptr
          1:  ELPM  R24, Z+   ; R24 <- (RAMPZ:Z)
              RCALL putch     ; putch(R24)
              SBIW  %0, 1     ; Decrement R29:R28
              BRNE  1b        ; Branch if Not Equal
          )#ASM#"
          : "=p" (length.word)
          : "0" (length.word)
          , "z" (address.bptr)
          : "r24", "r25"
        );
      }
      else {
        /* It's not an absolute address, so add the EEPROM offset. */
        /* (Standard AVRDUDE cannot read BOOTROW/USERROW.) */
        if (ch == 'E') address.word += MAPPED_EEPROM_START;
        do putch(*(address.bptr++)); while (--length.word);
      }
    }
    else if (ch == STK_READ_SIGN) {
      /* READ SIGN - return actual device signature from SIGROW
         this enables the same binary to be ued on multiple chips. */
      end_of_packet();

      /* SIGROW_DEVICEID0 : This value is always fixed. */
      putch(SIGNATURE_0);

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

__attribute__((used))
__attribute__((naked))
void usage (void) {
  /* Since there is spare space in the code area,
     an identification string has been embedded. */
  __asm__ __volatile__ (
    ".DS.B 10\n"
    ".ASCII \"bootloader for AVR Sx Famiry;\"\n"
    ".DS.B 3\n"
    ".ASCII \".appcode is .text=0x400\"\n"
    ".DS.B 5\n"
  );
}

/*** This is a dummy application. It is not included in the output file. ***/

__attribute__((naked))
__attribute__((noreturn))
__attribute__((section( ".appcode")))
void appcode (void) {
  __asm__ __volatile__ ( "RJMP vector_table" );
}

/* end of code */
