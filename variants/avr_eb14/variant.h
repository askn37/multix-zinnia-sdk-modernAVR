/**
 * @file variant.h
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2023-10-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <variant_io.h>
#include <api/CLKCTRL_modernAVR.h>

#define AVR_MODERNAVR 1
#define AVR_AVREX     1
#define AVR_AVREB     1
#define AVR_AVREB14   1
#define AVR_NVMCTRL   5
#define AVR_EVSYS   202

//// Pin name to PORT configuration
////   bit[765] PORTA-G index position
////   bit[4]   1 (+16) (A=16,B=48,C=80,D=112,E=144,F=176,G=208)
////   bit[3]   0
////   bit[210] PIN0-7 bit position (0-7)

/* GPIO x12 (other VDD,GND) */

#define PIN_PA0 16
#define PIN_PA1 17
/*      PIN_PA2 not implemented */
/*      PIN_PA3 not implemented */
/*      PIN_PA4 not implemented */
/*      PIN_PA5 not implemented */
/*      PIN_PA6 not implemented */
/*      PIN_PA7 not implemented */

/* PORTB not implemented */

#define PIN_PC0 80
#define PIN_PC1 81
#define PIN_PC2 82
#define PIN_PC3 83
/*      PIN_PC4 not implemented */
/*      PIN_PC5 not implemented */
/*      PIN_PC6 not implemented */
/*      PIN_PC7 not implemented */

/*      PIN_PD0 not implemented */
/*      PIN_PD1 not implemented */
/*      PIN_PD2 not implemented */
/*      PIN_PD3 not implemented */
#define PIN_PD4 116
#define PIN_PD5 117
#define PIN_PD6 118
#define PIN_PD7 119

/* PORTE not implemented */

/*      PIN_PF0 not implemented */
/*      PIN_PF1 not implemented */
/*      PIN_PF2 not implemented */
/*      PIN_PF3 not implemented */
/*      PIN_PF4 not implemented */
/*      PIN_PF5 not implemented */
#define PIN_PF6 182 /* HV-programming pad */
#define PIN_PF7 183 /* Default UPDI */

/* PORTG not implemented */

#define NOT_A_PIN    255
#define PIN_VREFA    PIN_PD7
#define PIN_RESET    PIN_PF6
#define PIN_UPDI     PIN_PF7

#ifndef LED_BUILTIN
#define LED_BUILTIN  PIN_PD7
#endif
#define LED_BUILTIN_INVERT  /* implementation dependent */

/* Timer Waveout signal */

#define PIN_WO0      PIN_PA0
#define PIN_WO1      PIN_PA1
// #define PIN_WO2      PIN_PA2
// #define PIN_WO3      PIN_PA3
// #define PIN_WO4      PIN_PA4
// #define PIN_WO5      PIN_PA5
// #define PIN_WO6      PIN_PA6
// #define PIN_WO7      PIN_PA7
#define PIN_WO0_ALT2 PIN_PC0
#define PIN_WO1_ALT2 PIN_PC1
#define PIN_WO2_ALT2 PIN_PC2
#define PIN_WO3_ALT2 PIN_PC3
// #define PIN_WO0_ALT3 PIN_PD0
// #define PIN_WO1_ALT3 PIN_PD1
// #define PIN_WO2_ALT3 PIN_PD2
// #define PIN_WO3_ALT3 PIN_PD3
#define PIN_WO4_ALT3 PIN_PD4
#define PIN_WO5_ALT3 PIN_PD5
#define PIN_WO6_ALT3 PIN_PD6
#define PIN_WO7_ALT3 PIN_PD7
// #define PIN_WO0_ALT5 PIN_PF0
// #define PIN_WO1_ALT5 PIN_PF1
// #define PIN_WO2_ALT5 PIN_PF2
// #define PIN_WO3_ALT5 PIN_PF3
// #define PIN_WO4_ALT5 PIN_PF4
// #define PIN_WO5_ALT5 PIN_PF5
#define PIN_WO0_ALT8 PIN_PA0
#define PIN_WO1_ALT8 PIN_PA1
#define PIN_WO2_ALT8 PIN_PC0
#define PIN_WO3_ALT8 PIN_PC1
#define PIN_WO4_ALT8 PIN_PC2
#define PIN_WO5_ALT8 PIN_PC3
// #define PIN_WO0_ALT9 PIN_PA2
// #define PIN_WO1_ALT9 PIN_PA3
// #define PIN_WO2_ALT9 PIN_PA4
// #define PIN_WO3_ALT9 PIN_PA5
// #define PIN_WO4_ALT9 PIN_PA6
// #define PIN_WO5_ALT9 PIN_PA7

