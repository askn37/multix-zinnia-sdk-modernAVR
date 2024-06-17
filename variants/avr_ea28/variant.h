/**
 * @file variant.h
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2023-04-21
 *
 * @copyright Copyright (c) 2024 askn37 at github.com
 *
 */
// MIT License : https://askn37.github.io/LICENSE.html

#pragma once
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <variant_io.h>
#include <api/CLKCTRL_modernAVR.h>

#define AVR_MODERNAVR 1
#define AVR_AVREX     1
#define AVR_AVREA     1
#define AVR_AVREA28   1
#define AVR_NVMCTRL   3
#define AVR_EVSYS   202

//// Pin name to PORT configuration
////   bit[765] PORTA-G index position
////   bit[4]   1 (+16) (A=16,B=48,C=80,D=112,E=144,F=176,G=208)
////   bit[3]   0
////   bit[210] PIN0-7 bit position (0-7)

/* GPIO x24 (other VDD,GND,VDD,GND) */

#define PIN_PA0 16
#define PIN_PA1 17
#define PIN_PA2 18
#define PIN_PA3 19
#define PIN_PA4 20
#define PIN_PA5 21
#define PIN_PA6 22
#define PIN_PA7 23

/* PORTB not implemented */

#define PIN_PC0 80
#define PIN_PC1 81
#define PIN_PC2 82
#define PIN_PC3 83
/*      PIN_PC4 not implemented */
/*      PIN_PC5 not implemented */
/*      PIN_PC6 not implemented */
/*      PIN_PC7 not implemented */

#define PIN_PD0 112
#define PIN_PD1 113
#define PIN_PD2 114
#define PIN_PD3 115
#define PIN_PD4 116
#define PIN_PD5 117
#define PIN_PD6 118
#define PIN_PD7 119

/* PORTE not implemented */

#define PIN_PF0 176
#define PIN_PF1 177
/*      PIN_PF2 not implemented */
/*      PIN_PF3 not implemented */
/*      PIN_PF4 not implemented */
/*      PIN_PF5 not implemented */
#define PIN_PF6 182
#define PIN_PF7 183 /* Default UPDI */

/* PORTG not implemented */

#define NOT_A_PIN    255
#define PIN_VREFA    PIN_PD7
#define PIN_RESET    PIN_PF6
#define PIN_UPDI     PIN_PF7

#ifndef LED_BUILTIN
#define LED_BUILTIN  PIN_PA7
#endif
#define LED_BUILTIN_INVERT  /* implementation dependent */

/* Timer Waveout signal */

#define PIN_WO0      PIN_PA0
#define PIN_WO1      PIN_PA1
#define PIN_WO2      PIN_PA2
#define PIN_WO3      PIN_PA3
#define PIN_WO4      PIN_PA4
#define PIN_WO5      PIN_PA5
// #define PIN_WO0_ALT1 PIN_PB0
// #define PIN_WO1_ALT1 PIN_PB1
// #define PIN_WO2_ALT1 PIN_PB2
// #define PIN_WO3_ALT1 PIN_PB3
// #define PIN_WO4_ALT1 PIN_PB4
// #define PIN_WO5_ALT1 PIN_PB5
#define PIN_WO0_ALT2 PIN_PC0
#define PIN_WO1_ALT2 PIN_PC1
#define PIN_WO2_ALT2 PIN_PC2
#define PIN_WO3_ALT2 PIN_PC3
// #define PIN_WO4_ALT2 PIN_PC4
// #define PIN_WO5_ALT2 PIN_PC5
#define PIN_WO0_ALT3 PIN_PD0
#define PIN_WO1_ALT3 PIN_PD1
#define PIN_WO2_ALT3 PIN_PD2
#define PIN_WO3_ALT3 PIN_PD3
#define PIN_WO4_ALT3 PIN_PD4
#define PIN_WO5_ALT3 PIN_PD5
// #define PIN_WO0_ALT4 PIN_PE0
// #define PIN_WO1_ALT4 PIN_PE1
// #define PIN_WO2_ALT4 PIN_PE2
// #define PIN_WO3_ALT4 PIN_PE3
#define PIN_WO0_ALT5 PIN_PF0
#define PIN_WO1_ALT5 PIN_PF1
// #define PIN_WO2_ALT5 PIN_PF2
// #define PIN_WO3_ALT5 PIN_PF3
// #define PIN_WO4_ALT5 PIN_PF4
// #define PIN_WO5_ALT5 PIN_PF5

