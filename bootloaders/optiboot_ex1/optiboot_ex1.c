/**********************************************************/
/* Optiboot bootloader for AVR EA series                  */
/*                                                        */
/* Experimental Customization                             */
/*                                                        */
/*   OPTIBOOT_CUSTOMVER = 0x20 (+ base version 9 == 41)   */
/*                                                        */
/* Copyright 2019-2023 askn (K.Sato) multix.jp            */
/*                                                        */
/* Check Device:                                          */
/*   AVR64EA32 AVR16EB32                                  */
/*                                                        */
/* Edit History:                                          */
/*                                                        */
/* April 2023                                             */
/* 9.2.1                                                  */
/**********************************************************/

/**********************************************************/
/*                                                        */
/* Optional defines:                                      */
/*                                                        */
/**********************************************************/
/*                                                        */
/* BIGBOOT:                                               */
/* Build a 1k bootloader, not 512 bytes. This turns on    */
/* extra functionality.                                   */
/*                                                        */
/* BAUD_RATE:                                             */
/* Set bootloader baud rate.                              */
/*                                                        */
/* LED_START_FLASHES:                                     */
/* Number of LED flashes on bootup.                       */
/*                                                        */
/* LED_DATA_FLASH:                                        */
/* Flash LED when transferring data. For boards without   */
/* TX or RX LEDs, or for people who like blinky lights.   */
/*                                                        */
/* WDTIME:                                                */
/* Bootloader timeout period, in seconds.                 */
/* 1, 2, 4, 8 supported.                                  */
/*                                                        */
/* UARTTX:                                                */
/* UART TX pin (B0, etc) for devices with more than       */
/* one hardware uart, or alternative pins                 */
/*                                                        */
/**********************************************************/

/**********************************************************/
/* Version Numbers!                                       */
/*                                                        */
/* Optiboot now includes a Version number in  the source  */
/*  and object code, and returns this value via STK500    */
/*                                                        */
/* The iniital Mega0/Xtiny support is version 9.          */
/*  This is very different from normal AVR because of     */
/*  changed peripherals and unified address space.        */
/*                                                        */
/* It would be good if versions implemented outside the   */
/*  official repository used an out-of-seqeunce version   */
/*  number (like 104.6 if based on based on 4.5) to       */
/*  prevent collisions.  The CUSTOM_VERSION=n option      */
/*  adds n to the high version to facilitate this.        */
/*                                                        */
/**********************************************************/

#define OPTIBOOT_MAJVER 9
#define OPTIBOOT_MINVER 2

/*
 * OPTIBOOT_CUSTOMVER should be defined (by the makefile) for custom edits
 * of optiboot.  That way you don't wind up with very different code that
 * matches the version number of a "released" optiboot.
 */

#if !defined(OPTIBOOT_CUSTOMVER)
  #define OPTIBOOT_CUSTOMVER 0x20
#endif

#include <inttypes.h>
#include <avr/io.h>

#if (!defined(__AVR_XMEGA__)) || ((__AVR_ARCH__ != 102) && (__AVR_ARCH__ != 103) && (__AVR_ARCH__ != 104))
  #error CPU not supported by this version of Optiboot.
  #include BUILD_STOP
  // include a non-existent file to stop compilation
#endif

const uint16_t optiboot_version
  __attribute__((section(".version")))
  __attribute__((used));
const uint16_t optiboot_version = 256 * (OPTIBOOT_MAJVER + OPTIBOOT_CUSTOMVER) + OPTIBOOT_MINVER;

/*
 * optiboot uses several "address" variables that are sometimes byte pointers,
 * sometimes word pointers. sometimes 16bit quantities, and sometimes built
 * up from 8bit input characters.  avr-gcc is not great at optimizing the
 * assembly of larger words from bytes, but we can use the usual union to
 * do this manually.  Expanding it a little, we can also get rid of casts.
 */
typedef union {
  uint8_t  *bptr;
  uint16_t *wptr;
  uint16_t word;
  uint8_t  bytes[2];
} addr16_t;

/*
 * This contains most of the rather ugly defines that implement our
 * ability to use UART=n and LED=D3, and some avr family bit name differences.
 */
#include "pin_defs_ex1.h"

/*
 * stk500.h contains the constant definitions for the stk500v1 comm protocol
 */
#include "stk500.h"

#ifndef LED_START_FLASHES
  #define LED_START_FLASHES 0
#endif

#ifdef UART
  #warning UART is ignored for this chip (use UARTTX=PortPin instead)
#endif

#if !defined(USART)

/*
 * set the UART baud rate defaults
 */
