/**
 * @file variant.h
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2022-12-12
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
#define AVR_AVRDX     1
#define AVR_AVRDA     1
#define AVR_AVRDA48   1
#define AVR_NVMCTRL   2
#define AVR_EVSYS   201

//// Pin name to PORT configuration
////   bit[765] PORTA-G index position
////   bit[4]   1 (+16) (A=16,B=48,C=80,D=112,E=144,F=176,G=208)
////   bit[3]   0
////   bit[210] PIN0-7 bit position (0-7)

/* GPIO x41 (other VDD,GND,AVDD,GND,UPDI,VDD2) */

#define PIN_PA0 16
#define PIN_PA1 17
#define PIN_PA2 18
#define PIN_PA3 19
#define PIN_PA4 20
#define PIN_PA5 21
#define PIN_PA6 22
#define PIN_PA7 23

#define PIN_PB0 48
#define PIN_PB1 49
#define PIN_PB2 50
#define PIN_PB3 51
#define PIN_PB4 52
#define PIN_PB5 53
/*      PIN_PB6 not implemented */
/*      PIN_PB7 not implemented */

#define PIN_PC0 80
#define PIN_PC1 81
#define PIN_PC2 82
#define PIN_PC3 83
#define PIN_PC4 84
#define PIN_PC5 85
#define PIN_PC6 86
#define PIN_PC7 87

#define PIN_PD0 112
#define PIN_PD1 113
#define PIN_PD2 114
#define PIN_PD3 115
#define PIN_PD4 116
#define PIN_PD5 117
#define PIN_PD6 118
#define PIN_PD7 119

#define PIN_PE0 144
#define PIN_PE1 145
#define PIN_PE2 146
#define PIN_PE3 147
/*      PIN_PE4 not implemented */
/*      PIN_PE5 not implemented */
/*      PIN_PE6 not implemented */
/*      PIN_PE7 not implemented */

#define PIN_PF0 176
#define PIN_PF1 177
#define PIN_PF2 178
#define PIN_PF3 179
#define PIN_PF4 180
#define PIN_PF5 181
#define PIN_PF6 182
/*      PIN_PF7 not implemented */

/* PORTG not implemented */

#define NOT_A_PIN    255
#define PIN_VREFA    PIN_PD7
#define PIN_RESET    PIN_PF6

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

#define PIN_WO0_ALT1 PIN_PB0
#define PIN_WO1_ALT1 PIN_PB1
#define PIN_WO2_ALT1 PIN_PB2
#define PIN_WO3_ALT1 PIN_PB3
#define PIN_WO4_ALT1 PIN_PB4
#define PIN_WO5_ALT1 PIN_PB5

#define PIN_WO0_ALT2 PIN_PC0
#define PIN_WO1_ALT2 PIN_PC1
#define PIN_WO2_ALT2 PIN_PC2
#define PIN_WO3_ALT2 PIN_PC3
#define PIN_WO4_ALT2 PIN_PC4
#define PIN_WO5_ALT2 PIN_PC5

#define PIN_WO0_ALT3 PIN_PD0
#define PIN_WO1_ALT3 PIN_PD1
#define PIN_WO2_ALT3 PIN_PD2
#define PIN_WO3_ALT3 PIN_PD3
#define PIN_WO4_ALT3 PIN_PD4
#define PIN_WO5_ALT3 PIN_PD5

#define PIN_WO0_ALT4 PIN_PE0
#define PIN_WO1_ALT4 PIN_PE1
#define PIN_WO2_ALT4 PIN_PE2
#define PIN_WO3_ALT4 PIN_PE3
// #define PIN_WO4_ALT4 PIN_PE4
// #define PIN_WO5_ALT4 PIN_PE5

#define PIN_WO0_ALT5 PIN_PF0
#define PIN_WO1_ALT5 PIN_PF1
#define PIN_WO2_ALT5 PIN_PF2
#define PIN_WO3_ALT5 PIN_PF3
#define PIN_WO4_ALT5 PIN_PF4
#define PIN_WO5_ALT5 PIN_PF5

// #define PIN_WO0_ALT6 PIN_PG0
// #define PIN_WO1_ALT6 PIN_PG1
// #define PIN_WO2_ALT6 PIN_PG2
// #define PIN_WO3_ALT6 PIN_PG3
// #define PIN_WO4_ALT6 PIN_PG4
// #define PIN_WO5_ALT6 PIN_PG5

