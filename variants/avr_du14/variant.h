/**
 * @file variant.h
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2024-05-12
 *
 * @copyright Copyright (c) 2024 askn37 at github.com
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
#define AVR_AVRDX     1
#define AVR_AVRDU     1
#define AVR_AVRDU14   1
#define AVR_NVMCTRL   4
#define AVR_EVSYS   202

//// Pin name to PORT configuration
////   bit[765] PORTA-G index position
////   bit[4]   1 (+16) (A=16,B=48,C=80,D=112,E=144,F=176,G=208)
////   bit[3]   0
////   bit[210] PIN0-7 bit position (0-7)

/* GPIO x9 (other VDD,GND,VUSB,DM,DP) */

#define PIN_PA0 16
#define PIN_PA1 17
/*      PIN_PA2 not implemented */
/*      PIN_PA3 not implemented */
/*      PIN_PA4 not implemented */
/*      PIN_PA5 not implemented */
/*      PIN_PA6 not implemented */
/*      PIN_PA7 not implemented */

/* PORTB not implemented */

/*      PIN_PC0 not implemented */
/*      PIN_PC1 not implemented */
/*      PIN_PC2 not implemented */
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
#define PIN_PF6 182
#define PIN_PF7 183

/* PORTG not implemented */

#define NOT_A_PIN    255
#define PIN_VREFA    PIN_PD7
#define PIN_RESET    PIN_PF6
#define PIN_UPDI     PIN_PF7

#ifndef LED_BUILTIN
#define LED_BUILTIN  PIN_PD7
#endif
#define LED_BUILTIN_INVERT  /* implementation dependent */

/* Timer Waveout signal*/

#define PIN_WO0       PIN_PA0
#define PIN_WO1       PIN_PA1
// #define PIN_WO2       PIN_PA2
// #define PIN_WO3       PIN_PA3
// #define PIN_WO4       PIN_PA4
// #define PIN_WO5       PIN_PA5
// #define PIN_WO0_ALT_2 PIN_PC0
// #define PIN_WO1_ALT_2 PIN_PC1
// #define PIN_WO2_ALT_2 PIN_PC2
#define PIN_WO3_ALT_2 PIN_PC3
// #define PIN_WO0_ALT_3 PIN_PD0
// #define PIN_WO1_ALT_3 PIN_PD1
// #define PIN_WO2_ALT_3 PIN_PD2
// #define PIN_WO3_ALT_3 PIN_PD3
#define PIN_WO4_ALT_3 PIN_PD4
#define PIN_WO5_ALT_3 PIN_PD5
// #define PIN_WO0_ALT_5 PIN_PF0
// #define PIN_WO1_ALT_5 PIN_PF1
// #define PIN_WO2_ALT_5 PIN_PF2
// #define PIN_WO3_ALT_5 PIN_PF3
// #define PIN_WO4_ALT_5 PIN_PF4
// #define PIN_WO5_ALT_5 PIN_PF5
#define PIN_TCA0_WO0       PIN_PA0
#define PIN_TCA0_WO1       PIN_PA1
// #define PIN_TCA0_WO2       PIN_PA2
// #define PIN_TCA0_WO3       PIN_PA3
// #define PIN_TCA0_WO4       PIN_PA4
// #define PIN_TCA0_WO5       PIN_PA5
#define PIN_TCA0_WO3_ALT_2 PIN_PC3
// #define PIN_TCA0_WO0_ALT_3 PIN_PD0
// #define PIN_TCA0_WO1_ALT_3 PIN_PD1
// #define PIN_TCA0_WO2_ALT_3 PIN_PD2
// #define PIN_TCA0_WO3_ALT_3 PIN_PD3
#define PIN_TCA0_WO4_ALT_3 PIN_PD4
#define PIN_TCA0_WO5_ALT_3 PIN_PD5
// #define PIN_TCA0_WO0_ALT_5 PIN_PF0
// #define PIN_TCA0_WO1_ALT_5 PIN_PF1
// #define PIN_TCA0_WO2_ALT_5 PIN_PF2
// #define PIN_TCA0_WO3_ALT_5 PIN_PF3
// #define PIN_TCA0_WO4_ALT_5 PIN_PF4
// #define PIN_TCA0_WO5_ALT_5 PIN_PF5
// #define PIN_TCB0_WO       PIN_PA2
// #define PIN_TCB1_WO       PIN_PA3
// #define PIN_TCB0_WO_ALT_1 PIN_PF4
// #define PIN_TCB1_WO_ALT_1 PIN_PF5
// #define PIN_TCD0_WOA      PIN_PA4
// #define PIN_TCD0_WOB      PIN_PA5
// #define PIN_TCD0_WOC      PIN_PA6
// #define PIN_TCD0_WOD      PIN_PA7
// #define PIN_TCD0_WOA_ALT2 PIN_PF0
// #define PIN_TCD0_WOB_ALT2 PIN_PF1
// #define PIN_TCD0_WOC_ALT2 PIN_PF2
// #define PIN_TCD0_WOD_ALT2 PIN_PF3
// #define PIN_TCD0_WOA_ALT4 PIN_PA4
// #define PIN_TCD0_WOB_ALT4 PIN_PA5
#define PIN_TCD0_WOC_ALT4 PIN_PD4
#define PIN_TCD0_WOD_ALT4 PIN_PD5
// #define PIN_EVOUTA        PIN_PA2
// #define PIN_EVOUTA_ALT_1  PIN_PA7
// #define PIN_EVOUTD        PIN_PD2
#define PIN_EVOUTD_ALT_1  PIN_PD7
// #define PIN_EVOUTF        PIN_PF2
#define PIN_EVOUTF_ALT_1  PIN_PF7

