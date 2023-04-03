/*
 * pin_defs_dx.h
 * optiboot helper defining the default pin assignments (LED, SOFT_UART)
 * for the various chips that are supported.  This also has some ugly macros
 * for selecting among various UARTs and LED possibilities using command-line
 * defines like "UART=2 LED=B5"
 *
 * Copyright 2013-2015 by Bill Westfield.
 * Copyright 2010 by Peter Knight.
 * This software is licensed under version 2 of the Gnu Public Licence.
 * See optiboot.c for details.
 */


/*
 * ------------------------------------------------------------------------
 * A bunch of macros to enable the LED to be specified as "B5" for bit 5
 * of port B, and similar.
 * We define symbols for all the legal combination of port/bit on a chip,
 * and do pre-processor tests to see if there's a match.  This ends up
 * being very verbose, but it is pretty easy to generate semi-automatically.
 * (We wouldn't need this if the preprocessor could do string compares.)
 */

// Symbols for each PortA bit.
#define A0 0x100
#define A1 0x101
#define A2 0x102
#define A3 0x103
#define A4 0x104
#define A5 0x105
#define A6 0x106
#define A7 0x107
// If there is no PORTA on this chip, don't allow these to be used
//   (and indicate the error by redefining LED)
#if !defined(PORTA)
  #if LED >= A0 && LED <= A7
    #undef LED
    #define LED -1
  #endif
#endif

#define B0 0x200
#define B1 0x201
#define B2 0x202
#define B3 0x203
#define B4 0x204
#define B5 0x205
#define B6 0x206
#define B7 0x207
#if !defined(PORTB)
  #if LED >= B0 && LED <= B7
    #undef LED
    #define LED -1
  #endif
#endif

#define C0 0x300
#define C1 0x301
#define C2 0x302
#define C3 0x303
#define C4 0x304
#define C5 0x305
#define C6 0x306
#define C7 0x307
#if !(defined(PORTC))
  #if LED >= C0 && LED <= C7
    #undef LED
    #define LED -1
  #endif
#endif

#define D0 0x400
#define D1 0x401
#define D2 0x402
#define D3 0x403
#define D4 0x404
#define D5 0x405
#define D6 0x406
#define D7 0x407
#if !(defined(PORTD))
  #if LED >= D0 && LED <= D7
    #undef LED
    #define LED -1
  #endif
#endif

#define E0 0x500
#define E1 0x501
#define E2 0x502
#define E3 0x503
#define E4 0x504
#define E5 0x505
#define E6 0x506
#define E7 0x507
#if !(defined(PORTE))
  #if LED >= E0 && LED <= E7
    #undef LED
    #define LED -1
  #endif
#endif

#define F0 0x600
#define F1 0x601
#define F2 0x602
#define F3 0x603
#define F4 0x604
#define F5 0x605
#define F6 0x606
#define F7 0x607
#if !(defined(PORTF))
  #if LED >= F0 && LED <= F7
    #undef LED
    #define LED -1
  #endif
#endif

#define G0 0x700
#define G1 0x701
#define G2 0x702
#define G3 0x703
#define G4 0x704
#define G5 0x705
#define G6 0x706
#define G7 0x707
#if !defined(PORTG)
  #if LED >= G0 && LED <= G7
    #undef LED
    #define LED -1
  #endif
#endif


/*
 * A statement like "#if LED == B0" will evaluation (in the preprocessor)
 * to #if C0 == B0, and then to #if 0x301 == 0x201
 */
#if LED == B0
  #define LED_NAME "B0"
  #undef LED
  #define LED_PORT VPORTB
  #define LED PIN0_bm
#elif LED == B1
  #define LED_NAME "B1"
  #undef LED
  #define LED_PORT VPORTB
  #define LED PIN1_bm
#elif LED == B2
  #define LED_NAME "B2"
  #undef LED
  #define LED_PORT VPORTB
  #define LED PIN2_bm
#elif LED == B3
  #define LED_NAME "B3"
  #undef LED
  #define LED_PORT VPORTB
  #define LED PIN3_bm
