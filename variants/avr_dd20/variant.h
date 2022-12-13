/**
 * @file variant.h
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2022
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
#define AVR_AVRDD     1
#define AVR_AVRDD20   1

//// Pin name to PORT configuration
////   bit[756] PORTA-G index position
////   bit[4]   1 (+16) (A=16,B=48,C=80,D=112,E=144,F=176,G=208)
////   bit[4]   0
////   bit[210] PIN0-7 bit position (0-7)

/* GPIO x17 (other VDD,GND,VDD2) */

#define PIN_PA0 16
#define PIN_PA1 17
#define PIN_PA2 18
#define PIN_PA3 19
#define PIN_PA4 20
#define PIN_PA5 21
#define PIN_PA6 22
#define PIN_PA7 23

/* PORTB not implemented */

#define PIN_PC0 80 /* used MVIOVDD */
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
#define PIN_PF6 182
#define PIN_PF7 183

/* PORTG not implemented */

#define NOT_A_PIN    255
#define PIN_MVIOVDD2 PIN_PC0
#define PIN_VREFA    PIN_PD7
#define PIN_RESET    PIN_PF6
#define PIN_UPDI     PIN_PF7

#ifndef LED_BUILTIN
#define LED_BUILTIN  PIN_PD5
#endif
#define LED_BUILTIN_INVERT  /* implementation dependent */

/* Timer Waveout signal */

#define PIN_WO0      PIN_PA0
#define PIN_WO1      PIN_PA1
#define PIN_WO2      PIN_PA2
#define PIN_WO3      PIN_PA3
#define PIN_WO4      PIN_PA4
#define PIN_WO5      PIN_PA5
#define PIN_WO6      PIN_PA6
#define PIN_WO7      PIN_PA7
#define PIN_WO0_ALT2 PIN_PC0
#define PIN_WO1_ALT2 PIN_PC1
#define PIN_WO2_ALT2 PIN_PC2
#define PIN_WO3_ALT2 PIN_PC3
#define PIN_WO4_ALT3 PIN_PD4
#define PIN_WO5_ALT3 PIN_PD5
#define PIN_TCA0_WO0      PIN_PA0
#define PIN_TCA0_WO1      PIN_PA1
#define PIN_TCA0_WO0_ALT2 PIN_PC0
#define PIN_TCA0_WO1_ALT2 PIN_PC1
#define PIN_TCA0_WO2_ALT2 PIN_PC2
#define PIN_TCA0_WO3_ALT2 PIN_PC3
#define PIN_TCA0_WO4_ALT3 PIN_PD4
#define PIN_TCA0_WO5_ALT3 PIN_PD5
#define PIN_TCB0_WO       PIN_PA2
#define PIN_TCB1_WO       PIN_PA3
#define PIN_TCD0_WOA      PIN_PA4
#define PIN_TCD0_WOB      PIN_PA5
#define PIN_TCD0_WOC      PIN_PA6
#define PIN_TCD0_WOD      PIN_PA7
#define PIN_TCD0_WOA_ALT4 PIN_PA4
#define PIN_TCD0_WOB_ALT4 PIN_PA5
#define PIN_TCD0_WOC_ALT4 PIN_PD4
#define PIN_TCD0_WOD_ALT4 PIN_PD5

/* peripheral ports */

#define PIN_AC0_OUT       PIN_PA7
#define PIN_AC0_AINP3     PIN_PD6
#define PIN_AC0_AINN2     PIN_PD7
#define PIN_AC0_AINN3     PIN_PC2
#define PIN_AC0_AINN4     PIN_PC3
#define PIN_ADC0_AIN4     PIN_PD4
#define PIN_ADC0_AIN5     PIN_PD5
#define PIN_ADC0_AIN6     PIN_PD6
#define PIN_ADC0_AIN7     PIN_PD7
#define PIN_ADC0_AIN22    PIN_PA2
#define PIN_ADC0_AIN23    PIN_PA3
#define PIN_ADC0_AIN24    PIN_PA4
#define PIN_ADC0_AIN25    PIN_PA5
#define PIN_ADC0_AIN26    PIN_PA6
#define PIN_ADC0_AIN27    PIN_PA7
#define PIN_ADC0_AIN29    PIN_PC1
#define PIN_ADC0_AIN30    PIN_PC2
#define PIN_ADC0_AIN31    PIN_PC3
#define PIN_DAC0_OUT      PIN_PD6
#define PIN_EVOUTA_ALT1   PIN_PA7
#define PIN_EVOUTC        PIN_PC2
#define PIN_EVOUTD_ALT1   PIN_PD7
#define PIN_EVOUTF_ALT1   PIN_PF7
#define PIN_LUT0_IN0      PIN_PA0
#define PIN_LUT0_IN1      PIN_PA1
#define PIN_LUT1_IN1      PIN_PC1
#define PIN_LUT1_IN2      PIN_PC2
#define PIN_LUT1_OUT      PIN_PC3
#define PIN_LUT2_OUT_ALT1 PIN_PD6
#define PIN_ZCD3_ZCIN     PIN_PC2
#define PIN_ZCD3_ZCOUT    PIN_PA7

#define PIN_SPI0_MOSI        PIN_PA4
#define PIN_SPI0_MISO        PIN_PA5
#define PIN_SPI0_SCK         PIN_PA6
#define PIN_SPI0_SS          PIN_PA7
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
#define PIN_TWI0S_SCL_ALT3   PIN_PC2
#define PIN_TWI0S_SDA_ALT3   PIN_PC3

#define PIN_USART0_TXD       PIN_PA0
#define PIN_USART0_RXD       PIN_PA1
#define PIN_USART0_TXD_ALT3  PIN_PD4
#define PIN_USART0_RXD_ALT3  PIN_PD5
#define PIN_USART0_XCK_ALT3  PIN_PD6
#define PIN_USART0_XDIR_ALT3 PIN_PD7
#define PIN_USART0_TXD_ALT4  PIN_PC1
#define PIN_USART0_RXD_ALT4  PIN_PC2
#define PIN_USART0_XCK_ALT4  PIN_PC3
#define PIN_USART1_RXD       PIN_PC1
#define PIN_USART1_XCK       PIN_PC2
#define PIN_USART1_XDIR      PIN_PC3
#define PIN_USART1_TXD_ALT2  PIN_PD6
#define PIN_USART1_RXD_ALT2  PIN_PD7

/* peripheral symbols */

#define HAVE_AC0           AC0_AC_vect_num
#define HAVE_ADC0     ADC0_RESRDY_vect_num
#define HAVE_BOD          BOD_VLM_vect_num
#define HAVE_CCL          CCL_CCL_vect_num
#define HAVE_CLKCTR   CLKCTRL_CFD_vect_num
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
#define HAVE_SPI1        SPI1_INT_vect_num
#define HAVE_TCA0        TCA0_OVF_vect_num
#define HAVE_TCB0        TCB0_INT_vect_num
#define HAVE_TCB1        TCB1_INT_vect_num
#define HAVE_TCB2        TCB2_INT_vect_num
#define HAVE_TCD0        TCD0_OVF_vect_num
#define HAVE_TWI0       TWI0_TWIS_vect_num
#define HAVE_TWI1       TWI1_TWIS_vect_num
#define HAVE_USART0    USART0_RXC_vect_num
#define HAVE_USART1    USART1_RXC_vect_num
#define HAVE_ZCD3        ZCD3_ZCD_vect_num

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
  PORTA.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc;
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