#ifndef BAUD_RATE
  #define BAUD_RATE 115200L
#endif

/*
 * calculate USARTn.BAUD setting value (asynchronous standard mode)
 */
#define BAUD_SETTING_16 ((16000000L / 6 * 64) / (16L * BAUD_RATE))
#define BAUD_SETTING_20 ((20000000L / 6 * 64) / (16L * BAUD_RATE))

#if (BAUD_SETTING_16 < 64)
  #error Unachievable baud rate (too fast) BAUD_RATE
#elif (BAUD_SETTING_16 > 65535)
  #error Unachievable baud rate (too slow) BAUD_RATE
#elif (BAUD_SETTING_20 < 64)
  #error Unachievable baud rate (too fast) BAUD_RATE
#elif (BAUD_SETTING_20 > 65535)
  #error Unachievable baud rate (too slow) BAUD_RATE
#endif

#endif /* not USART */

/*
 * Watchdog timeout translations from human readable to config vals
 */
#if !defined(WDTTIME)
  // 1 second
  #define WDTPERIOD WDT_PERIOD_1KCLK_gc
#elif (WDTTIME == 1)
  // 1 second
  #define WDTPERIOD WDT_PERIOD_1KCLK_gc
#elif (WDTTIME == 2)
  // 2 seconds
  #define WDTPERIOD WDT_PERIOD_2KCLK_gc
#elif (WDTTIME == 4)
  // 4 seconds
  #define WDTPERIOD WDT_PERIOD_4KCLK_gc
#elif (WDTTIME == 8)
  // 8 seconds
  #define WDTPERIOD WDT_PERIOD_8KCLK_gc
#else
  // 1 second
  #define WDTPERIOD WDT_PERIOD_1KCLK_gc
#endif

/* Function Prototypes
 * The main() function is in init9, which removes the interrupt vector table
 * we don't need. It is also 'OS_main', which means the compiler does not
 * generate any entry or exit code itself (but unlike 'naked', it doesn't
 * suppress some compile-time options we want.)
 */

int main (void)
    __attribute__((OS_main))
    __attribute__((section (".init9")))
    __attribute__((used));
void putch (uint8_t ch)
    __attribute__((noinline))
    __attribute__((leaf));
uint8_t getch (void)
    __attribute__((noinline))
    __attribute__((leaf));
void verifySpace (void)
    __attribute__((noinline));
void watchdogConfig (uint8_t x)
    __attribute__((noinline));
void getNch (uint8_t count);

#ifndef APP_NOSPM
void vector_table (void)
    __attribute__((naked))
    __attribute__((section (".init0")));
void nvmctrl (uint8_t _nvm_cmd)
    __attribute__((used))
    __attribute__((noinline))
    __attribute__((section (".init1")));
void nvmwrite (uint8_t* _address, uint8_t _data)
    __attribute__((used))
    __attribute__((noinline))
    __attribute__((section (".init2")));
#endif

#define watchdogReset() __builtin_avr_wdr()

#if LED_START_FLASHES > 0
static inline void flash_led (uint8_t);
#endif

/*
 * This section provides an auxiliary capability
 * for self-modifying the flash area.
 *
 * $0000 : Started Bootloader (POR)
 * $0002 : nvmwrite function : magicnumber $C009
 * $0004 : nvmctrl function  : magicnumber $E99D, $BF94
 */

#ifndef APP_NOSPM
void vector_table (void) {
  __asm__ __volatile__ (
    "RJMP    main \n"
    "RJMP    nvmwrite"
    /* next nvmctrl */
  );
}

void nvmctrl (uint8_t _nvm_cmd) {
  _PROTECTED_WRITE_SPM(NVMCTRL_CTRLA, _nvm_cmd);
  while (NVMCTRL.STATUS & (NVMCTRL_EEBUSY_bm | NVMCTRL_FLBUSY_bm));
}
void nvmwrite (uint8_t* _address, uint8_t _data) {
  *_address = _data;
}
#endif