#define PIN_TCA0_WO0      PIN_PA0
#define PIN_TCA0_WO1      PIN_PA1
#define PIN_TCA0_WO2      PIN_PA2
#define PIN_TCA0_WO3      PIN_PA3
#define PIN_TCA0_WO4      PIN_PA4
#define PIN_TCA0_WO5      PIN_PA5

#define PIN_TCA0_WO0_ALT1 PIN_PB0
#define PIN_TCA0_WO1_ALT1 PIN_PB1
#define PIN_TCA0_WO2_ALT1 PIN_PB2
#define PIN_TCA0_WO3_ALT1 PIN_PB3
#define PIN_TCA0_WO4_ALT1 PIN_PB4
#define PIN_TCA0_WO5_ALT1 PIN_PB5

#define PIN_TCA0_WO0_ALT2 PIN_PC0
#define PIN_TCA0_WO1_ALT2 PIN_PC1
#define PIN_TCA0_WO2_ALT2 PIN_PC2
#define PIN_TCA0_WO3_ALT2 PIN_PC3
#define PIN_TCA0_WO4_ALT2 PIN_PC4
#define PIN_TCA0_WO5_ALT2 PIN_PC5

#define PIN_TCA0_WO0_ALT3 PIN_PD0
#define PIN_TCA0_WO1_ALT3 PIN_PD1
#define PIN_TCA0_WO2_ALT3 PIN_PD2
#define PIN_TCA0_WO3_ALT3 PIN_PD3
#define PIN_TCA0_WO4_ALT3 PIN_PD4
#define PIN_TCA0_WO5_ALT3 PIN_PD5

#define PIN_TCA0_WO0_ALT4 PIN_PE0
#define PIN_TCA0_WO1_ALT4 PIN_PE1
#define PIN_TCA0_WO2_ALT4 PIN_PE2
#define PIN_TCA0_WO3_ALT4 PIN_PE3
// #define PIN_TCA0_WO4_ALT4 PIN_PE4
// #define PIN_TCA0_WO5_ALT4 PIN_PE5

#define PIN_TCA0_WO0_ALT5 PIN_PF0
#define PIN_TCA0_WO1_ALT5 PIN_PF1
#define PIN_TCA0_WO2_ALT5 PIN_PF2
#define PIN_TCA0_WO3_ALT5 PIN_PF3
#define PIN_TCA0_WO4_ALT5 PIN_PF4
#define PIN_TCA0_WO5_ALT5 PIN_PF5

// #define PIN_TCA0_WO0_ALT6 PIN_PG0
// #define PIN_TCA0_WO1_ALT6 PIN_PG1
// #define PIN_TCA0_WO2_ALT6 PIN_PG2
// #define PIN_TCA0_WO3_ALT6 PIN_PG3
// #define PIN_TCA0_WO4_ALT6 PIN_PG4
// #define PIN_TCA0_WO5_ALT6 PIN_PG5

#define PIN_TCA1_WO0      PIN_PB0
#define PIN_TCA1_WO1      PIN_PB1
#define PIN_TCA1_WO2      PIN_PB2
#define PIN_TCA1_WO3      PIN_PB3
#define PIN_TCA1_WO4      PIN_PB4
#define PIN_TCA1_WO5      PIN_PB5

#define PIN_TCA1_WO0_ALT1 PIN_PC4
#define PIN_TCA1_WO1_ALT1 PIN_PC5
#define PIN_TCA1_WO2_ALT1 PIN_PC6

// #define PIN_TCA1_WO0_ALT2 PIN_PE4
// #define PIN_TCA1_WO1_ALT2 PIN_PE5
// #define PIN_TCA1_WO2_ALT2 PIN_PE6

// #define PIN_TCA1_WO0_ALT3 PIN_PG0
// #define PIN_TCA1_WO1_ALT3 PIN_PG1
// #define PIN_TCA1_WO2_ALT3 PIN_PG2
// #define PIN_TCA1_WO3_ALT3 PIN_PG3
// #define PIN_TCA1_WO4_ALT3 PIN_PG4
// #define PIN_TCA1_WO5_ALT3 PIN_PG5

#define PIN_TCB0_WO       PIN_PA2
#define PIN_TCB1_WO       PIN_PA3
#define PIN_TCB2_WO       PIN_PC0
#define PIN_TCB3_WO       PIN_PB5
// #define PIN_TCB4_WO       PIN_PG3