#elif LED == B4
  #define LED_NAME "B4"
  #undef LED
  #define LED_PORT VPORTB
  #define LED PIN4_bm
#elif LED == B5
  #define LED_NAME "B5"
  #undef LED
  #define LED_PORT VPORTB
  #define LED PIN5_bm
#elif LED == B6
  #define LED_NAME "B6"
  #undef LED
  #define LED_PORT VPORTB
  #define LED PIN6_bm
#elif LED == B7
  #define LED_NAME "B7"
  #undef LED
  #define LED_PORT VPORTB
  #define LED PIN7_bm

#elif LED == C0
  #define LED_NAME "C0"
  #undef LED
  #define LED_PORT VPORTC
  #define LED PIN0_bm
#elif LED == C1
  #define LED_NAME "C1"
  #undef LED
  #define LED_PORT VPORTC
  #define LED PIN1_bm
#elif LED == C2
  #define LED_NAME "C2"
  #undef LED
  #define LED_PORT VPORTC
  #define LED PIN2_bm
#elif LED == C3
  #define LED_NAME "C3"
  #undef LED
  #define LED_PORT VPORTC
  #define LED PIN3_bm
#elif LED == C4
  #define LED_NAME "C4"
  #undef LED
  #define LED_PORT VPORTC
  #define LED PIN4_bm
#elif LED == C5
  #define LED_NAME "C5"
  #undef LED
  #define LED_PORT VPORTC
  #define LED PIN5_bm
#elif LED == C6
  #define LED_NAME "C6"
  #undef LED
  #define LED_PORT VPORTC
  #define LED PIN6_bm
#elif LED == C7
  #define LED_NAME "C7"
  #undef LED
  #define LED_PORT VPORTC
  #define LED PIN7_bm

#elif LED == D0
  #define LED_NAME "D0"
  #undef LED
  #define LED_PORT VPORTD
  #define LED PIN0_bm
#elif LED == D1
  #define LED_NAME "D1"
  #undef LED
  #define LED_PORT VPORTD
  #define LED PIN1_bm
#elif LED == D2
  #define LED_NAME "D2"
  #undef LED
  #define LED_PORT VPORTD
  #define LED PIN2_bm
#elif LED == D3
  #define LED_NAME "D3"
  #undef LED
  #define LED_PORT VPORTD
  #define LED PIN3_bm
#elif LED == D4
  #define LED_NAME "D4"
  #undef LED
  #define LED_PORT VPORTD
  #define LED PIN4_bm
#elif LED == D5
  #define LED_NAME "D5"
  #undef LED
  #define LED_PORT VPORTD
  #define LED PIN5_bm
#elif LED == D6
  #define LED_NAME "D6"
  #undef LED
  #define LED_PORT VPORTD
  #define LED PIN6_bm
#elif LED == D7
  #define LED_NAME "D7"
  #undef LED
  #define LED_PORT VPORTD
  #define LED PIN7_bm

#elif LED == E0
  #define LED_NAME "E0"
  #undef LED
  #define LED_PORT VPORTE
  #define LED PIN0_bm
#elif LED == E1
  #define LED_NAME "E1"
  #undef LED
  #define LED_PORT VPORTE
  #define LED PIN1_bm
#elif LED == E2
  #define LED_NAME "E2"
  #undef LED
  #define LED_PORT VPORTE
  #define LED PIN2_bm
#elif LED == E3
  #define LED_NAME "E3"
  #undef LED
  #define LED_PORT VPORTE
  #define LED PIN3_bm
#elif LED == E4
  #define LED_NAME "E4"
  #undef LED
  #define LED_PORT VPORTE
  #define LED PIN4_bm
#elif LED == E5
  #define LED_NAME "E5"
  #undef LED
  #define LED_PORT VPORTE
  #define LED PIN5_bm
#elif LED == E6
  #define LED_NAME "E6"
  #undef LED
  #define LED_PORT VPORTE
  #define LED PIN6_bm
#elif LED == E7
  #define LED_NAME "E7"
  #undef LED
  #define LED_PORT VPORTE
  #define LED PIN7_bm