#define PIN_TCA0_WO0      PIN_PA0
#define PIN_TCA0_WO1      PIN_PA1
#define PIN_TCA0_WO2      PIN_PA2
#define PIN_TCA0_WO3      PIN_PA3
#define PIN_TCA0_WO4      PIN_PA4
#define PIN_TCA0_WO5      PIN_PA5
// #define PIN_TCA0_WO0_ALT1 PIN_PB0
// #define PIN_TCA0_WO1_ALT1 PIN_PB1
// #define PIN_TCA0_WO2_ALT1 PIN_PB2
// #define PIN_TCA0_WO3_ALT1 PIN_PB3
// #define PIN_TCA0_WO4_ALT1 PIN_PB4
// #define PIN_TCA0_WO5_ALT1 PIN_PB5
#define PIN_TCA0_WO0_ALT2 PIN_PC0
#define PIN_TCA0_WO1_ALT2 PIN_PC1
#define PIN_TCA0_WO2_ALT2 PIN_PC2
#define PIN_TCA0_WO3_ALT2 PIN_PC3
// #define PIN_TCA0_WO4_ALT2 PIN_PC4
// #define PIN_TCA0_WO5_ALT2 PIN_PC5
#define PIN_TCA0_WO0_ALT3 PIN_PD0
#define PIN_TCA0_WO1_ALT3 PIN_PD1
#define PIN_TCA0_WO2_ALT3 PIN_PD2
#define PIN_TCA0_WO3_ALT3 PIN_PD3
#define PIN_TCA0_WO4_ALT3 PIN_PD4
#define PIN_TCA0_WO5_ALT3 PIN_PD5
// #define PIN_TCA0_WO0_ALT4 PIN_PE0
// #define PIN_TCA0_WO1_ALT4 PIN_PE1
// #define PIN_TCA0_WO2_ALT4 PIN_PE2
// #define PIN_TCA0_WO3_ALT4 PIN_PE3
#define PIN_TCA0_WO0_ALT5 PIN_PF0
#define PIN_TCA0_WO1_ALT5 PIN_PF1
// #define PIN_TCA0_WO2_ALT5 PIN_PF2
// #define PIN_TCA0_WO3_ALT5 PIN_PF3
// #define PIN_TCA0_WO4_ALT5 PIN_PF4
// #define PIN_TCA0_WO5_ALT5 PIN_PF5

// #define PIN_TCA1_WO0      PIN_PB0
// #define PIN_TCA1_WO1      PIN_PB1
// #define PIN_TCA1_WO2      PIN_PB2
// #define PIN_TCA1_WO3      PIN_PB3
// #define PIN_TCA1_WO4      PIN_PB4
// #define PIN_TCA1_WO5      PIN_PB5
// #define PIN_TCA1_WO0_ALT1 PIN_PC4
// #define PIN_TCA1_WO1_ALT1 PIN_PC5
// #define PIN_TCA1_WO2_ALT1 PIN_PC6
#define PIN_TCA1_WO0_ALT2 PIN_PA4
#define PIN_TCA1_WO1_ALT2 PIN_PA5
#define PIN_TCA1_WO2_ALT2 PIN_PA6
#define PIN_TCA1_WO0_ALT3 PIN_PD4
#define PIN_TCA1_WO1_ALT3 PIN_PD5
#define PIN_TCA1_WO2_ALT3 PIN_PD6

#define PIN_TCB0_WO       PIN_PA2
#define PIN_TCB1_WO       PIN_PA3
#define PIN_TCB2_WO       PIN_PC0
// #define PIN_TCB3_WO       PIN_PB5
// #define PIN_TCB0_WO_ALT1  PIN_PF4
// #define PIN_TCB1_WO_ALT1  PIN_PF5
// #define PIN_TCB2_WO_ALT1  PIN_PB4
#define PIN_TCB3_WO_ALT1  PIN_PC1

