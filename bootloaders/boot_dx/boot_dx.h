/**
 * @file boot_dx.h
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 3.7
 * @date 2023-11-30
 *
 * @copyright Copyright (c) 2024 askn37 at github.com
 *
 */
// MIT License : https://askn37.github.io/LICENSE.html

#pragma once

/*** Default vaules ***/

// #define BOOT_HW_VER '2' /* This is defined later */
#define BOOT_MAJVER 3   /* To save space, this value is not returned */
#define BOOT_MINVER 72

#ifndef UART
#define UART A0
#endif

#ifndef BAUD_RATE
#define BAUD_RATE 115200
#endif

#if !defined(__AVR_XMEGA__)
        || ((__AVR_ARCH__ != 102)
        &&  (__AVR_ARCH__ != 103)
        &&  (__AVR_ARCH__ != 104))
  #error This AVR chip is not supported
  #include "BUILD_STOP"
#endif

/*** STK500 constant values ***/
/* List only compatible numbers */

#define STK_OK              0x10
#define STK_INSYNC          0x14
#define CRC_EOP             0x20  // 'SPACE'
#define STK_GET_PARAMETER   0x41  // 'A'
#define STK_SET_DEVICE      0x42  // 'B'
#define STK_SET_DEVICE_EXT  0x45  // 'E'
#define PAR_LOAD_EXT_ADDR   0x4d  // 'M' (STK_UNIVERSAL sub command)
#define STK_LEAVE_PROGMODE  0x51  // 'Q'
#define STK_LOAD_ADDRESS    0x55  // 'U'
#define STK_UNIVERSAL       0x56  // 'V'
#define STK_PROG_PAGE       0x64  // 'd'
#define STK_READ_PAGE       0x74  // 't'
#define STK_READ_SIGN       0x75  // 'u'
#define PAR_SW_MAJOR        0x81  // (STK_GET_PARAMETER sub command)
#define PAR_SW_MINOR        0x82  // (STK_GET_PARAMETER sub command)

/*** Pin constat values ***/

//// Pin name to PORT configuration
////   bit[765] PORTA-G index position
////   bit[4]   1 (+16) (A=16,B=48,C=80,D=112,E=144,F=176,G=208)
////   bit[3]   0
////   bit[210] PIN0-7 bit position (0-7)

#define A0 16
#define A1 17
#define A2 18
#define A3 19
#define A4 20
#define A5 21
#define A6 22
#define A7 23
#define B0 48
#define B1 49
#define B2 50
#define B3 51
#define B4 52
#define B5 53
#define B6 54
#define B7 55
#define C0 80
#define C1 81
#define C2 82
#define C3 83
#define C4 84
#define C5 85
#define C6 86
#define C7 87
#define D0 112
#define D1 113
#define D2 114
#define D3 115
#define D4 116
#define D5 117
#define D6 118
#define D7 119
#define E0 144
#define E1 145
#define E2 146
#define E3 147
#define E4 148
#define E5 149
#define E6 150
#define E7 151
#define F0 176
#define F1 177
#define F2 178
#define F3 179
#define F4 180
#define F5 181
#define F6 182
#define F7 183
#define G0 208
#define G1 209
#define G2 210
#define G3 211
#define G4 212
#define G5 213
#define G6 214
#define G7 215

/* If you build at a speed other than the default 4MHz. */
#ifndef F_CPU_Scale
  #define F_CPU_Scale 1
#endif
#if F_CPU_Scale == 1
  #define F_CPU 4000000L  /* CLKCTRL_FREQSEL_4M_gc */
#elif F_CPU_Scale == 2
  #define F_CPU 8000000L
  #define FREQSEL 0x14    /* CLKCTRL_FREQSEL_8M_gc */
#elif F_CPU_Scale == 3
  #define F_CPU 12000000L
  #define FREQSEL 0x18    /* CLKCTRL_FREQSEL_12M_gc */
#elif F_CPU_Scale == 4
  #define F_CPU 16000000L
  #define FREQSEL 0x1c    /* CLKCTRL_FREQSEL_16M_gc */
#elif F_CPU_Scale == 5
  #define F_CPU 20000000L
  #define FREQSEL 0x20    /* CLKCTRL_FREQSEL_20M_gc */