/* main program starts here */
int main (void) {

  /*
   * Making these local and in registers prevents the need for initializing
   * them, and also saves space because code no longer stores to memory.
   * (initializing address keeps the compiler happy, but isn't really
   *  necessary, and uses 4 bytes of flash.)
   */

  register addr16_t address;
  register addr16_t length;
  register uint8_t ch;

  // This is the first code to run.
  //
  // Optiboot C code makes the following assumptions:
  //  No interrupts will execute
  //  SP points to RAMEND

  __asm__ __volatile__ ( "CLR __zero_reg__" ); // known-zero required by avr-libc

  ch = RSTCTRL_RSTFR;   // get reset cause

  // If the register is zero, consider it a user call and perform a software reset.
  if (ch == 0) {
    _PROTECTED_WRITE(RSTCTRL_SWRR, 1);
  }

#if defined(START_APP_ON_POR)
  if ((ch & RSTCTRL_WDRF_bm) || ch < 4)
#else
  if ((ch & RSTCTRL_WDRF_bm) || ch == RSTCTRL_BORF_bm)
#endif
  {
    RSTCTRL_RSTFR = ch;   // clear the reset causes before jumping to app...
    GPR_GPR0 = ch;        // but, stash the reset cause in GPIOR0 for use by app...
    __asm__ __volatile__ ( "RJMP app" );
  } // end of jumping to app

  watchdogConfig(WDTPERIOD);

#if defined(BIGBOOT)
  /* Clock control (Power On Reset) default settings; */
  _PROTECTED_WRITE(CLKCTRL_MCLKCTRLA, 0);     // CLKCTRL_CLKSEL_OSCHF_gc
  _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, 0);     // Prescaler Disable = Division 1x
  _PROTECTED_WRITE(CLKCTRL_OSCHFCTRLA, 0x0C); // CLKCTRL_FREQSEL_4M_gc (4MHz)
#endif

  // PORTMUX setting
#if defined (MYUART_PMUX_VAL)
  MYPMUX_REG = MYUART_PMUX_VAL;     // alternate pinout to use
#endif

#if !defined(USART)

if (bit_is_set(FUSE_OSCCFG, FUSE_OSCHFFRQ_bp)) {
  #if (BAUD_SETTING_16 < 256)
    MYUART.BAUDL = BAUD_SETTING_16;    // 8bit-wide register
  #else
    MYUART.BAUD = BAUD_SETTING_16;     // 16bit-wide register
  #endif
}
else {
  #if (BAUD_SETTING_20 < 256)
    MYUART.BAUDL = BAUD_SETTING_20;    // 8bit-wide register
  #else
    MYUART.BAUD = BAUD_SETTING_20;     // 16bit-wide register
  #endif
}

#endif /* not USART */

#ifdef RS485
  // RS485 setting
  #ifdef MYUART_XDIRCFG
    #ifdef RS485_INVERT
  MYUART_XDIRCFG = PORT_INVEN_bm;
    #endif
  MYUART.CTRLA = USART_RS485_EXT_gc;
  #else
    #error RS485 XDIR pin not USART exists
  #endif
#endif

#ifdef USART
  // USART setting
  #ifdef MYUART_XCKCFG
    #ifdef USART_INVERT
  MYUART_XCKCFG = PORT_INVEN_bm;
    #endif
  #else
    #error USART XCK pin not USART exists
  #endif
#endif

  // GPIO setting (VPORTn based)
#if defined(RS485) && defined(MYUART_XDIRPIN)
  MYUART_TXPORT.DIR = MYUART_TXPIN | MYUART_XDIRPIN;
#else
  MYUART_TXPORT.DIR |= MYUART_TXPIN;  // set TX pin to output
#endif

#ifdef PULLUP_RX
  // RX pin pullup (RX is TX next GPIO)
  MYUART_TXCFG = PORT_PULLUPEN_bm;
#endif

#ifdef USART
  // Sync, Parity Disabled, 1 StopBit
  MYUART.CTRLC = USART_CHSIZE_8BIT_gc | USART_CMODE_SYNCHRONOUS_gc;
#else
  // Async, Parity Disabled, 1 StopBit
  MYUART.CTRLC = USART_CHSIZE_8BIT_gc;
#endif

  MYUART.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
  // not interrupt, polling read-write UART started

#if (LED_START_FLASHES > 0) || defined(LED_DATA_FLASH) || defined(LED_START_ON)
  /* Set LED pin as output */
  LED_PORT.DIR |= LED;
#endif

#if LED_START_FLASHES > 0
  /* Flash onboard LED to signal entering of bootloader */
  #ifdef LED_INVERT
  flash_led(LED_START_FLASHES * 2 + 1);
  #else
  flash_led(LED_START_FLASHES * 2);
  #endif
#elif defined(LED_START_ON) && !defined(LED_INVERT)
  /* Turn on LED to indicate starting bootloader (less code!) */
  LED_PORT.OUT |= LED;