/* peripheral ports */

#define PIN_AC0_OUT       PIN_PA7
// #define PIN_AC0_OUT_ALT1  PIN_PC5
#define PIN_AC0_AINN3     PIN_PC2
#define PIN_AC0_AINN4     PIN_PC3
#define PIN_AC0_AINN1     PIN_PD0
#define PIN_AC0_AINP0     PIN_PD2
#define PIN_AC0_AINN0     PIN_PD3
#define PIN_AC0_AINP3     PIN_PD6
#define PIN_AC0_AINN2     PIN_PD7
// #define PIN_AC0_AINP1     PIN_PE0
// #define PIN_AC0_AINP2     PIN_PE2

#define PIN_AC1_OUT       PIN_PA7
// #define PIN_AC1_OUT_ALT1  PIN_PC6
#define PIN_AC1_AINN3     PIN_PC2
#define PIN_AC1_AINP4     PIN_PC3
#define PIN_AC1_AINN1     PIN_PD0
#define PIN_AC1_AINP0     PIN_PD2
#define PIN_AC1_AINP1     PIN_PD3
#define PIN_AC1_AINP2     PIN_PD4
#define PIN_AC1_AINN0     PIN_PD5
#define PIN_AC1_AINP3     PIN_PD6
#define PIN_AC1_AINN2     PIN_PD7

#define PIN_ADC0_AIN0     PIN_PD0
#define PIN_ADC0_AIN1     PIN_PD1
#define PIN_ADC0_AIN2     PIN_PD2
#define PIN_ADC0_AIN3     PIN_PD3
#define PIN_ADC0_AIN4     PIN_PD4
#define PIN_ADC0_AIN5     PIN_PD5
#define PIN_ADC0_AIN6     PIN_PD6
#define PIN_ADC0_AIN7     PIN_PD7
// #define PIN_ADC0_AIN8     PIN_PE0
// #define PIN_ADC0_AIN9     PIN_PE1
// #define PIN_ADC0_AIN10    PIN_PE2
// #define PIN_ADC0_AIN11    PIN_PE3
#define PIN_ADC0_AIN16    PIN_PF0
#define PIN_ADC0_AIN17    PIN_PF1
// #define PIN_ADC0_AIN18    PIN_PF2
// #define PIN_ADC0_AIN19    PIN_PF3
// #define PIN_ADC0_AIN20    PIN_PF4
// #define PIN_ADC0_AIN21    PIN_PF5
#define PIN_ADC0_AIN22    PIN_PA2
#define PIN_ADC0_AIN23    PIN_PA3
#define PIN_ADC0_AIN24    PIN_PA4
#define PIN_ADC0_AIN25    PIN_PA5
#define PIN_ADC0_AIN26    PIN_PA6
#define PIN_ADC0_AIN27    PIN_PA7
#define PIN_ADC0_AIN28    PIN_PC0
#define PIN_ADC0_AIN29    PIN_PC1
#define PIN_ADC0_AIN30    PIN_PC2
#define PIN_ADC0_AIN31    PIN_PC3

#define PIN_DAC0_OUT      PIN_PD6

#define PIN_EVOUTA        PIN_PA2
#define PIN_EVOUTA_ALT1   PIN_PA7
// #define PIN_EVOUTB        PIN_PB2
#define PIN_EVOUTC        PIN_PC2
// #define PIN_EVOUTC_ALT1   PIN_PC7
#define PIN_EVOUTD        PIN_PD2
#define PIN_EVOUTD_ALT1   PIN_PD7
// #define PIN_EVOUTE        PIN_PE2
// #define PIN_EVOUTF        PIN_PF2
#define PIN_EVOUTF_ALT1   PIN_PF7