#elif F_CPU_Scale == 6
  #define F_CPU 24000000L
  #define FREQSEL 0x24    /* CLKCTRL_FREQSEL_24M_gc */
#else
  #error This F_CPU value cannot be specified
  #include "BUILD_STOP"
#endif

/* This union helps with compilation optimization. */
typedef union {
  uint8_t  *bptr;
  uint16_t word;
  uint8_t  bytes[2];
} addr16_t;

#define wdt_reset() __builtin_avr_wdr()

/* Convert watchdog timeout specified in seconds to configuration value. */

#ifndef TIMEOUT
  #define TIMEOUT 0
#endif
#ifdef TIMEOUT
  #if (TIMEOUT == 1)
    #define WDTPERIOD WDT_PERIOD_1KCLK_gc
  #elif (TIMEOUT == 2)
    #define WDTPERIOD WDT_PERIOD_2KCLK_gc
  #elif (TIMEOUT == 4)
    #define WDTPERIOD WDT_PERIOD_4KCLK_gc
  #elif (TIMEOUT == 8)
    #define WDTPERIOD WDT_PERIOD_8KCLK_gc
  #else
    #define WDTPERIOD WDT_PERIOD_512CLK_gc
  #endif
#endif

/*** Non-existent specifications will be invalidated */

#if defined(LED_BLINK) && LED_BLINK == 0
  #undef LED_BLINK
#endif 

#ifdef LED_PORT
  #undef LED_PORT
#endif

#ifdef PORTA
  #if (A0 <= LED) && (LED <= A7)
    #define LED_PORT VPORTA
  #endif
#endif

#ifdef PORTB
  #if (B0 <= LED) && (LED <= B7)
    #define LED_PORT VPORTB
  #endif
#endif

#ifdef PORTC
  #if (C0 <= LED) && (LED <= C7)
    #define LED_PORT VPORTC
  #endif
#endif

#ifdef PORTD
  #if (D0 <= LED) && (LED <= D7)
    #define LED_PORT VPORTD
  #endif
#endif

#ifdef PORTE
  #if (E0 <= LED) && (LED <= E7)
    #define LED_PORT VPORTE
  #endif
#endif

#ifdef PORTF
  #if (F0 <= LED) && (LED <= F7)
    #define LED_PORT VPORTF
  #endif
#endif

#ifdef PORTG
  #if (G0 <= LED) && (LED <= G7)
    #define LED_PORT VPORTG
  #endif
#endif

#ifndef LED_PORT
  #warning The specified LED pin does not exist. Please check the datasheet.
#else
  #define LED_PIN (LED & 7)
#endif

/*** Detailed settings for each part ***/

/*** AVR_DA/DB Series ***/
/* In this series, pins Pn0 and Pn4 except PORTD can be selected as TxD pins. */
/* For LEDs, we recommend using PA7, which is present in all chips. */