#endif

  /* Forever loop: exits by causing WDT reset */
  for (;;) {
    // get STK Command
    ch = getch();

    if (ch == STK_GET_PARAMETER) {
      ch = getch();
      verifySpace();
      /*
       * Send optiboot version as "SW version"
       * Note that the references to memory are optimized away.
       */
      if (ch == STK_SW_MINOR) ch = OPTIBOOT_MINVER;
      else if (ch == STK_SW_MAJOR) ch = OPTIBOOT_MAJVER + OPTIBOOT_CUSTOMVER;
      else ch = 0x03;
      putch(ch);
    }
    else if (ch == STK_SET_DEVICE) {
      // SET DEVICE is ignored
      // drop 20bytes
      getNch(20);
    }
    else if (ch == STK_SET_DEVICE_EXT) {
      // SET DEVICE EXT is ignored
      // drop 5bytes
      getNch(5);
    }
    else if (ch == STK_LOAD_ADDRESS) {
      // LOAD ADDRESS little endian
      address.bytes[0] = getch();
      address.bytes[1] = getch();
      // byte addressed mode
      // Both flash and EEPROM start at offset zero
      verifySpace();
    }
#ifdef BIGBOOT
    else if (ch == STK_UNIVERSAL) {
      // Not used because it is within 64KiB
      getNch(4);
      putch(0x00);  // response '0'
    }
#endif
    else if (ch == STK_PROG_PAGE) {
      /* Write up to 1 page of flash */
      /* Write memory block mode, length is big endian.  */
      length.bytes[1] = getch();
      length.bytes[0] = getch();
      ch = getch();

      nvmctrl(NVMCTRL_CMD_NOCMD_gc);
      if (ch == 'F') {
        /* Flash write */
        /*
         * The AVR_Ex series does not have a RAMPZ register, so adjust the FLMAP bit.
         */
        if (address.bytes[1] < 0x80) {
          /* Select low FPAGE */
          address.word += MAPPED_PROGMEM_START;
          _PROTECTED_WRITE(NVMCTRL_CTRLB, NVMCTRL_FLMAP_SECTION0_gc);
        }
        else {
          /* Select high FPAGE */
          _PROTECTED_WRITE(NVMCTRL_CTRLB, NVMCTRL_FLMAP_SECTION1_gc);
        }
        ch = NVMCTRL_CMD_FLPERW_gc;
      }
      else {
        /* EEPROM write */
        address.word += MAPPED_EEPROM_START;
        ch = NVMCTRL_CMD_EEPERW_gc;
      }
      do *(address.bptr++) = getch(); while (--length.word);
      nvmctrl(ch);

      /* Read command terminator, start reply */
      verifySpace();
    }
    else if (ch == STK_READ_PAGE) {
      /* Read memory block mode, length is big endian.  */
      length.bytes[1] = getch();
      length.bytes[0] = getch();
      ch = getch();
      verifySpace();

      /*
       * The entire flash does not fit in the same address space
       * so we call that helper function.
       * The AVR_Ex series does not have a RAMPZ register, so adjust the FLMAP bit.
       */
      if (ch == 'F') {
        if (address.bytes[1] < 0x80) {
          /* Select low FPAGE */
          address.word += MAPPED_PROGMEM_START;
          _PROTECTED_WRITE(NVMCTRL_CTRLB, NVMCTRL_FLMAP_SECTION0_gc);
        }
        else {
          /* Select high FPAGE */
          _PROTECTED_WRITE(NVMCTRL_CTRLB, NVMCTRL_FLMAP_SECTION1_gc);
        }
      }
      else { // it's EEPROM and we just read it
        address.word += MAPPED_EEPROM_START;
      }
      do putch(*(address.bptr++)); while (--length.word);
    }
    else if (ch == STK_READ_SIGN) {
      // READ SIGN - return actual device signature from SIGROW
      // this enables the same binary to be ued on multiple chips.
      verifySpace();

      /* SIGROW_DEVICEID0 : This value is always fixed. */
      putch(0x1E);

      /* This value indicates the size of the flash. */
      putch(SIGROW_DEVICEID1);

      /* Inconsistent values to avoid duplicate SIGROW */
      putch(SIGROW_DEVICEID2);
    }
    else {

#if defined(BIGBOOT)
      /* This covers the response to commands like STK_LEAVE_PROGMODE */
      /* Even if you ignore it, the WDT will be reset anyway. */
      if (ch == STK_LEAVE_PROGMODE) {
        watchdogConfig(WDT_PERIOD_256CLK_gc);
      }
#endif

      verifySpace();
    }
    putch(STK_OK);
  }
}

void putch (uint8_t ch) {
  loop_until_bit_is_set(MYUART.STATUS, USART_DREIF_bp);
  MYUART.TXDATAL = ch;
}