#define PIN_TCE0_WO0      PIN_PA0
#define PIN_TCE0_WO1      PIN_PA1
// #define PIN_TCE0_WO2      PIN_PA2
// #define PIN_TCE0_WO3      PIN_PA3
// #define PIN_TCE0_WO4      PIN_PA4
// #define PIN_TCE0_WO5      PIN_PA5
// #define PIN_TCE0_WO6      PIN_PA6
// #define PIN_TCE0_WO7      PIN_PA7
#define PIN_TCE0_WO0_ALT2 PIN_PC0
#define PIN_TCE0_WO1_ALT2 PIN_PC1
#define PIN_TCE0_WO2_ALT2 PIN_PC2
#define PIN_TCE0_WO3_ALT2 PIN_PC3
// #define PIN_TCE0_WO0_ALT3 PIN_PD0
// #define PIN_TCE0_WO1_ALT3 PIN_PD1
// #define PIN_TCE0_WO2_ALT3 PIN_PD2
// #define PIN_TCE0_WO3_ALT3 PIN_PD3
#define PIN_TCE0_WO4_ALT3 PIN_PD4
#define PIN_TCE0_WO5_ALT3 PIN_PD5
#define PIN_TCE0_WO6_ALT3 PIN_PD6
#define PIN_TCE0_WO7_ALT3 PIN_PD7
// #define PIN_TCE0_WO0_ALT5 PIN_PF0
// #define PIN_TCE0_WO1_ALT5 PIN_PF1
// #define PIN_TCE0_WO2_ALT5 PIN_PF2
// #define PIN_TCE0_WO3_ALT5 PIN_PF3
// #define PIN_TCE0_WO4_ALT5 PIN_PF4
// #define PIN_TCE0_WO5_ALT5 PIN_PF5
#define PIN_TCE0_WO0_ALT8 PIN_PA0
#define PIN_TCE0_WO1_ALT8 PIN_PA1
#define PIN_TCE0_WO2_ALT8 PIN_PC0
#define PIN_TCE0_WO3_ALT8 PIN_PC1
#define PIN_TCE0_WO4_ALT8 PIN_PC2
#define PIN_TCE0_WO5_ALT8 PIN_PC3
// #define PIN_TCE0_WO0_ALT9 PIN_PA2
// #define PIN_TCE0_WO1_ALT9 PIN_PA3
// #define PIN_TCE0_WO2_ALT9 PIN_PA4
// #define PIN_TCE0_WO3_ALT9 PIN_PA5
// #define PIN_TCE0_WO4_ALT9 PIN_PA6
// #define PIN_TCE0_WO5_ALT9 PIN_PA7

// #define PIN_TCB0_WO       PIN_PA2
// #define PIN_TCB1_WO       PIN_PA3
// #define PIN_TCB0_WO_ALT1  PIN_PF4
// #define PIN_TCB1_WO_ALT1  PIN_PF5

#define PIN_TCF0_WO0      PIN_PA0
#define PIN_TCF0_WO1      PIN_PA1
// #define PIN_TCF0_WO0_ALT1 PIN_PA6
// #define PIN_TCF0_WO1_ALT1 PIN_PA7
// #define PIN_TCF0_WO0_ALT2 PIN_PF4
// #define PIN_TCF0_WO1_ALT2 PIN_PF5

/* peripheral ports */

// #define PIN_AC1_AINP5     PIN_PA6
// #define PIN_AC0_OUT       PIN_PA7
// #define PIN_AC1_AINP6     PIN_PA7
// #define PIN_AC1_OUT       PIN_PA7
#define PIN_AC0_AINN3     PIN_PC2
#define PIN_AC1_AINN3     PIN_PC2
#define PIN_AC0_AINP4     PIN_PC3
#define PIN_AC1_AINP4     PIN_PC3
// #define PIN_AC0_AINN1     PIN_PD0
// #define PIN_AC1_AINN1     PIN_PD0
// #define PIN_AC0_AINP0     PIN_PD2
// #define PIN_AC1_AINP0     PIN_PD2
// #define PIN_AC0_AINN0     PIN_PD3
// #define PIN_AC1_AINP1     PIN_PD3
#define PIN_AC0_AINP5     PIN_PD4
#define PIN_AC1_AINP2     PIN_PD4
#define PIN_AC0_AINP6     PIN_PD5
#define PIN_AC1_AINN0     PIN_PD5
#define PIN_AC0_AINP3     PIN_PD6
#define PIN_AC1_AINP3     PIN_PD6
#define PIN_AC0_AINN2     PIN_PD7
#define PIN_AC1_AINN2     PIN_PD7