#if \
  defined(__AVR_AVR128DA64__) || defined(__AVR_AVR64DA64__) || defined(__AVR_AVR32DA64__) || \
  defined(__AVR_AVR128DA48__) || defined(__AVR_AVR64DA48__) || defined(__AVR_AVR32DA48__) || \
  defined(__AVR_AVR128DA32__) || defined(__AVR_AVR64DA32__) || defined(__AVR_AVR32DA32__) || \
  defined(__AVR_AVR128DA28__) || defined(__AVR_AVR64DA28__) || defined(__AVR_AVR32DA28__) || \
  defined(__AVR_AVR128DB64__) || defined(__AVR_AVR64DB64__) || \
  defined(__AVR_AVR128DB48__) || defined(__AVR_AVR64DB48__) || defined(__AVR_AVR32DB48__) || \
  defined(__AVR_AVR128DB32__) || defined(__AVR_AVR64DB32__) || defined(__AVR_AVR32DB32__) || \
  defined(__AVR_AVR128DB28__) || defined(__AVR_AVR64DB28__) || defined(__AVR_AVR32DB28__)
  #define BOOT_HW_VER '2' /* Make sure to match the NVMCTRL version. */
  #if (UART == A0) && defined(USART0)
    #define UART_BASE     USART0
    #define UART_PORTREG  PORTA
    #define UART_TXPORT   VPORTA
    #define UART_TXPIN    PIN0_bm
    #define UART_TXCFG    PORTA_PIN0CTRL
    #define UART_RXCFG    PORTA_PIN1CTRL
    // #define UART_PMUX_VAL PORTMUX_USART0_DEFAULT_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
    #define UART_XCKPIN   PIN2_bm
    #define UART_XCKCFG   PORTA_PIN2CTRL
    #define UART_XDIRPIN  PIN3_bm
    #define UART_XDIRCFG  PORTA_PIN3CTRL
  #elif (UART == A4) && defined(USART0)
    #define UART_BASE     USART0
    #define UART_PORTREG  PORTA
    #define UART_TXPORT   VPORTA
    #define UART_TXPIN    PIN4_bm
    #define UART_TXCFG    PORTA_PIN4CTRL
    #define UART_RXCFG    PORTA_PIN5CTRL
    #define UART_PMUX_VAL PORTMUX_USART0_ALT1_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
    #define UART_XCKPIN   PIN6_bm
    #define UART_XCKCFG   PORTA_PIN6CTRL
    #define UART_XDIRPIN  PIN7_bm
    #define UART_XDIRCFG  PORTA_PIN7CTRL
  #elif (UART == C0) && defined(USART1)
    #define UART_BASE     USART1
    #define UART_PORTREG  PORTC
    #define UART_TXPORT   VPORTC
    #define UART_TXPIN    PIN0_bm
    #define UART_TXCFG    PORTC_PIN0CTRL
    #define UART_RXCFG    PORTC_PIN1CTRL
    // #define UART_PMUX_VAL PORTMUX_USART1_DEFAULT_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
    #define UART_XCKPIN   PIN2_bm
    #define UART_XCKCFG   PORTC_PIN2CTRL
    #define UART_XDIRPIN  PIN3_bm
    #define UART_XDIRCFG  PORTC_PIN3CTRL
  #elif (UART == C4) && defined(USART1) && defined(PORTC_PIN4CTRL)
    #define UART_BASE     USART1
    #define UART_PORTREG  PORTC
    #define UART_TXPORT   VPORTC
    #define UART_TXPIN    PIN4_bm
    #define UART_TXCFG    PORTC_PIN4CTRL
    #define UART_RXCFG    PORTC_PIN5CTRL
    #define UART_PMUX_VAL PORTMUX_USART1_ALT1_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
    #define UART_XCKPIN   PIN6_bm
    #define UART_XCKCFG   PORTC_PIN6CTRL
    #define UART_XDIRPIN  PIN7_bm
    #define UART_XDIRCFG  PORTC_PIN7CTRL
  #elif (UART == F0) && defined(USART2)
    #define UART_BASE     USART2
    #define UART_PORTREG  PORTF
    #define UART_TXPORT   VPORTF
    #define UART_TXPIN    PIN0_bm
    #define UART_TXCFG    PORTF_PIN0CTRL
    #define UART_RXCFG    PORTF_PIN1CTRL
    // #define UART_PMUX_VAL PORTMUX_USART2_DEFAULT_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
    #ifdef PORTF_PIN2CTRL
    #define UART_XCKPIN   PIN2_bm
    #define UART_XCKCFG   PORTF_PIN2CTRL
    #define UART_XDIRPIN  PIN3_bm
    #define UART_XDIRCFG  PORTF_PIN3CTRL
    #endif
  #elif (UART == F4) && defined(USART2) && defined(PORTF_PIN4CTRL)
    #define UART_BASE     USART2
    #define UART_PORTREG  PORTF
    #define UART_TXPORT   VPORTF
    #define UART_TXPIN    PIN4_bm
    #define UART_TXCFG    PORTF_PIN4CTRL
    #define UART_RXCFG    PORTF_PIN5CTRL
    #define UART_PMUX_VAL PORTMUX_USART2_ALT1_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
  #elif (UART == B0) && defined(USART3)
    #define UART_BASE     USART3
    #define UART_PORTREG  PORTB
    #define UART_TXPORT   VPORTB
    #define UART_TXPIN    PIN0_bm
    #define UART_TXCFG    PORTB_PIN0CTRL
    #define UART_RXCFG    PORTB_PIN1CTRL
    // #define UART_PMUX_VAL PORTMUX_USART3_DEFAULT_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
    #define UART_XCKPIN   PIN2_bm
    #define UART_XCKCFG   PORTB_PIN2CTRL
    #define UART_XDIRPIN  PIN3_bm
    #define UART_XDIRCFG  PORTB_PIN3CTRL
  #elif (UART == B4) && defined(USART3)
    #define UART_BASE     USART3
    #define UART_PORTREG  PORTB
    #define UART_TXPORT   VPORTB
    #define UART_TXPIN    PIN4_bm
    #define UART_TXCFG    PORTB_PIN4CTRL
    #define UART_RXCFG    PORTB_PIN5CTRL
    #define UART_PMUX_VAL PORTMUX_USART3_ALT1_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
    #define UART_XCKPIN   PIN6_bm
    #define UART_XCKCFG   PORTB_PIN6CTRL
    #define UART_XDIRPIN  PIN7_bm
    #define UART_XDIRCFG  PORTB_PIN7CTRL
  #elif (UART == E0) && defined(USART4)
    #define UART_BASE     USART4
    #define UART_PORTREG  PORTE
    #define UART_TXPORT   VPORTE
    #define UART_TXPIN    PIN0_bm
    #define UART_TXCFG    PORTE_PIN0CTRL
    #define UART_RXCFG    PORTE_PIN1CTRL
    // #define UART_PMUX_VAL PORTMUX_USART4_DEFAULT_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEB
    #define UART_XCKPIN   PIN2_bm
    #define UART_XCKCFG   PORTE_PIN2CTRL
    #define UART_XDIRPIN  PIN3_bm
    #define UART_XDIRCFG  PORTE_PIN3CTRL
  #elif (UART == E4) && defined(USART4)
    #define UART_BASE     USART4
    #define UART_PORTREG  PORTE
    #define UART_TXPORT   VPORTE
    #define UART_TXPIN    PIN4_bm
    #define UART_TXCFG    PORTE_PIN4CTRL
    #define UART_RXCFG    PORTE_PIN5CTRL
    #define UART_PMUX_VAL PORTMUX_USART4_ALT1_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEB
    #define UART_XCKPIN   PIN6_bm
    #define UART_XCKCFG   PORTE_PIN6CTRL
    #define UART_XDIRPIN  PIN7_bm
    #define UART_XDIRCFG  PORTE_PIN7CTRL
  #elif (UART == G0) && defined(USART5)
    #define UART_BASE     USART5
    #define UART_PORTREG  PORTG
    #define UART_TXPORT   VPORTG
    #define UART_TXPIN    PIN0_bm
    #define UART_TXCFG    PORTG_PIN0CTRL
    #define UART_RXCFG    PORTG_PIN1CTRL
    // #define UART_PMUX_VAL PORTMUX_USART5_DEFAULT_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEB
    #define UART_XCKPIN   PIN2_bm
    #define UART_XCKCFG   PORTG_PIN2CTRL
    #define UART_XDIRPIN  PIN3_bm
    #define UART_XDIRCFG  PORTG_PIN3CTRL
  #elif (UART == G4) && defined(USART5)
    #define UART_BASE     USART5
    #define UART_PORTREG  PORTG
    #define UART_TXPORT   VPORTG
    #define UART_TXPIN    PIN4_bm
    #define UART_TXCFG    PORTG_PIN4CTRL
    #define UART_RXCFG    PORTG_PIN5CTRL
    #define UART_PMUX_VAL PORTMUX_USART5_ALT1_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEB
    #define UART_XCKPIN   PIN6_bm
    #define UART_XCKCFG   PORTG_PIN6CTRL
    #define UART_XDIRPIN  PIN7_bm
    #define UART_XDIRCFG  PORTG_PIN7CTRL
  #endif