#define PIN_TCB0_WO_ALT1  PIN_PF4
#define PIN_TCB1_WO_ALT1  PIN_PF5
#define PIN_TCB2_WO_ALT1  PIN_PB4
#define PIN_TCB3_WO_ALT1  PIN_PC1
#define PIN_TCB4_WO_ALT1  PIN_PC6

#define PIN_TCD0_WOA      PIN_PA4
#define PIN_TCD0_WOB      PIN_PA5
#define PIN_TCD0_WOC      PIN_PA6
#define PIN_TCD0_WOD      PIN_PA7

#define PIN_TCD0_WOA_ALT1 PIN_PB4
#define PIN_TCD0_WOB_ALT1 PIN_PB5
// #define PIN_TCD0_WOC_ALT1 PIN_PB6
// #define PIN_TCD0_WOD_ALT1 PIN_PB7

#define PIN_TCD0_WOA_ALT2 PIN_PF0
#define PIN_TCD0_WOB_ALT2 PIN_PF1
#define PIN_TCD0_WOC_ALT2 PIN_PF2
#define PIN_TCD0_WOD_ALT2 PIN_PF3

// #define PIN_TCD0_WOA_ALT3 PIN_PG4
// #define PIN_TCD0_WOB_ALT3 PIN_PG5
// #define PIN_TCD0_WOC_ALT3 PIN_PG6
// #define PIN_TCD0_WOD_ALT3 PIN_PG7

/* peripheral ports */

#define PIN_AC0_OUT       PIN_PA7
#define PIN_AC0_AINN1     PIN_PD0
#define PIN_AC0_AINP0     PIN_PD2
#define PIN_AC0_AINN0     PIN_PD3
#define PIN_AC0_AINP3     PIN_PD6
#define PIN_AC0_AINN2     PIN_PD7

#define PIN_AC1_OUT       PIN_PA7
#define PIN_AC1_AINN1     PIN_PD0
#define PIN_AC1_AINP0     PIN_PD2
#define PIN_AC1_AINP1     PIN_PD3
#define PIN_AC1_AINP2     PIN_PD4
#define PIN_AC1_AINN0     PIN_PD5
#define PIN_AC1_AINP3     PIN_PD6
#define PIN_AC1_AINN2     PIN_PD7

#define PIN_AC2_OUT       PIN_PA7
#define PIN_AC2_AINN1     PIN_PD0
#define PIN_AC2_AINP0     PIN_PD2
#define PIN_AC2_AINP1     PIN_PD4
#define PIN_AC2_AINP3     PIN_PD6
#define PIN_AC2_AINN0     PIN_PD7
#define PIN_AC2_AINN2     PIN_PD7

#define PIN_ADC0_AIN0     PIN_PD0
#define PIN_ADC0_AIN1     PIN_PD1
#define PIN_ADC0_AIN2     PIN_PD2
#define PIN_ADC0_AIN3     PIN_PD3
#define PIN_ADC0_AIN4     PIN_PD4
#define PIN_ADC0_AIN5     PIN_PD5
#define PIN_ADC0_AIN6     PIN_PD6
#define PIN_ADC0_AIN7     PIN_PD7
#define PIN_ADC0_AIN16    PIN_PF0
#define PIN_ADC0_AIN17    PIN_PF1
#define PIN_ADC0_AIN18    PIN_PF2
#define PIN_ADC0_AIN19    PIN_PF3
#define PIN_ADC0_AIN20    PIN_PF4
#define PIN_ADC0_AIN21    PIN_PF5

#define PIN_DAC0_OUT      PIN_PD2

#define PIN_EVOUTA        PIN_PA2
#define PIN_EVOUTA_ALT1   PIN_PA7
#define PIN_EVOUTB        PIN_PB2
// #define PIN_EVOUTB_ALT1   PIN_PB7
#define PIN_EVOUTC        PIN_PC2
#define PIN_EVOUTC_ALT1   PIN_PC7
#define PIN_EVOUTD        PIN_PD2
#define PIN_EVOUTD_ALT1   PIN_PD7
#define PIN_EVOUTE        PIN_PE2
#define PIN_EVOUTE_ALT1   PIN_PE7
#define PIN_EVOUTF        PIN_PF2
// #define PIN_EVOUTG        PIN_PG2
// #define PIN_EVOUTG_ALT1   PIN_PG7