// #define PIN_ADC0_AIN22    PIN_PA2
// #define PIN_ADC0_AIN23    PIN_PA3
// #define PIN_ADC0_AIN24    PIN_PA4
// #define PIN_ADC0_AIN25    PIN_PA5
// #define PIN_ADC0_AIN26    PIN_PA6
// #define PIN_ADC0_AIN27    PIN_PA7
#define PIN_ADC0_AIN28    PIN_PC0
#define PIN_ADC0_AIN29    PIN_PC1
#define PIN_ADC0_AIN30    PIN_PC2
#define PIN_ADC0_AIN31    PIN_PC3
// #define PIN_ADC0_AIN0     PIN_PD0
// #define PIN_ADC0_AIN1     PIN_PD1
// #define PIN_ADC0_AIN2     PIN_PD2
// #define PIN_ADC0_AIN3     PIN_PD3
#define PIN_ADC0_AIN4     PIN_PD4
#define PIN_ADC0_AIN5     PIN_PD5
#define PIN_ADC0_AIN6     PIN_PD6
#define PIN_ADC0_AIN7     PIN_PD7
// #define PIN_ADC0_AIN16    PIN_PF0
// #define PIN_ADC0_AIN17    PIN_PF1
// #define PIN_ADC0_AIN18    PIN_PF2
// #define PIN_ADC0_AIN19    PIN_PF3
// #define PIN_ADC0_AIN20    PIN_PF4
// #define PIN_ADC0_AIN21    PIN_PF5

// #define PIN_EVOUTA        PIN_PA2
// #define PIN_EVOUTA_ALT1   PIN_PA7
#define PIN_EVOUTC        PIN_PC2
// #define PIN_EVOUTD        PIN_PD2
#define PIN_EVOUTD_ALT1   PIN_PD7
// #define PIN_EVOUTF        PIN_PF2
#define PIN_EVOUTF_ALT1   PIN_PF7

#define PIN_LUT0_IN0      PIN_PA0
#define PIN_LUT0_IN1      PIN_PA1
// #define PIN_LUT0_IN2      PIN_PA2
// #define PIN_LUT0_OUT      PIN_PA3
// #define PIN_LUT0_OUT_ALT1 PIN_PA6
#define PIN_LUT1_IN0      PIN_PC0
#define PIN_LUT1_IN1      PIN_PC1
#define PIN_LUT1_IN2      PIN_PC2
#define PIN_LUT1_OUT      PIN_PC3
// #define PIN_LUT2_IN0      PIN_PD0
// #define PIN_LUT2_IN1      PIN_PD1
// #define PIN_LUT2_IN2      PIN_PD2
// #define PIN_LUT2_OUT      PIN_PD3
#define PIN_LUT2_OUT_ALT1 PIN_PD6
// #define PIN_LUT3_IN0      PIN_PF0
// #define PIN_LUT3_IN1      PIN_PF1
// #define PIN_LUT3_IN2      PIN_PF2
// #define PIN_LUT3_OUT      PIN_PF3

// #define PIN_SPI0_MOSI        PIN_PA4
// #define PIN_SPI0_MISO        PIN_PA5
// #define PIN_SPI0_SCK         PIN_PA6
// #define PIN_SPI0_SS          PIN_PA7
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

// #define PIN_TWI0_SCL         PIN_PA2
// #define PIN_TWI0_SDA         PIN_PA3
#define PIN_TWI0_SCL_ALT2    PIN_PC2
#define PIN_TWI0_SDA_ALT2    PIN_PC3
#define PIN_TWI0_SCL_ALT3    PIN_PA0
#define PIN_TWI0_SDA_ALT3    PIN_PA1
#define PIN_TWI0S_SCL        PIN_PC2
#define PIN_TWI0S_SDA        PIN_PC3
#define PIN_TWI0S_SCL_ALT3   PIN_PC2
#define PIN_TWI0S_SDA_ALT3   PIN_PC3