#define PIN_LUT0_IN0      PIN_PA0
#define PIN_LUT0_IN1      PIN_PA1
#define PIN_LUT0_IN2      PIN_PA2
#define PIN_LUT0_OUT      PIN_PA3
#define PIN_LUT0_OUT_ALT1 PIN_PA6
#define PIN_LUT1_IN0      PIN_PC0
#define PIN_LUT1_IN1      PIN_PC1
#define PIN_LUT1_IN2      PIN_PC2
#define PIN_LUT1_OUT      PIN_PC3
// #define PIN_LUT1_OUT_ALT1 PIN_PC6
#define PIN_LUT2_IN0      PIN_PD0
#define PIN_LUT2_IN1      PIN_PD1
#define PIN_LUT2_IN2      PIN_PD2
#define PIN_LUT2_OUT      PIN_PD3
#define PIN_LUT2_OUT_ALT1 PIN_PD6
#define PIN_LUT3_IN0      PIN_PF0
#define PIN_LUT3_IN1      PIN_PF1
// #define PIN_LUT3_IN2      PIN_PF2
// #define PIN_LUT3_OUT      PIN_PF3

#define PIN_SPI0_MOSI        PIN_PA4
#define PIN_SPI0_MISO        PIN_PA5
#define PIN_SPI0_SCK         PIN_PA6
#define PIN_SPI0_SS          PIN_PA7
// #define PIN_SPI0_MOSI_ALT1   PIN_PE0
// #define PIN_SPI0_MISO_ALT1   PIN_PE1
// #define PIN_SPI0_SCK_ALT1    PIN_PE2
// #define PIN_SPI0_SS_ALT1     PIN_PE3
#define PIN_SPI0_MOSI_ALT3   PIN_PA0
#define PIN_SPI0_MISO_ALT3   PIN_PA1
#define PIN_SPI0_SCK_ALT3    PIN_PC0
#define PIN_SPI0_SS_ALT3     PIN_PC1
#define PIN_SPI0_MOSI_ALT4   PIN_PD4
#define PIN_SPI0_MISO_ALT4   PIN_PD5
#define PIN_SPI0_SCK_ALT4    PIN_PD6
#define PIN_SPI0_SS_ALT4     PIN_PD7
#define PIN_SPI0_MOSI_ALT5   PIN_PC0
#define PIN_SPI0_MISO_ALT5   PIN_PC1
#define PIN_SPI0_SCK_ALT5    PIN_PC2
#define PIN_SPI0_SS_ALT5     PIN_PC3
#define PIN_SPI0_MOSI_ALT6   PIN_PC1
#define PIN_SPI0_MISO_ALT6   PIN_PC2
#define PIN_SPI0_SCK_ALT6    PIN_PC3
#define PIN_SPI0_SS_ALT6     PIN_PF7

#define PIN_TWI0_SCL         PIN_PA2
#define PIN_TWI0_SDA         PIN_PA3
#define PIN_TWI0_SCL_ALT1    PIN_PA2
#define PIN_TWI0_SDA_ALT1    PIN_PA3
#define PIN_TWI0_SCL_ALT2    PIN_PC2
#define PIN_TWI0_SDA_ALT2    PIN_PC3
#define PIN_TWI0_SCL_ALT3    PIN_PA0
#define PIN_TWI0_SDA_ALT3    PIN_PA1
#define PIN_TWI0S_SCL        PIN_PC2
#define PIN_TWI0S_SDA        PIN_PC3
// #define PIN_TWI0S_SCL_ALT1   PIN_PC6
// #define PIN_TWI0S_SDA_ALT1   PIN_PC7
// #define PIN_TWI0S_SCL_ALT2   PIN_PC6
// #define PIN_TWI0S_SDA_ALT2   PIN_PC7
#define PIN_TWI0S_SCL_ALT3   PIN_PC2
#define PIN_TWI0S_SDA_ALT3   PIN_PC3