#define PIN_LUT0_IN0      PIN_PA0
#define PIN_LUT0_IN1      PIN_PA1
#define PIN_LUT0_IN2      PIN_PA2
#define PIN_LUT0_OUT      PIN_PA3
#define PIN_LUT0_OUT_ALT1 PIN_PA6
#define PIN_LUT1_IN0      PIN_PC0
#define PIN_LUT1_IN1      PIN_PC1
#define PIN_LUT1_IN2      PIN_PC2
#define PIN_LUT1_OUT      PIN_PC3
#define PIN_LUT2_IN0      PIN_PD0
#define PIN_LUT2_IN1      PIN_PD1
#define PIN_LUT2_IN2      PIN_PD2
#define PIN_LUT2_OUT      PIN_PD3
#define PIN_LUT2_OUT_ALT1 PIN_PD6
#define PIN_LUT3_IN0      PIN_PF0
#define PIN_LUT3_IN1      PIN_PF1
#define PIN_LUT3_IN2      PIN_PF2
#define PIN_LUT3_OUT      PIN_PF3
#define PIN_LUT4_IN0      PIN_PB0
#define PIN_LUT4_IN1      PIN_PB1
#define PIN_LUT4_IN2      PIN_PB2
#define PIN_LUT4_OUT      PIN_PB3
// #define PIN_LUT4_OUT_ALT1 PIN_PB6
// #define PIN_LUT5_IN0      PIN_PG0
// #define PIN_LUT5_IN1      PIN_PG1
// #define PIN_LUT5_IN2      PIN_PG2
// #define PIN_LUT5_OUT      PIN_PG3
// #define PIN_LUT5_OUT_ALT1 PIN_PG6

#define PIN_ZCD0_ZCIN        PIN_PD1
#define PIN_ZCD1_ZCIN        PIN_PE3
#define PIN_ZCD2_ZCIN        PIN_PE7
#define PIN_ZCD0_ZCOUT       PIN_PA7
#define PIN_ZCD1_ZCOUT       PIN_PA7
#define PIN_ZCD2_ZCOUT       PIN_PA7
#define PIN_ZCD0_ZCOUT_ALT1  PIN_PC7
#define PIN_ZCD1_ZCOUT_ALT1  PIN_PC7
#define PIN_ZCD2_ZCOUT_ALT1  PIN_PC7

#define PIN_SPI0_MOSI        PIN_PA4
#define PIN_SPI0_MISO        PIN_PA5
#define PIN_SPI0_SCK         PIN_PA6
#define PIN_SPI0_SS          PIN_PA7
#define PIN_SPI0_MOSI_ALT1   PIN_PE0
#define PIN_SPI0_MISO_ALT1   PIN_PE1
#define PIN_SPI0_SCK_ALT1    PIN_PE2
#define PIN_SPI0_SS_ALT1     PIN_PE3
// #define PIN_SPI0_MOSI_ALT2   PIN_PG4
// #define PIN_SPI0_MISO_ALT2   PIN_PG5
// #define PIN_SPI0_SCK_ALT2    PIN_PG6
// #define PIN_SPI0_SS_ALT2     PIN_PG7
#define PIN_SPI1_MOSI        PIN_PC0
#define PIN_SPI1_MISO        PIN_PC1
#define PIN_SPI1_SCK         PIN_PC2
#define PIN_SPI1_SS          PIN_PC3
#define PIN_SPI1_MOSI_ALT1   PIN_PC4
#define PIN_SPI1_MISO_ALT1   PIN_PC5
#define PIN_SPI1_SCK_ALT1    PIN_PC6
#define PIN_SPI1_SS_ALT1     PIN_PC7
#define PIN_SPI1_MOSI_ALT2   PIN_PB4
#define PIN_SPI1_MISO_ALT2   PIN_PB5
// #define PIN_SPI1_SCK_ALT2    PIN_PB6
// #define PIN_SPI1_SS_ALT2     PIN_PB7