#elif LED == F0
  #define LED_NAME "F0"
  #undef LED
  #define LED_PORT VPORTF
  #define LED PIN0_bm
#elif LED == F1
  #define LED_NAME "F1"
  #undef LED
  #define LED_PORT VPORTF
  #define LED PIN1_bm
#elif LED == F2
  #define LED_NAME "F2"
  #undef LED
  #define LED_PORT VPORTF
  #define LED PIN2_bm
#elif LED == F3
  #define LED_NAME "F3"
  #undef LED
  #define LED_PORT VPORTF
  #define LED PIN3_bm
#elif LED == F4
  #define LED_NAME "F4"
  #undef LED
  #define LED_PORT VPORTF
  #define LED PIN4_bm
#elif LED == F5
  #define LED_NAME "F5"
  #undef LED
  #define LED_PORT VPORTF
  #define LED PIN5_bm
#elif LED == F6
  #define LED_NAME "F6"
  #undef LED
  #define LED_PORT VPORTF
  #define LED PIN6_bm
#elif LED == F7
  #define LED_NAME "F7"
  #undef LED
  #define LED_PORT VPORTF
  #define LED PIN7_bm

#elif LED == G0
  #define LED_NAME "G0"
  #undef LED
  #define LED_PORT VPORTG
  #define LED PIN0_bm
#elif LED == G1
  #define LED_NAME "G1"
  #undef LED
  #define LED_PORT VPORTG
  #define LED PIN1_bm
#elif LED == G2
  #define LED_NAME "G2"
  #undef LED
  #define LED_PORT VPORTG
  #define LED PIN2_bm
#elif LED == G3
  #define LED_NAME "G3"
  #undef LED
  #define LED_PORT VPORTG
  #define LED PIN3_bm
#elif LED == G4
  #define LED_NAME "G4"
  #undef LED
  #define LED_PORT VPORTG
  #define LED PIN4_bm
#elif LED == G5
  #define LED_NAME "G5"
  #undef LED
  #define LED_PORT VPORTG
  #define LED PIN5_bm
#elif LED == G6
  #define LED_NAME "G6"
  #undef LED
  #define LED_PORT VPORTG
  #define LED PIN6_bm
#elif LED == G7
  #define LED_NAME "G7"
  #undef LED
  #define LED_PORT VPORTG
  #define LED PIN7_bm

// PORTs after G will require a Microchip do something different about the VPORT registers, because that's it for the I/O space!

#elif LED == A0
  #define LED_NAME "A0"
  #undef LED
  #define LED_PORT VPORTA
  #define LED PIN0_bm
#elif LED == A1
  #define LED_NAME "A1"
  #undef LED
  #define LED_PORT VPORTA
  #define LED PIN1_bm
#elif LED == A2
  #define LED_NAME "A2"
  #undef LED
  #define LED_PORT VPORTA
  #define LED PIN2_bm
#elif LED == A3
  #define LED_NAME "A3"
  #undef LED
  #define LED_PORT VPORTA
  #define LED PIN3_bm
#elif LED == A4
  #define LED_NAME "A4"
  #undef LED
  #define LED_PORT VPORTA
  #define LED PIN4_bm
#elif LED == A5
  #define LED_NAME "A5"
  #undef LED
  #define LED_PORT VPORTA
  #define LED PIN5_bm
#elif LED == A6
  #define LED_NAME "A6"
  #undef LED
  #define LED_PORT VPORTA
  #define LED PIN6_bm
#elif LED == A7
  #define LED_NAME "A7"
  #undef LED
  #define LED_PORT VPORTA
  #define LED PIN7_bm

#else
  // Stop compilation right away, so we don't get more errors.
  #if LED == -1
    #error Unrecognized LED name.  Should be like "B5"
    // Stop compilation right away, so we don't get more errors.
    #pragma GCC diagnostic warning "-Wfatal-errors"
    #error Nonexistent LED PORT.  Check datasheet.
  #endif
  #pragma GCC diagnostic warning "-Wfatal-errors"
  #error Unrecognized LED name.  Should be like "B5"