/* peripheral ports */

// #define PIN_AC0_OUT       PIN_PA7
// #define PIN_AC0_AINP0     PIN_PD2
// #define PIN_AC0_AINN0     PIN_PD3
#define PIN_AC0_AINP3     PIN_PD6
#define PIN_AC0_AINN2     PIN_PD7
// #define PIN_AC0_AINN3     PIN_PC2
#define PIN_AC0_AINN4     PIN_PC3

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
// #define PIN_ADC0_AIN22    PIN_PA2
// #define PIN_ADC0_AIN23    PIN_PA3
// #define PIN_ADC0_AIN24    PIN_PA4
// #define PIN_ADC0_AIN25    PIN_PA5
// #define PIN_ADC0_AIN26    PIN_PA6
// #define PIN_ADC0_AIN27    PIN_PA7
// #define PIN_ADC0_AIN28    PIN_PC0
// #define PIN_ADC0_AIN29    PIN_PC1
// #define PIN_ADC0_AIN30    PIN_PC2
#define PIN_ADC0_AIN31    PIN_PC3

// #define PIN_DAC0_OUT      PIN_PD6

// #define PIN_EVOUTA_ALT1   PIN_PA7
#define PIN_EVOUTD_ALT1   PIN_PD7
#define PIN_EVOUTF_ALT1   PIN_PF7

#define PIN_LUT0_IN0      PIN_PA0
#define PIN_LUT0_IN1      PIN_PA1
// #define PIN_LUT0_IN2      PIN_PA2
// #define PIN_LUT0_OUT      PIN_PA3
// #define PIN_LUT0_OUT_ALT1 PIN_PA6
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
#define PIN_SPI0_MOSI_ALT4   PIN_PD4
#define PIN_SPI0_MISO_ALT4   PIN_PD5
#define PIN_SPI0_SCK_ALT4    PIN_PD6
#define PIN_SPI0_SS_ALT4     PIN_PD7
// #define PIN_TWI0_SCL         PIN_PA2
// #define PIN_TWI0_SDA         PIN_PA3
#define PIN_TWI0_SCL_ALT3    PIN_PA0
#define PIN_TWI0_SDA_ALT3    PIN_PA1

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
#define PIN_USART1_TXD_ALT2  PIN_PD6
#define PIN_USART1_RXD_ALT2  PIN_PD7

/* peripheral symbols */

#define HAVE_AC0           AC0_AC_vect_num
#define HAVE_ADC0     ADC0_RESRDY_vect_num
#define HAVE_BOD          BOD_VLM_vect_num
#define HAVE_CCL          CCL_CCL_vect_num
#define HAVE_CLKCTRL  CLKCTRL_CFD_vect_num
#define HAVE_MVIO       MVIO_MVIO_vect_num
#define HAVE_NMI              NMI_vect_num
#define HAVE_NVMCTRL   NVMCTRL_EE_vect_num
#define HAVE_PIT          RTC_PIT_vect_num
#define HAVE_PORTA     PORTA_PORT_vect_num
#define HAVE_PORTC     PORTC_PORT_vect_num
#define HAVE_PORTD     PORTD_PORT_vect_num
#define HAVE_PORTF     PORTF_PORT_vect_num
#define HAVE_RTC          RTC_CNT_vect_num
#define HAVE_SPI0        SPI0_INT_vect_num
#define HAVE_TCA0       TCA0_LUNF_vect_num
#define HAVE_TCB0        TCB0_INT_vect_num
#define HAVE_TCB1        TCB1_INT_vect_num
#define HAVE_TWI0       TWI0_TWIS_vect_num
#define HAVE_USART0    USART0_RXC_vect_num
#define HAVE_USART1    USART1_RXC_vect_num
#define HAVE_USB0   USB0_TRNCOMPL_vect_num

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
  _CLKCTRL_SETUP();
  PORTA.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc;
  PORTA.PINCTRLUPD = ~0;
  PORTC.PINCTRLUPD = ~0;
  PORTD.PINCTRLUPD = ~0;
  PORTF.PINCTRLUPD = ~0;
}

#ifdef __cplusplus
} // extern "C"
#endif

// end of code