#endif

/*** AVR_DD Series ***/
/* The PORTMUX layout of this series is special. */
/* PC0 cannot be selected as TxD because it conflicts with the MVIO function. */

#if \
  defined(__AVR_AVR64DD32__) || defined(__AVR_AVR32DD32__) || defined(__AVR_AVR16DD32__) || \
  defined(__AVR_AVR64DD28__) || defined(__AVR_AVR32DD28__) || defined(__AVR_AVR16DD28__) || \
  defined(__AVR_AVR64DD20__) || defined(__AVR_AVR32DD20__) || defined(__AVR_AVR16DD20__) || \
  defined(__AVR_AVR64DD14__) || defined(__AVR_AVR32DD14__) || defined(__AVR_AVR16DD14__)
  #define BOOT_HW_VER '2' /* Make sure to match the NVMCTRL version. */
  #if (UART == A0) && defined(USART0)
    #define UART_PORTREG  PORTA
    #define UART_BASE     USART0
    #define UART_TXPORT   VPORTA
    #define UART_TXPIN    PIN0_bm
    #define UART_TXCFG    PORTA_PIN0CTRL
    #define UART_RXCFG    PORTA_PIN1CTRL
    // #define UART_PMUX_VAL PORTMUX_USART0_DEFAULT_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
    #define UART_XCKPIN   PIN2_bm
    #define UART_XCKCFG   PORTA_PIN2CTRL
    #define UART_XDIRPIN  PIN3_bm
    #define UART_XDIRCFG  PORTA_PIN3CTRL
  #elif (UART == A4) && defined(USART0) && defined(PORTA_PIN4CTRL)
    #define UART_BASE     USART0
    #define UART_PORTREG  PORTA
    #define UART_TXPORT   VPORTA
    #define UART_TXPIN    PIN4_bm
    #define UART_TXCFG    PORTA_PIN4CTRL
    #define UART_RXCFG    PORTA_PIN5CTRL
    #define UART_PMUX_VAL PORTMUX_USART0_ALT1_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
    #define UART_XCKPIN   PIN6_bm
    #define UART_XCKCFG   PORTA_PIN6CTRL
    #define UART_XDIRPIN  PIN7_bm
    #define UART_XDIRCFG  PORTA_PIN7CTRL
  #elif (UART == A2) && defined(USART0)
    #define UART_BASE     USART0
    #define UART_PORTREG  PORTA
    #define UART_TXPORT   VPORTA
    #define UART_TXPIN    PIN2_bm
    #define UART_TXCFG    PORTA_PIN2CTRL
    #define UART_RXCFG    PORTA_PIN3CTRL
    #define UART_PMUX_VAL PORTMUX_USART0_ALT2_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
  #elif (UART == D4) && defined(USART0)
    #define UART_BASE     USART0
    #define UART_PORTREG  PORTD
    #define UART_TXPORT   VPORTD
    #define UART_TXPIN    PIN4_bm
    #define UART_TXCFG    PORTD_PIN4CTRL
    #define UART_RXCFG    PORTD_PIN5CTRL
    #define UART_PMUX_VAL PORTMUX_USART0_ALT3_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
    #define UART_XCKPIN   PIN6_bm
    #define UART_XCKCFG   PORTD_PIN6CTRL
    #define UART_XDIRPIN  PIN7_bm
    #define UART_XDIRCFG  PORTD_PIN7CTRL
  #elif (UART == C1) && defined(USART0)
    #define UART_BASE     USART0
    #define UART_PORTREG  PORTC
    #define UART_TXPORT   VPORTC
    #define UART_TXPIN    PIN1_bm
    #define UART_TXCFG    PORTC_PIN1CTRL
    #define UART_RXCFG    PORTC_PIN2CTRL
    #define UART_PMUX_VAL PORTMUX_USART0_ALT4_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
    #define UART_XCKPIN   PIN3_bm
    #define UART_XCKCFG   PORTC_PIN3CTRL
  #elif (UART == D6) && defined(USART1)
    #define UART_BASE     USART1
    #define UART_PORTREG  PORTD
    #define UART_TXPORT   VPORTD
    #define UART_TXPIN    PIN6_bm
    #define UART_TXCFG    PORTD_PIN6CTRL
    #define UART_RXCFG    PORTD_PIN7CTRL
    #define UART_PMUX_VAL PORTMUX_USART1_ALT2_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
  #endif