#endif


/*
 * Handle devices with up to 6 uarts.
 */
#if \
  defined(__AVR_AVR128DA64__) || defined(__AVR_AVR64DA64__) || defined(__AVR_AVR32DA64__) || \
  defined(__AVR_AVR128DA48__) || defined(__AVR_AVR64DA48__) || defined(__AVR_AVR32DA48__) || \
  defined(__AVR_AVR128DA32__) || defined(__AVR_AVR64DA32__) || defined(__AVR_AVR32DA32__) || \
  defined(__AVR_AVR128DA28__) || defined(__AVR_AVR64DA28__) || defined(__AVR_AVR32DA28__) || \
  defined(__AVR_AVR128DB64__) || defined(__AVR_AVR64DB64__) || \
  defined(__AVR_AVR128DB48__) || defined(__AVR_AVR64DB48__) || defined(__AVR_AVR32DB48__) || \
  defined(__AVR_AVR128DB32__) || defined(__AVR_AVR64DB32__) || defined(__AVR_AVR32DB32__) || \
  defined(__AVR_AVR128DB28__) || defined(__AVR_AVR64DB28__) || defined(__AVR_AVR32DB28__)
  #if   (UARTTX == A0)
    #define UART_NAME "A0"
    #ifndef USART0
      #error Pin on USART0, but no USART0 exists
    #endif
    #define MYUART USART0
    #define MYUART_TXPORT VPORTA
    #define MYUART_TXPIN  PIN0_bm
    #define MYUART_TXCFG  PORTA_PIN0CTRL
    #define MYUART_RXCFG  PORTA_PIN1CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART0_DEFAULT_gc)
    #define MYPMUX_REG PORTMUX_USARTROUTEA
    #define MYUART_XDIRPIN PIN3_bm
    #define MYUART_XDIRCFG PORTA_PIN3CTRL
    #define MYUART_XCKPIN  PIN2_bm
    #define MYUART_XCKCFG  PORTA_PIN2CTRL
    #define MYUART_PORTREG PORTA
  #elif (UARTTX == A4)
    #define UART_NAME "A4"
    #ifndef USART0
      #error Pin on USART0, but no USART0 exists
    #endif
    #define MYUART USART0
    #define MYUART_TXPORT VPORTA
    #define MYUART_TXPIN  PIN4_bm
    #define MYUART_TXCFG  PORTA_PIN4CTRL
    #define MYUART_RXCFG  PORTA_PIN5CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART0_ALT1_gc)
    #define MYPMUX_REG PORTMUX.USARTROUTEA
    #define MYUART_XDIRPIN PIN7_bm
    #define MYUART_XDIRCFG PORTA_PIN7CTRL
    #define MYUART_XCKPIN  PIN6_bm
    #define MYUART_XCKCFG  PORTA_PIN6CTRL
    #define MYUART_PORTREG PORTA
  #elif (UARTTX == B0)
    #define UART_NAME "B0"
    #ifndef USART3
      #error Pin on USART3, but no USART3 exists
    #endif
    #define MYUART USART3
    #define MYUART_TXPORT VPORTB
    #define MYUART_TXPIN  PIN0_bm
    #define MYUART_TXCFG  PORTB_PIN0CTRL
    #define MYUART_RXCFG  PORTB_PIN1CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART3_DEFAULT_gc)
    #define MYPMUX_REG PORTMUX.USARTROUTEA
    #define MYUART_XDIRPIN PIN3_bm
    #define MYUART_XDIRCFG PORTB_PIN3CTRL
    #define MYUART_XCKPIN  PIN2_bm
    #define MYUART_XCKCFG  PORTB_PIN2CTRL
    #define MYUART_PORTREG PORTB
  #elif (UARTTX == B4)
    #define UART_NAME "B4"
    #ifndef USART3
      #error Pin on USART3, but no USART3 exists
    #endif
    #define MYUART USART3
    #define MYUART_TXPORT VPORTB
    #define MYUART_TXPIN  PIN4_bm
    #define MYUART_TXCFG  PORTB_PIN4CTRL
    #define MYUART_RXCFG  PORTB_PIN5CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART3_ALT1_gc)
    #define MYPMUX_REG PORTMUX.USARTROUTEA
    #define MYUART_XDIRPIN PIN7_bm
    #define MYUART_XDIRCFG PORTB_PIN7CTRL
    #define MYUART_XCKPIN  PIN6_bm
    #define MYUART_XCKCFG  PORTB_PIN6CTRL
    #define MYUART_PORTREG PORTB
  #elif (UARTTX == C0)
    #define UART_NAME "C0"
    #ifndef USART1
      #error Pin on USART1, but no USART1 exists
    #endif
    #define MYUART USART1
    #define MYUART_TXPORT VPORTC
    #define MYUART_TXPIN  PIN0_bm
    #define MYUART_TXCFG  PORTC_PIN0CTRL
    #define MYUART_RXCFG  PORTC_PIN1CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART1_DEFAULT_gc)
    #define MYPMUX_REG PORTMUX.USARTROUTEA
    #define MYUART_XDIRPIN PIN3_bm
    #define MYUART_XDIRCFG PORTC_PIN3CTRL
    #define MYUART_XCKPIN  PIN2_bm
    #define MYUART_XCKCFG  PORTC_PIN2CTRL
    #define MYUART_PORTREG PORTC
  #elif (UARTTX == C4)
    #define UART_NAME "C4"
    #ifndef USART1
      #error Pin on USART1, but no USART1 exists
    #endif
    #define MYUART USART1
    #define MYUART_TXPORT VPORTC
    #define MYUART_TXPIN  PIN4_bm
    #define MYUART_TXCFG  PORTC_PIN4CTRL
    #define MYUART_RXCFG  PORTC_PIN5CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART1_ALT1_gc)
    #define MYPMUX_REG PORTMUX.USARTROUTEA
    #define MYUART_XDIRPIN PIN7_bm
    #define MYUART_XDIRCFG PORTC_PIN7CTRL
    #define MYUART_XCKPIN  PIN6_bm
    #define MYUART_XCKCFG  PORTC_PIN6CTRL
    #define MYUART_PORTREG PORTC
  #elif (UARTTX == F0)
    #define UART_NAME "F0"
    #ifndef USART2
      #error Pin on USART2, but no USART2 exists
    #endif
    #define MYUART USART2
    #define MYUART_TXPORT VPORTF
    #define MYUART_TXPIN  PIN0_bm
    #define MYUART_TXCFG  PORTF_PIN0CTRL
    #define MYUART_RXCFG  PORTF_PIN1CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART2_DEFAULT_gc)
    #define MYPMUX_REG PORTMUX_USARTROUTEA
    #define MYUART_XDIRPIN PIN3_bm
    #define MYUART_XDIRCFG PORTD_PIN3CTRL
    #define MYUART_XCKPIN  PIN2_bm
    #define MYUART_XCKCFG  PORTF_PIN2CTRL
    #define MYUART_PORTREG PORTF
  #elif (UARTTX == F4)
    #define UART_NAME "F4"
    #ifndef USART2
      #error Pin on USART2, but no USART2 exists
    #endif
    #define MYUART USART2
    #define MYUART_TXPORT VPORTF
    #define MYUART_TXPIN  PIN4_bm
    #define MYUART_TXCFG  PORTF_PIN4CTRL
    #define MYUART_RXCFG  PORTF_PIN5CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART2_ALT1_gc)
    #define MYPMUX_REG PORTMUX_USARTROUTEA
    #define MYUART_PORTREG PORTF
  #elif (UARTTX == E0)
    #define UART_NAME "E0"
    #ifndef USART4
      #error Pin on USART4, but no USART4 exists
    #endif
    #define MYUART USART4
    #define MYUART_TXPORT VPORTE
    #define MYUART_TXPIN  PIN0_bm
    #define MYUART_TXCFG  PORTE_PIN0CTRL
    #define MYUART_RXCFG  PORTE_PIN1CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART4_DEFAULT_gc)
    #define MYPMUX_REG PORTMUX.USARTROUTEB
    #define MYUART_XDIRPIN PIN3_bm
    #define MYUART_XDIRCFG PORTE_PIN3CTRL
    #define MYUART_XCKPIN  PIN2_bm
    #define MYUART_XCKCFG  PORTE_PIN2CTRL
    #define MYUART_PORTREG PORTE
  #elif (UARTTX == E4)
    #define UART_NAME "E4"
    #ifndef USART4
      #error Pin on USART4, but no USART4 exists
    #endif
    #define MYUART USART4
    #define MYUART_TXPORT VPORTE
    #define MYUART_TXPIN  PIN4_bm
    #define MYUART_TXCFG  PORTE_PIN4CTRL
    #define MYUART_RXCFG  PORTE_PIN5CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART4_ALT1_gc)
    #define MYPMUX_REG PORTMUX.USARTROUTEB
    #define MYUART_XDIRPIN PIN7_bm
    #define MYUART_XDIRCFG PORTE_PIN7CTRL
    #define MYUART_XCKPIN  PIN6_bm
    #define MYUART_XCKCFG  PORTE_PIN6CTRL
    #define MYUART_PORTREG PORTE
  #elif (UARTTX == G0)
    #define UART_NAME "G0"
    #ifndef USART5
      #error Pin on USART5, but no USART5 exists
    #endif
    #define MYUART USART5
    #define MYUART_TXPORT VPORTG
    #define MYUART_TXPIN  PIN0_bm
    #define MYUART_TXCFG  PORTG_PIN0CTRL
    #define MYUART_RXCFG  PORTG_PIN1CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART5_DEFAULT_gc)
    #define MYPMUX_REG PORTMUX.USARTROUTEB
    #define MYUART_XDIRPIN PIN3_bm
    #define MYUART_XDIRCFG PORTG_PIN3CTRL
    #define MYUART_XCKPIN  PIN2_bm
    #define MYUART_XCKCFG  PORTG_PIN2CTRL
    #define MYUART_PORTREG PORTG
  #elif (UARTTX == G4)
    #define UART_NAME "G4"
    #ifndef USART2
      #error Pin on USART5, but no USART5 exists
    #endif
    #define MYUART USART5
    #define MYUART_TXPORT VPORTG
    #define MYUART_TXPIN  PIN4_bm
    #define MYUART_TXCFG  PORTG_PIN4CTRL
    #define MYUART_RXCFG  PORTG_PIN5CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART5_ALT1_gc)
    #define MYPMUX_REG PORTMUX.USARTROUTEB
    #define MYUART_XDIRPIN PIN7_bm
    #define MYUART_XDIRCFG PORTG_PIN7CTRL
    #define MYUART_XCKPIN  PIN6_bm
    #define MYUART_XCKCFG  PORTG_PIN6CTRL
    #define MYUART_PORTREG PORTG
  #endif