#define PIN_USART0_TXD       PIN_PA0
#define PIN_USART0_RXD       PIN_PA1
// #define PIN_USART0_XCK       PIN_PA2
// #define PIN_USART0_XDIR      PIN_PA3
// #define PIN_USART0_TXD_ALT1  PIN_PA4
// #define PIN_USART0_RXD_ALT1  PIN_PA5
// #define PIN_USART0_XCK_ALT1  PIN_PA6
// #define PIN_USART0_XDIR_ALT1 PIN_PA7
// #define PIN_USART0_TXD_ALT2  PIN_PA2
// #define PIN_USART0_RXD_ALT2  PIN_PA3
#define PIN_USART0_TXD_ALT3  PIN_PD4
#define PIN_USART0_RXD_ALT3  PIN_PD5
#define PIN_USART0_XCK_ALT3  PIN_PD6
#define PIN_USART0_XDIR_ALT3 PIN_PD7
#define PIN_USART0_TXD_ALT4  PIN_PC1
#define PIN_USART0_RXD_ALT4  PIN_PC2
#define PIN_USART0_XCK_ALT4  PIN_PC3
#define PIN_USART0_TXD_ALT6  PIN_PF7
#define PIN_USART0_RXD_ALT6  PIN_PF6

/* peripheral symbols */

#define HAVE_AC0               AC0_AC_vect_num
#define HAVE_AC1               AC1_AC_vect_num
#define HAVE_ADC0         ADC0_RESRDY_vect_num
#define HAVE_BOD              BOD_VLM_vect_num
#define HAVE_CCL              CCL_CCL_vect_num
#define HAVE_NMI                  NMI_vect_num
#define HAVE_NVMCTRL  NVMCTRL_EEREADY_vect_num
#define HAVE_PIT              RTC_PIT_vect_num
#define HAVE_PORTA         PORTA_PORT_vect_num
#define HAVE_PORTC         PORTC_PORT_vect_num
#define HAVE_PORTD         PORTD_PORT_vect_num
#define HAVE_PORTF         PORTF_PORT_vect_num
#define HAVE_RTC              RTC_CNT_vect_num
#define HAVE_SPI0            SPI0_INT_vect_num
#define HAVE_TCB0            TCB0_INT_vect_num
#define HAVE_TCB1            TCB1_INT_vect_num
#define HAVE_TCE0            TCE0_OVF_vect_num
#define HAVE_TCF0            TCF0_INT_vect_num
#define HAVE_TWI0           TWI0_TWIS_vect_num
#define HAVE_USART0        USART0_RXC_vect_num
#define HAVE_WEX0          WEX0_FAULT_vect_num

// #define NMI_vect_num               1
// #define BOD_VLM_vect_num           2
// #define RTC_CNT_vect_num           3
// #define RTC_PIT_vect_num           4
// #define CCL_CCL_vect_num           5
// #define PORTA_PORT_vect_num        6
// #define WEX0_FAULT_vect_num        7
// #define TCE0_OVF_vect_num          8
// #define TCE0_CMP0_vect_num         9
// #define TCE0_CMP1_vect_num         10
// #define TCE0_CMP2_vect_num         11
// #define TCE0_CMP3_vect_num         12
// #define TCB0_INT_vect_num          13
// #define TCB1_INT_vect_num          14
// #define TWI0_TWIS_vect_num         15
// #define TWI0_TWIM_vect_num         16
// #define SPI0_INT_vect_num          17
// #define USART0_RXC_vect_num        18
// #define USART0_DRE_vect_num        19
// #define USART0_TXC_vect_num        20
// #define PORTD_PORT_vect_num        21
// #define TCF0_INT_vect_num          22
// #define AC0_AC_vect_num            23
// #define ADC0_ERROR_vect_num        24
// #define ADC0_RESRDY_vect_num       25
// #define ADC0_SAMPRDY_vect_num      26
// #define AC1_AC_vect_num            27
// #define PORTC_PORT_vect_num        28
// #define PORTF_PORT_vect_num        29
// #define NVMCTRL_EEREADY_vect_num   30
// #define NVMCTRL_FLREADY_vect_num   30
// #define NVMCTRL_NVMREADY_vect_num  30

/* build.console_select */

#ifndef ICSP_Serial
#define ICSP_Serial Serial0
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
  PORTA.PINCONFIG  = PORT_ISC_INPUT_DISABLE_gc;
  PORTA.PINCTRLUPD = ~0;
  PORTC.PINCTRLUPD = ~0;
  PORTD.PINCTRLUPD = ~0;
  PORTF.PINCTRLUPD = ~0;
  _CLKCTRL_SETUP();
}

#ifdef __cplusplus
} // extern "C"
#endif

// end of code