uint8_t getch (void) {
  register uint8_t ch, flags;
  loop_until_bit_is_set(MYUART.STATUS, USART_RXCIF_bp);
  flags = MYUART.RXDATAH;
  ch = MYUART.RXDATAL;
  if ((flags & USART_FERR_bm) == 0) watchdogReset();
#ifdef LED_DATA_FLASH
  LED_PORT.IN |= LED;
#endif
  return ch;
}

void getNch (uint8_t count) {
  do getch(); while (--count);
  verifySpace();
}

void verifySpace (void) {
  if (getch() != CRC_EOP) {
    watchdogConfig(WDT_PERIOD_8CLK_gc);
    for (;;) {}
    // a reset and app start.
  }
  putch(STK_INSYNC);
}

#if LED_START_FLASHES > 0
void flash_led (uint8_t count) {
  uint16_t delay;
  do {
    LED_PORT.IN |= LED;
    // delay assuming 2.66 or 3.33Mhz
    delay = 3000000U / 150;
    do {
      watchdogReset();
      if (bit_is_set(MYUART.STATUS, USART_RXCIF_bp)) return;
    } while (--delay);
  }
  while (--count);
  watchdogReset(); // for breakpointing
}
#endif

/*
 * Change the watchdog configuration.
 *  Could be a new timeout, could be off...
 */
void watchdogConfig (uint8_t x) {
  // Busy wait for sycnhronization is required!
  loop_until_bit_is_clear(WDT_STATUS, WDT_SYNCBUSY_bp);
  _PROTECTED_WRITE(WDT_CTRLA, x);
}

#ifdef BIGBOOT
/*
 * Optiboot is designed to fit in 512 bytes, with a minimum feature set.
 * Some chips have a minimum bootloader size of 1024 bytes, and sometimes
 * it is desirable to add extra features even though 512bytes is exceedded.
 * In that case, the BIGBOOT can be used.
 * Our extra features so far don't come close to filling 1k, so we can
 * add extra "frivolous" data to the image.   In particular, we can add
 * information about how Optiboot was built (which options were selected,
 * what version, all in human-readable form (and extractable from the
 * binary with avr-strings.)
 *
 * This can always be removed or trimmed if more actual program space
 * is needed in the future.  Currently the data occupies about 160 bytes,
 */
#define xstr(s) str(s)
#define str(s) #s
#define OPTFLASHSECT __attribute__((section(".fini8")))
#define OPT2FLASH(o) OPTFLASHSECT const char f##o[] = #o "=" xstr(o)

#ifdef LED_START_FLASHES
OPT2FLASH(LED_START_FLASHES);
#endif
#ifdef LED_DATA_FLASH
OPT2FLASH(LED_DATA_FLASH);
#endif
#ifdef LED_START_ON
OPT2FLASH(LED_START_ON);
#endif
#ifdef LED_NAME
OPTFLASHSECT const char f_LED[] = "LED=" LED_NAME;
#endif

#ifdef SUPPORT_EEPROM
OPT2FLASH(SUPPORT_EEPROM);
#endif

#ifdef USART
OPT2FLASH(USART);
#endif

#ifdef RS485
OPT2FLASH(RS485);
#endif

#ifdef BAUD_RATE
OPT2FLASH(BAUD_RATE);
#endif

#ifdef UARTTX
OPTFLASHSECT const char f_uart[] = "UARTTX=" UART_NAME;
#endif

OPTFLASHSECT const char f_date[] = "Built:" __DATE__ ":" __TIME__;
#ifdef BIGBOOT
OPT2FLASH(BIGBOOT);
#endif
OPTFLASHSECT const char f_device[] = "Device=" xstr(__AVR_DEVICE_NAME__);
#ifdef OPTIBOOT_CUSTOMVER
#if OPTIBOOT_CUSTOMVER != 0
OPT2FLASH(OPTIBOOT_CUSTOMVER);
#endif
#endif
OPTFLASHSECT const char f_version[] = "Version=" xstr(OPTIBOOT_MAJVER) "." xstr(OPTIBOOT_MINVER);

#endif

// Dummy application that will loop back into the bootloader if not overwritten
// This gives the bootloader somewhere to jump, and by referencing otherwise
//  unused variables/functions in the bootloader, it prevents them from being
//  omitted by the linker, with fewer mysterious link options.
void app (void)
    __attribute__((section( ".application")))
    __attribute__((noreturn))
    __attribute__((naked));

void app (void) {
  uint8_t ch;

  ch = RSTCTRL_RSTFR;
  RSTCTRL_RSTFR = ch; // reset causes
  *(volatile uint16_t *)(&optiboot_version);   // reference the version
  _PROTECTED_WRITE(RSTCTRL_SWRR, 1);
  // cause new reset - doesn't this make more sense?!
}

// end of code