#endif

#if \
  defined(__AVR_AVR64DD32__) || defined(__AVR_AVR32DD32__) || defined(__AVR_AVR16DD32__) || \
  defined(__AVR_AVR64DD28__) || defined(__AVR_AVR32DD28__) || defined(__AVR_AVR16DD28__) || \
  defined(__AVR_AVR64DD20__) || defined(__AVR_AVR32DD20__) || defined(__AVR_AVR16DD20__) || \
  defined(__AVR_AVR64DD14__) || defined(__AVR_AVR32DD14__) || defined(__AVR_AVR16DD14__)
  #if   (UARTTX == A0)
    #define UART_NAME "A0"
    #ifndef USART0
      #error Pin on USART0, but no USART0 exists
    #endif
    #define MYUART USART0
    #define MYUART_TXPORT VPORTA
    #define MYUART_TXPIN  PIN0_bm
    #define MYUART_TXCFG  PORTA_PIN0CTRL
    #define MYUART_RXCFG  PORTA_PIN1CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART0_DEFAULT_gc)
    #define MYPMUX_REG PORTMUX.USARTROUTEA
    #define MYUART_XDIRPIN PIN3_bm
    #define MYUART_XDIRCFG PORTA_PIN3CTRL
    #define MYUART_XCKPIN  PIN2_bm
    #define MYUART_XCKCFG  PORTA_PIN2CTRL
    #define MYUART_PORTREG PORTA
  #elif (UARTTX == A2)
    #define UART_NAME "A2"
    #ifndef USART0
      #error Pin on USART0, but no USART0 exists
    #endif
    #define MYUART USART0
    #define MYUART_TXPORT VPORTA
    #define MYUART_TXPIN  PIN2_bm
    #define MYUART_TXCFG  PORTA_PIN2CTRL
    #define MYUART_RXCFG  PORTA_PIN3CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART0_ALT2_gc)
    #define MYPMUX_REG PORTMUX.USARTROUTEA
    #define MYUART_PORTREG PORTA
  #elif (UARTTX == A4)
    #define UART_NAME "A4"
    #ifndef USART0
      #error Pin on USART0, but no USART0 exists
    #endif
    #define MYUART USART0
    #define MYUART_TXPORT VPORTA
    #define MYUART_TXPIN  PIN4_bm
    #define MYUART_TXCFG  PORTA_PIN4CTRL
    #define MYUART_RXCFG  PORTA_PIN5CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART0_ALT1_gc)
    #define MYPMUX_REG PORTMUX.USARTROUTEA
    #define MYUART_XDIRPIN PIN7_bm
    #define MYUART_XDIRCFG PORTA_PIN7CTRL
    #define MYUART_XCKPIN  PIN6_bm
    #define MYUART_XCKCFG  PORTA_PIN6CTRL
    #define MYUART_PORTREG PORTA
  #elif (UARTTX == C1)
    #define UART_NAME "C1"
    #ifndef USART0
      #error Pin on USART0, but no USART0 exists
    #endif
    #define MYUART USART0
    #define MYUART_TXPORT VPORTC
    #define MYUART_TXPIN  PIN1_bm
    #define MYUART_TXCFG  PORTC_PIN1CTRL
    #define MYUART_RXCFG  PORTC_PIN2CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART0_ALT4_gc)
    #define MYPMUX_REG PORTMUX.USARTROUTEA
    #define MYUART_XCKPIN  PIN3_bm
    #define MYUART_XCKCFG  PORTC_PIN3CTRL
    #define MYUART_PORTREG PORTC
  #elif (UARTTX == D4)
    #define UART_NAME "D4"
    #ifndef USART0
      #error Pin on USART0, but no USART0 exists
    #endif
    #define MYUART USART0
    #define MYUART_TXPORT VPORTD
    #define MYUART_TXPIN  PIN4_bm
    #define MYUART_TXCFG  PORTD_PIN4CTRL
    #define MYUART_RXCFG  PORTD_PIN5CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART0_ALT3_gc)
    #define MYPMUX_REG PORTMUX.USARTROUTEA
    #define MYUART_XDIRPIN PIN7_bm
    #define MYUART_XDIRCFG PORTD_PIN7CTRL
    #define MYUART_XCKPIN  PIN6_bm
    #define MYUART_XCKCFG  PORTD_PIN6CTRL
    #define MYUART_PORTREG PORTD
  #elif (UARTTX == D6)
    #define UART_NAME "D6"
    #ifndef USART1
      #error Pin on USART1, but no USART1 exists
    #endif
    #define MYUART USART1
    #define MYUART_TXPORT VPORTD
    #define MYUART_TXPIN  PIN6_bm
    #define MYUART_TXCFG  PORTD_PIN6CTRL
    #define MYUART_RXCFG  PORTD_PIN7CTRL
    #define MYUART_PMUX_VAL (PORTMUX_USART1_ALT2_gc)
    #define MYPMUX_REG PORTMUX.USARTROUTEA
    #define MYUART_PORTREG PORTD
  #endif
#endif

#ifndef MYUART
  #warning No UARTTX pin specified.
#endif