#define PIN_TWI0_SCL         PIN_PA2
#define PIN_TWI0_SDA         PIN_PA3
#define PIN_TWI0_SCL_ALT1    PIN_PA2
#define PIN_TWI0_SDA_ALT1    PIN_PA3
#define PIN_TWI0_SCL_ALT2    PIN_PC2
#define PIN_TWI0_SDA_ALT2    PIN_PC3
#define PIN_TWI0S_SCL        PIN_PC2
#define PIN_TWI0S_SDA        PIN_PC3
#define PIN_TWI0S_SCL_ALT2   PIN_PC6
#define PIN_TWI0S_SDA_ALT2   PIN_PC7
#define PIN_TWI0S_SCL_ALT2   PIN_PC6
#define PIN_TWI0S_SDA_ALT2   PIN_PC7
#define PIN_TWI1_SCL         PIN_PF2
#define PIN_TWI1_SDA         PIN_PF3
#define PIN_TWI1_SCL_ALT1    PIN_PF2
#define PIN_TWI1_SDA_ALT1    PIN_PF3
#define PIN_TWI1_SCL_ALT2    PIN_PB2
#define PIN_TWI1_SDA_ALT2    PIN_PB3
#define PIN_TWI1S_SCL        PIN_PB2
#define PIN_TWI1S_SDA        PIN_PB3
// #define PIN_TWI1S_SCL_ALT2   PIN_PB6
// #define PIN_TWI1S_SDA_ALT2   PIN_PB7
// #define PIN_TWI1S_SCL_ALT2   PIN_PB6
// #define PIN_TWI1S_SDA_ALT2   PIN_PB7

#define PIN_USART0_TXD       PIN_PA0
#define PIN_USART0_RXD       PIN_PA1
#define PIN_USART0_XCK       PIN_PA2
#define PIN_USART0_XDIR      PIN_PA3
#define PIN_USART0_TXD_ALT1  PIN_PA4
#define PIN_USART0_RXD_ALT1  PIN_PA5
#define PIN_USART0_XCK_ALT1  PIN_PA6
#define PIN_USART0_XDIR_ALT1 PIN_PA7
#define PIN_USART1_TXD       PIN_PC0
#define PIN_USART1_RXD       PIN_PC1
#define PIN_USART1_XCK       PIN_PC2
#define PIN_USART1_XDIR      PIN_PC3
#define PIN_USART1_TXD_ALT1  PIN_PC4
#define PIN_USART1_RXD_ALT1  PIN_PC5
#define PIN_USART1_XCK_ALT1  PIN_PC6
#define PIN_USART1_XDIR_ALT1 PIN_PC7
#define PIN_USART2_TXD       PIN_PF0
#define PIN_USART2_RXD       PIN_PF1
#define PIN_USART2_XCK       PIN_PF2
#define PIN_USART2_XDIR      PIN_PF3
#define PIN_USART2_TXD_ALT1  PIN_PF4
#define PIN_USART2_RXD_ALT1  PIN_PF5
#define PIN_USART3_TXD       PIN_PB0
#define PIN_USART3_RXD       PIN_PB1
#define PIN_USART3_XCK       PIN_PB2
#define PIN_USART3_XDIR      PIN_PB3
#define PIN_USART3_TXD_ALT1  PIN_PB4
#define PIN_USART3_RXD_ALT1  PIN_PB5
// #define PIN_USART3_XCK_ALT1  PIN_PB6
// #define PIN_USART3_XDIR_ALT1 PIN_PB7
#define PIN_USART4_TXD       PIN_PE0
#define PIN_USART4_RXD       PIN_PE1
#define PIN_USART4_XCK       PIN_PE2
#define PIN_USART4_XDIR      PIN_PE3
// #define PIN_USART4_TXD_ALT1  PIN_PE4
// #define PIN_USART4_RXD_ALT1  PIN_PE5
// #define PIN_USART4_XCK_ALT1  PIN_PE6
// #define PIN_USART4_XDIR_ALT1 PIN_PE7
// #define PIN_USART5_TXD       PIN_PG0
// #define PIN_USART5_RXD       PIN_PG1
// #define PIN_USART5_XCK       PIN_PG2
// #define PIN_USART5_XDIR      PIN_PG3
// #define PIN_USART5_TXD_ALT1  PIN_PG4
// #define PIN_USART5_RXD_ALT1  PIN_PG5
// #define PIN_USART5_XCK_ALT1  PIN_PG6
// #define PIN_USART5_XDIR_ALT1 PIN_PG7