#define PIN_USART0_TXD       PIN_PA0
#define PIN_USART0_RXD       PIN_PA1
#define PIN_USART0_XCK       PIN_PA2
#define PIN_USART0_XDIR      PIN_PA3
#define PIN_USART0_TXD_ALT1  PIN_PA4
#define PIN_USART0_RXD_ALT1  PIN_PA5
#define PIN_USART0_XCK_ALT1  PIN_PA6
#define PIN_USART0_XDIR_ALT1 PIN_PA7
#define PIN_USART0_TXD_ALT2  PIN_PA2
#define PIN_USART0_RXD_ALT2  PIN_PA3
#define PIN_USART0_TXD_ALT3  PIN_PD4
#define PIN_USART0_RXD_ALT3  PIN_PD5
#define PIN_USART0_XCK_ALT3  PIN_PD6
#define PIN_USART0_XDIR_ALT3 PIN_PD7
#define PIN_USART0_TXD_ALT4  PIN_PC1
#define PIN_USART0_RXD_ALT4  PIN_PC2
#define PIN_USART0_XCK_ALT4  PIN_PC3
#define PIN_USART1_TXD       PIN_PC0
#define PIN_USART1_RXD       PIN_PC1
#define PIN_USART1_XCK       PIN_PC2
#define PIN_USART1_XDIR      PIN_PC3
// #define PIN_USART1_TXD_ALT1  PIN_PC4
// #define PIN_USART1_RXD_ALT1  PIN_PC5
// #define PIN_USART1_XCK_ALT1  PIN_PC6
// #define PIN_USART1_XDIR_ALT1 PIN_PC7
#define PIN_USART1_TXD_ALT2  PIN_PD6
#define PIN_USART1_RXD_ALT2  PIN_PD7
#define PIN_USART2_TXD       PIN_PF0
#define PIN_USART2_RXD       PIN_PF1
// #define PIN_USART2_XCK       PIN_PF2
// #define PIN_USART2_XDIR      PIN_PF3
// #define PIN_USART2_TXD_ALT1  PIN_PF4
// #define PIN_USART2_RXD_ALT1  PIN_PF5

/* peripheral symbols */

#define HAVE_AC0           AC0_AC_vect_num
#define HAVE_AC1           AC1_AC_vect_num
#define HAVE_ADC0     ADC0_RESRDY_vect_num
#define HAVE_BOD          BOD_VLM_vect_num
#define HAVE_CCL          CCL_CCL_vect_num
#define HAVE_CLKCTR   CLKCTRL_CFD_vect_num
#define HAVE_NMI              NMI_vect_num
#define HAVE_NVMCTRL   NVMCTRL_EE_vect_num
#define HAVE_PIT          RTC_PIT_vect_num
#define HAVE_PORTA     PORTA_PORT_vect_num
#define HAVE_PORTB     PORTB_PORT_vect_num
#define HAVE_PORTC     PORTC_PORT_vect_num
#define HAVE_PORTD     PORTD_PORT_vect_num
#define HAVE_PORTE     PORTE_PORT_vect_num
#define HAVE_PORTF     PORTF_PORT_vect_num
#define HAVE_RTC          RTC_CNT_vect_num
#define HAVE_SPI0        SPI0_INT_vect_num
#define HAVE_TCA0       TCA0_LUNF_vect_num
#define HAVE_TCA1       TCA1_LUNF_vect_num
#define HAVE_TCB0        TCB0_INT_vect_num
#define HAVE_TCB1        TCB1_INT_vect_num
#define HAVE_TCB2        TCB2_INT_vect_num
#define HAVE_TCB3        TCB3_INT_vect_num
#define HAVE_TWI0       TWI0_TWIS_vect_num
#define HAVE_USART0    USART0_RXC_vect_num
#define HAVE_USART1    USART1_RXC_vect_num
#define HAVE_USART2    USART2_RXC_vect_num
#define HAVE_USART3    USART3_RXC_vect_num

/* build.console_select */

#ifndef ICSP_Serial
#define ICSP_Serial Serial2
#endif

/* build.console_select */

#ifndef Serial
#define Serial Serial0
#endif

#ifndef Wire
#define Wire Wire0
#endif

#ifdef __cplusplus
extern "C" {
#endif

inline void initVariant (void) {
  _CLKCTRL_SETUP();
  PORTA.PINCONFIG  = PORT_ISC_INPUT_DISABLE_gc;
  PORTA.PINCTRLUPD = ~0;
  // PORTB.PINCTRLUPD = ~0;
  PORTC.PINCTRLUPD = ~0;
  PORTD.PINCTRLUPD = ~0;
  // PORTE.PINCTRLUPD = ~0;
  PORTF.PINCTRLUPD = ~0;
}

#ifdef __cplusplus
} // extern "C"
#endif

// end of code