#endif

/*** AVR_DU Series ***/
/* The PORTMUX layout of this series is special. */
/* PC0 cannot be selected as TxD because it conflicts with the MVIO function. */

#if \
  defined(__AVR_AVR64DU32__) || defined(__AVR_AVR32DU32__) || defined(__AVR_AVR16DU32__) || \
  defined(__AVR_AVR64DU28__) || defined(__AVR_AVR32DU28__) || defined(__AVR_AVR16DU28__) || \
  defined(__AVR_AVR32DU20__) || defined(__AVR_AVR16DU20__) || \
  defined(__AVR_AVR32DU14__) || defined(__AVR_AVR16DU14__)
  #define BOOT_HW_VER '4' /* Make sure to match the NVMCTRL version. */
  #if (UART == A0) && defined(USART0)
    #define UART_PORTREG  PORTA
    #define UART_BASE     USART0
    #define UART_TXPORT   VPORTA
    #define UART_TXPIN    PIN0_bm
    #define UART_TXCFG    PORTA_PIN0CTRL
    #define UART_RXCFG    PORTA_PIN1CTRL
    // #define UART_PMUX_VAL PORTMUX_USART0_DEFAULT_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
    #define UART_XCKPIN   PIN2_bm
    #define UART_XCKCFG   PORTA_PIN2CTRL
    #define UART_XDIRPIN  PIN3_bm
    #define UART_XDIRCFG  PORTA_PIN3CTRL
  #elif (UART == A4) && defined(USART0) && defined(PORTA_PIN4CTRL)
    #define UART_BASE     USART0
    #define UART_PORTREG  PORTA
    #define UART_TXPORT   VPORTA
    #define UART_TXPIN    PIN4_bm
    #define UART_TXCFG    PORTA_PIN4CTRL
    #define UART_RXCFG    PORTA_PIN5CTRL
    #define UART_PMUX_VAL PORTMUX_USART0_ALT1_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
    #define UART_XCKPIN   PIN6_bm
    #define UART_XCKCFG   PORTA_PIN6CTRL
    #define UART_XDIRPIN  PIN7_bm
    #define UART_XDIRCFG  PORTA_PIN7CTRL
  #elif (UART == A2) && defined(USART0) && defined(PORTA_PIN2CTRL)
    #define UART_BASE     USART0
    #define UART_PORTREG  PORTA
    #define UART_TXPORT   VPORTA
    #define UART_TXPIN    PIN2_bm
    #define UART_TXCFG    PORTA_PIN2CTRL
    #define UART_RXCFG    PORTA_PIN3CTRL
    #define UART_PMUX_VAL PORTMUX_USART0_ALT2_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
  #elif (UART == D4) && defined(USART0) && defined(PORTD_PIN4CTRL)
    #define UART_BASE     USART0
    #define UART_PORTREG  PORTD
    #define UART_TXPORT   VPORTD
    #define UART_TXPIN    PIN4_bm
    #define UART_TXCFG    PORTD_PIN4CTRL
    #define UART_RXCFG    PORTD_PIN5CTRL
    #define UART_PMUX_VAL PORTMUX_USART0_ALT3_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
    #define UART_XCKPIN   PIN6_bm
    #define UART_XCKCFG   PORTD_PIN6CTRL
    #define UART_XDIRPIN  PIN7_bm
    #define UART_XDIRCFG  PORTD_PIN7CTRL
  #elif (UART == D6) && defined(USART1)
    #define UART_BASE     USART1
    #define UART_PORTREG  PORTD
    #define UART_TXPORT   VPORTD
    #define UART_TXPIN    PIN6_bm
    #define UART_TXCFG    PORTD_PIN6CTRL
    #define UART_RXCFG    PORTD_PIN7CTRL
    #define UART_PMUX_VAL PORTMUX_USART1_ALT2_gc
    #define UART_PMUX_REG PORTMUX_USARTROUTEA
  #endif
#endif

#ifndef UART_BASE
  #error The specified UART TxD pin does not exist. Please check the datasheet.
  #include "BUILD_STOP"
#endif

// end of header file