#define PIN_PTC_XY0   PIN_PA0
#define PIN_PTC_XY1   PIN_PA1
#define PIN_PTC_XY2   PIN_PA2
#define PIN_PTC_XY3   PIN_PA3
#define PIN_PTC_XY4   PIN_PA4
#define PIN_PTC_XY5   PIN_PA5
#define PIN_PTC_XY6   PIN_PA6
#define PIN_PTC_XY7   PIN_PA7
#define PIN_PTC_XY8   PIN_PB0
#define PIN_PTC_XY9   PIN_PB1
#define PIN_PTC_XY10  PIN_PB2
#define PIN_PTC_XY11  PIN_PB3
#define PIN_PTC_XY12  PIN_PB4
#define PIN_PTC_XY13  PIN_PB5
// #define PIN_PTC_XY14  PIN_PB6
// #define PIN_PTC_XY15  PIN_PB7
#define PIN_PTC_XY16  PIN_PD0
#define PIN_PTC_XY17  PIN_PD1
#define PIN_PTC_XY18  PIN_PD2
#define PIN_PTC_XY19  PIN_PD3
#define PIN_PTC_XY20  PIN_PD4
#define PIN_PTC_XY21  PIN_PD5
#define PIN_PTC_XY22  PIN_PD6
#define PIN_PTC_XY23  PIN_PD7
#define PIN_PTC_XY24  PIN_PE0
#define PIN_PTC_XY25  PIN_PE1
#define PIN_PTC_XY26  PIN_PE2
#define PIN_PTC_XY27  PIN_PE3
// #define PIN_PTC_XY28  PIN_PE4
// #define PIN_PTC_XY29  PIN_PE5
// #define PIN_PTC_XY30  PIN_PE6
// #define PIN_PTC_XY31  PIN_PE7
#define PIN_PTC_XY32  PIN_PF0
#define PIN_PTC_XY33  PIN_PF1
#define PIN_PTC_XY34  PIN_PF2
#define PIN_PTC_XY35  PIN_PF3
#define PIN_PTC_XY36  PIN_PF4
#define PIN_PTC_XY37  PIN_PF5
// #define PIN_PTC_XY40  PIN_PG0
// #define PIN_PTC_XY41  PIN_PG1
// #define PIN_PTC_XY42  PIN_PG2
// #define PIN_PTC_XY43  PIN_PG3
// #define PIN_PTC_XY44  PIN_PG4
// #define PIN_PTC_XY45  PIN_PG5
// #define PIN_PTC_XY46  PIN_PG6
// #define PIN_PTC_XY47  PIN_PG7

/* peripheral symbols */

#define HAVE_AC0           AC0_AC_vect_num
#define HAVE_AC1           AC1_AC_vect_num
#define HAVE_AC2           AC2_AC_vect_num
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
// #define HAVE_PORTG     PORTG_PORT_vect_num
#define HAVE_RTC          RTC_CNT_vect_num
#define HAVE_SPI0        SPI0_INT_vect_num
#define HAVE_SPI1        SPI1_INT_vect_num
#define HAVE_TCA0       TCA0_LUNF_vect_num
#define HAVE_TCA1       TCA1_LUNF_vect_num
#define HAVE_TCB0        TCB0_INT_vect_num
#define HAVE_TCB1        TCB1_INT_vect_num
#define HAVE_TCB2        TCB2_INT_vect_num
#define HAVE_TCB3        TCB3_INT_vect_num
#define HAVE_TCB4        TCB4_INT_vect_num
#define HAVE_TCD0        TCD0_OVF_vect_num
#define HAVE_TWI0       TWI0_TWIS_vect_num
#define HAVE_TWI1       TWI1_TWIS_vect_num
#define HAVE_USART0    USART0_RXC_vect_num
#define HAVE_USART1    USART1_RXC_vect_num
#define HAVE_USART2    USART2_RXC_vect_num
#define HAVE_USART3    USART3_RXC_vect_num
#define HAVE_USART4    USART4_RXC_vect_num
// #define HAVE_USART5    USART5_RXC_vect_num
#define HAVE_ZCD0        ZCD0_ZCD_vect_num
#define HAVE_ZCD1        ZCD1_ZCD_vect_num
#define HAVE_ZCD2        ZCD2_ZCD_vect_num

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
  PORTB.PINCTRLUPD = ~0;
  PORTC.PINCTRLUPD = ~0;
  PORTD.PINCTRLUPD = ~0;
  PORTE.PINCTRLUPD = ~0;
  PORTF.PINCTRLUPD = ~0;
  // PORTG.PINCTRLUPD = ~0;
}

#ifdef __cplusplus
} // extern "C"
#endif

// end of code
