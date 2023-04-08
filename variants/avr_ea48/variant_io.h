/**
 * @file variant_io.h
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2023-04-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <avr/io.h>
#define AVR_MEGAAVR_LIKE_MODERNAVR

#define SLEEP_MODE_ADC      SLEEP_MODE_STANDBY

/* RS485 Mode internal transmitter select */
#define USART_RS485_EXT_gc  (0x01<<0)
#define USART_RS485_INT_gc  (0x02<<0)

#define USART_RS485_0_bm    (1<<0)  /* RS485 Mode internal transmitter bit 0 mask. */
#define USART_RS485_0_bp    0       /* RS485 Mode internal transmitter bit 0 position. */
#define USART_RS485_1_bm    (1<<1)  /* RS485 Mode internal transmitter bit 1 mask. */
#define USART_RS485_1_bp    1       /* RS485 Mode internal transmitter bit 1 position. */

/* Clock select */
typedef enum CLKCTRL_CLKSEL_ALT_enum
{
    CLKCTRL_CLKSEL_OSC20M_gc = (0x00<<0),  /* 20MHz oscillator */
    CLKCTRL_CLKSEL_OSCULP32K_gc = (0x01<<0),  /* 32KHz oscillator */
} CLKCTRL_CLKSEL_ALT_t;

/* Prescaler division select */
typedef enum CLKCTRL_PDIV_ALT_enum
{
    CLKCTRL_PDIV_2X_gc = (0x00<<1),  /* 2X */
    CLKCTRL_PDIV_4X_gc = (0x01<<1),  /* 4X */
    CLKCTRL_PDIV_8X_gc = (0x02<<1),  /* 8X */
    CLKCTRL_PDIV_16X_gc = (0x03<<1),  /* 16X */
    CLKCTRL_PDIV_32X_gc = (0x04<<1),  /* 32X */
    CLKCTRL_PDIV_64X_gc = (0x05<<1),  /* 64X */
    CLKCTRL_PDIV_6X_gc = (0x08<<1),  /* 6X */
    CLKCTRL_PDIV_10X_gc = (0x09<<1),  /* 10X */
    CLKCTRL_PDIV_12X_gc = (0x0A<<1),  /* 12X */
    CLKCTRL_PDIV_24X_gc = (0x0B<<1),  /* 24X */
    CLKCTRL_PDIV_48X_gc = (0x0C<<1)  /* 48X */
} CLKCTRL_PDIV_ALT_t;

/* Channel generator select */
typedef enum EVSYS_CHANNEL0_enum
{
    EVSYS_CHANNEL0_OFF_gc = (0x00<<0),  /* Off */
    EVSYS_CHANNEL0_UPDI_SYNCH_gc = (0x01<<0),  /* UPDI SYNCH character */
    EVSYS_CHANNEL0_RTC_OVF_gc = (0x06<<0),  /* Real Time Counter overflow */
    EVSYS_CHANNEL0_RTC_CMP_gc = (0x07<<0),  /* Real Time Counter compare */
    EVSYS_CHANNEL0_CCL_LUT0_gc = (0x10<<0),  /* Configurable Custom Logic LUT0 */
    EVSYS_CHANNEL0_CCL_LUT1_gc = (0x11<<0),  /* Configurable Custom Logic LUT1 */
    EVSYS_CHANNEL0_CCL_LUT2_gc = (0x12<<0),  /* Configurable Custom Logic LUT2 */
    EVSYS_CHANNEL0_CCL_LUT3_gc = (0x13<<0),  /* Configurable Custom Logic LUT3 */
    EVSYS_CHANNEL0_AC0_OUT_gc = (0x20<<0),  /* Analog Comparator 0 out */
    EVSYS_CHANNEL0_AC1_OUT_gc = (0x21<<0),  /* Analog Comparator 1 out */
    EVSYS_CHANNEL0_ADC0_RES_gc = (0x24<<0),  /* ADC 0 Result Ready */
    EVSYS_CHANNEL0_ADC0_SAMP_gc = (0x25<<0),  /* ADC 0 Sample Ready */
    EVSYS_CHANNEL0_ADC0_WCMP_gc = (0x26<<0),  /* ADC 0 Window Compare */
    EVSYS_CHANNEL0_USART0_XCK_gc = (0x60<<0),  /* USART 0 XCK */
    EVSYS_CHANNEL0_USART1_XCK_gc = (0x61<<0),  /* USART 1 XCK */
    EVSYS_CHANNEL0_USART2_XCK_gc = (0x62<<0),  /* USART 2 XCK */
    EVSYS_CHANNEL0_SPI0_SCK_gc = (0x68<<0),  /* SPI 0 SCK */
    EVSYS_CHANNEL0_TCA0_OVF_LUNF_gc = (0x80<<0),  /* Timer/Counter A0 overflow / low byte timer underflow */
    EVSYS_CHANNEL0_TCA0_HUNF_gc = (0x81<<0),  /* Timer/Counter A0 high byte timer underflow */
    EVSYS_CHANNEL0_TCA0_CMP0_LCMP0_gc = (0x84<<0),  /* Timer/Counter A0 compare 0 / low byte timer compare 0 */
    EVSYS_CHANNEL0_TCA0_CMP1_LCMP1_gc = (0x85<<0),  /* Timer/Counter A0 compare 1 / low byte timer compare 1 */
    EVSYS_CHANNEL0_TCA0_CMP2_LCMP2_gc = (0x86<<0),  /* Timer/Counter A0 compare 2 / low byte timer compare 2 */
    EVSYS_CHANNEL0_TCA1_OVF_LUNF_gc = (0x88<<0),  /* Timer/Counter A1 overflow / low byte timer underflow */
    EVSYS_CHANNEL0_TCA1_HUNF_gc = (0x89<<0),  /* Timer/Counter A1 high byte timer underflow */
    EVSYS_CHANNEL0_TCA1_CMP0_LCMP0_gc = (0x8C<<0),  /* Timer/Counter A1 compare 0 / low byte timer compare 0 */
    EVSYS_CHANNEL0_TCA1_CMP1_LCMP1_gc = (0x8D<<0),  /* Timer/Counter A1 compare 1 / low byte timer compare 1 */
    EVSYS_CHANNEL0_TCA1_CMP2_LCMP2_gc = (0x8E<<0),  /* Timer/Counter A1 compare 2 / low byte timer compare 2 */
    EVSYS_CHANNEL0_TCB0_CAPT_gc = (0xA0<<0),  /* Timer/Counter B0 capture */
    EVSYS_CHANNEL0_TCB0_OVF_gc = (0xA1<<0),  /* Timer/Counter B0 overflow */
    EVSYS_CHANNEL0_TCB1_CAPT_gc = (0xA2<<0),  /* Timer/Counter B1 capture */
    EVSYS_CHANNEL0_TCB1_OVF_gc = (0xA3<<0),  /* Timer/Counter B1 overflow */
    EVSYS_CHANNEL0_TCB2_CAPT_gc = (0xA4<<0),  /* Timer/Counter B2 capture */
    EVSYS_CHANNEL0_TCB2_OVF_gc = (0xA5<<0),  /* Timer/Counter B2 overflow */
    EVSYS_CHANNEL0_TCB3_CAPT_gc = (0xA6<<0),  /* Timer/Counter B3 capture */
    EVSYS_CHANNEL0_TCB3_OVF_gc = (0xA7<<0)  /* Timer/Counter B3 overflow */
} EVSYS_CHANNEL0_t;

/* Channel generator select */
typedef enum EVSYS_CHANNEL1_enum
{
    EVSYS_CHANNEL1_OFF_gc = (0x00<<0),  /* Off */
    EVSYS_CHANNEL1_UPDI_SYNCH_gc = (0x01<<0),  /* UPDI SYNCH character */
    EVSYS_CHANNEL1_RTC_OVF_gc = (0x06<<0),  /* Real Time Counter overflow */
    EVSYS_CHANNEL1_RTC_CMP_gc = (0x07<<0),  /* Real Time Counter compare */
    EVSYS_CHANNEL1_CCL_LUT0_gc = (0x10<<0),  /* Configurable Custom Logic LUT0 */
    EVSYS_CHANNEL1_CCL_LUT1_gc = (0x11<<0),  /* Configurable Custom Logic LUT1 */
    EVSYS_CHANNEL1_CCL_LUT2_gc = (0x12<<0),  /* Configurable Custom Logic LUT2 */
    EVSYS_CHANNEL1_CCL_LUT3_gc = (0x13<<0),  /* Configurable Custom Logic LUT3 */
    EVSYS_CHANNEL1_AC0_OUT_gc = (0x20<<0),  /* Analog Comparator 0 out */
    EVSYS_CHANNEL1_AC1_OUT_gc = (0x21<<0),  /* Analog Comparator 1 out */
    EVSYS_CHANNEL1_ADC0_RES_gc = (0x24<<0),  /* ADC 0 Result Ready */
    EVSYS_CHANNEL1_ADC0_SAMP_gc = (0x25<<0),  /* ADC 0 Sample Ready */
    EVSYS_CHANNEL1_ADC0_WCMP_gc = (0x26<<0),  /* ADC 0 Window Compare */
    EVSYS_CHANNEL1_USART0_XCK_gc = (0x60<<0),  /* USART 0 XCK */
    EVSYS_CHANNEL1_USART1_XCK_gc = (0x61<<0),  /* USART 1 XCK */
    EVSYS_CHANNEL1_USART2_XCK_gc = (0x62<<0),  /* USART 2 XCK */
    EVSYS_CHANNEL1_SPI0_SCK_gc = (0x68<<0),  /* SPI 0 SCK */
    EVSYS_CHANNEL1_TCA0_OVF_LUNF_gc = (0x80<<0),  /* Timer/Counter A0 overflow / low byte timer underflow */
    EVSYS_CHANNEL1_TCA0_HUNF_gc = (0x81<<0),  /* Timer/Counter A0 high byte timer underflow */
    EVSYS_CHANNEL1_TCA0_CMP0_LCMP0_gc = (0x84<<0),  /* Timer/Counter A0 compare 0 / low byte timer compare 0 */
    EVSYS_CHANNEL1_TCA0_CMP1_LCMP1_gc = (0x85<<0),  /* Timer/Counter A0 compare 1 / low byte timer compare 1 */
    EVSYS_CHANNEL1_TCA0_CMP2_LCMP2_gc = (0x86<<0),  /* Timer/Counter A0 compare 2 / low byte timer compare 2 */
    EVSYS_CHANNEL1_TCA1_OVF_LUNF_gc = (0x88<<0),  /* Timer/Counter A1 overflow / low byte timer underflow */
    EVSYS_CHANNEL1_TCA1_HUNF_gc = (0x89<<0),  /* Timer/Counter A1 high byte timer underflow */
    EVSYS_CHANNEL1_TCA1_CMP0_LCMP0_gc = (0x8C<<0),  /* Timer/Counter A1 compare 0 / low byte timer compare 0 */
    EVSYS_CHANNEL1_TCA1_CMP1_LCMP1_gc = (0x8D<<0),  /* Timer/Counter A1 compare 1 / low byte timer compare 1 */
    EVSYS_CHANNEL1_TCA1_CMP2_LCMP2_gc = (0x8E<<0),  /* Timer/Counter A1 compare 2 / low byte timer compare 2 */
    EVSYS_CHANNEL1_TCB0_CAPT_gc = (0xA0<<0),  /* Timer/Counter B0 capture */
    EVSYS_CHANNEL1_TCB0_OVF_gc = (0xA1<<0),  /* Timer/Counter B0 overflow */
    EVSYS_CHANNEL1_TCB1_CAPT_gc = (0xA2<<0),  /* Timer/Counter B1 capture */
    EVSYS_CHANNEL1_TCB1_OVF_gc = (0xA3<<0),  /* Timer/Counter B1 overflow */
    EVSYS_CHANNEL1_TCB2_CAPT_gc = (0xA4<<0),  /* Timer/Counter B2 capture */
    EVSYS_CHANNEL1_TCB2_OVF_gc = (0xA5<<0),  /* Timer/Counter B2 overflow */
    EVSYS_CHANNEL1_TCB3_CAPT_gc = (0xA6<<0),  /* Timer/Counter B3 capture */
    EVSYS_CHANNEL1_TCB3_OVF_gc = (0xA7<<0)  /* Timer/Counter B3 overflow */
} EVSYS_CHANNEL1_t;

/* Channel generator select */
typedef enum EVSYS_CHANNEL2_enum
{
    EVSYS_CHANNEL2_OFF_gc = (0x00<<0),  /* Off */
    EVSYS_CHANNEL2_UPDI_SYNCH_gc = (0x01<<0),  /* UPDI SYNCH character */
    EVSYS_CHANNEL2_RTC_OVF_gc = (0x06<<0),  /* Real Time Counter overflow */
    EVSYS_CHANNEL2_RTC_CMP_gc = (0x07<<0),  /* Real Time Counter compare */
    EVSYS_CHANNEL2_CCL_LUT0_gc = (0x10<<0),  /* Configurable Custom Logic LUT0 */
    EVSYS_CHANNEL2_CCL_LUT1_gc = (0x11<<0),  /* Configurable Custom Logic LUT1 */
    EVSYS_CHANNEL2_CCL_LUT2_gc = (0x12<<0),  /* Configurable Custom Logic LUT2 */
    EVSYS_CHANNEL2_CCL_LUT3_gc = (0x13<<0),  /* Configurable Custom Logic LUT3 */
    EVSYS_CHANNEL2_AC0_OUT_gc = (0x20<<0),  /* Analog Comparator 0 out */
    EVSYS_CHANNEL2_AC1_OUT_gc = (0x21<<0),  /* Analog Comparator 1 out */
    EVSYS_CHANNEL2_ADC0_RES_gc = (0x24<<0),  /* ADC 0 Result Ready */
    EVSYS_CHANNEL2_ADC0_SAMP_gc = (0x25<<0),  /* ADC 0 Sample Ready */
    EVSYS_CHANNEL2_ADC0_WCMP_gc = (0x26<<0),  /* ADC 0 Window Compare */
    EVSYS_CHANNEL2_USART0_XCK_gc = (0x60<<0),  /* USART 0 XCK */
    EVSYS_CHANNEL2_USART1_XCK_gc = (0x61<<0),  /* USART 1 XCK */
    EVSYS_CHANNEL2_USART2_XCK_gc = (0x62<<0),  /* USART 2 XCK */
    EVSYS_CHANNEL2_SPI0_SCK_gc = (0x68<<0),  /* SPI 0 SCK */
    EVSYS_CHANNEL2_TCA0_OVF_LUNF_gc = (0x80<<0),  /* Timer/Counter A0 overflow / low byte timer underflow */
    EVSYS_CHANNEL2_TCA0_HUNF_gc = (0x81<<0),  /* Timer/Counter A0 high byte timer underflow */
    EVSYS_CHANNEL2_TCA0_CMP0_LCMP0_gc = (0x84<<0),  /* Timer/Counter A0 compare 0 / low byte timer compare 0 */
    EVSYS_CHANNEL2_TCA0_CMP1_LCMP1_gc = (0x85<<0),  /* Timer/Counter A0 compare 1 / low byte timer compare 1 */
    EVSYS_CHANNEL2_TCA0_CMP2_LCMP2_gc = (0x86<<0),  /* Timer/Counter A0 compare 2 / low byte timer compare 2 */
    EVSYS_CHANNEL2_TCA1_OVF_LUNF_gc = (0x88<<0),  /* Timer/Counter A1 overflow / low byte timer underflow */
    EVSYS_CHANNEL2_TCA1_HUNF_gc = (0x89<<0),  /* Timer/Counter A1 high byte timer underflow */
    EVSYS_CHANNEL2_TCA1_CMP0_LCMP0_gc = (0x8C<<0),  /* Timer/Counter A1 compare 0 / low byte timer compare 0 */
    EVSYS_CHANNEL2_TCA1_CMP1_LCMP1_gc = (0x8D<<0),  /* Timer/Counter A1 compare 1 / low byte timer compare 1 */
    EVSYS_CHANNEL2_TCA1_CMP2_LCMP2_gc = (0x8E<<0),  /* Timer/Counter A1 compare 2 / low byte timer compare 2 */
    EVSYS_CHANNEL2_TCB0_CAPT_gc = (0xA0<<0),  /* Timer/Counter B0 capture */
    EVSYS_CHANNEL2_TCB0_OVF_gc = (0xA1<<0),  /* Timer/Counter B0 overflow */
    EVSYS_CHANNEL2_TCB1_CAPT_gc = (0xA2<<0),  /* Timer/Counter B1 capture */
    EVSYS_CHANNEL2_TCB1_OVF_gc = (0xA3<<0),  /* Timer/Counter B1 overflow */
    EVSYS_CHANNEL2_TCB2_CAPT_gc = (0xA4<<0),  /* Timer/Counter B2 capture */
    EVSYS_CHANNEL2_TCB2_OVF_gc = (0xA5<<0),  /* Timer/Counter B2 overflow */
    EVSYS_CHANNEL2_TCB3_CAPT_gc = (0xA6<<0),  /* Timer/Counter B3 capture */
    EVSYS_CHANNEL2_TCB3_OVF_gc = (0xA7<<0)  /* Timer/Counter B3 overflow */
} EVSYS_CHANNEL2_t;

/* Channel generator select */
typedef enum EVSYS_CHANNEL3_enum
{
    EVSYS_CHANNEL3_OFF_gc = (0x00<<0),  /* Off */
    EVSYS_CHANNEL3_UPDI_SYNCH_gc = (0x01<<0),  /* UPDI SYNCH character */
    EVSYS_CHANNEL3_RTC_OVF_gc = (0x06<<0),  /* Real Time Counter overflow */
    EVSYS_CHANNEL3_RTC_CMP_gc = (0x07<<0),  /* Real Time Counter compare */
    EVSYS_CHANNEL3_CCL_LUT0_gc = (0x10<<0),  /* Configurable Custom Logic LUT0 */
    EVSYS_CHANNEL3_CCL_LUT1_gc = (0x11<<0),  /* Configurable Custom Logic LUT1 */
    EVSYS_CHANNEL3_CCL_LUT2_gc = (0x12<<0),  /* Configurable Custom Logic LUT2 */
    EVSYS_CHANNEL3_CCL_LUT3_gc = (0x13<<0),  /* Configurable Custom Logic LUT3 */
    EVSYS_CHANNEL3_AC0_OUT_gc = (0x20<<0),  /* Analog Comparator 0 out */
    EVSYS_CHANNEL3_AC1_OUT_gc = (0x21<<0),  /* Analog Comparator 1 out */
    EVSYS_CHANNEL3_ADC0_RES_gc = (0x24<<0),  /* ADC 0 Result Ready */
    EVSYS_CHANNEL3_ADC0_SAMP_gc = (0x25<<0),  /* ADC 0 Sample Ready */
    EVSYS_CHANNEL3_ADC0_WCMP_gc = (0x26<<0),  /* ADC 0 Window Compare */
    EVSYS_CHANNEL3_USART0_XCK_gc = (0x60<<0),  /* USART 0 XCK */
    EVSYS_CHANNEL3_USART1_XCK_gc = (0x61<<0),  /* USART 1 XCK */
    EVSYS_CHANNEL3_USART2_XCK_gc = (0x62<<0),  /* USART 2 XCK */
    EVSYS_CHANNEL3_SPI0_SCK_gc = (0x68<<0),  /* SPI 0 SCK */
    EVSYS_CHANNEL3_TCA0_OVF_LUNF_gc = (0x80<<0),  /* Timer/Counter A0 overflow / low byte timer underflow */
    EVSYS_CHANNEL3_TCA0_HUNF_gc = (0x81<<0),  /* Timer/Counter A0 high byte timer underflow */
    EVSYS_CHANNEL3_TCA0_CMP0_LCMP0_gc = (0x84<<0),  /* Timer/Counter A0 compare 0 / low byte timer compare 0 */
    EVSYS_CHANNEL3_TCA0_CMP1_LCMP1_gc = (0x85<<0),  /* Timer/Counter A0 compare 1 / low byte timer compare 1 */
    EVSYS_CHANNEL3_TCA0_CMP2_LCMP2_gc = (0x86<<0),  /* Timer/Counter A0 compare 2 / low byte timer compare 2 */
    EVSYS_CHANNEL3_TCA1_OVF_LUNF_gc = (0x88<<0),  /* Timer/Counter A1 overflow / low byte timer underflow */
    EVSYS_CHANNEL3_TCA1_HUNF_gc = (0x89<<0),  /* Timer/Counter A1 high byte timer underflow */
    EVSYS_CHANNEL3_TCA1_CMP0_LCMP0_gc = (0x8C<<0),  /* Timer/Counter A1 compare 0 / low byte timer compare 0 */
    EVSYS_CHANNEL3_TCA1_CMP1_LCMP1_gc = (0x8D<<0),  /* Timer/Counter A1 compare 1 / low byte timer compare 1 */
    EVSYS_CHANNEL3_TCA1_CMP2_LCMP2_gc = (0x8E<<0),  /* Timer/Counter A1 compare 2 / low byte timer compare 2 */
    EVSYS_CHANNEL3_TCB0_CAPT_gc = (0xA0<<0),  /* Timer/Counter B0 capture */
    EVSYS_CHANNEL3_TCB0_OVF_gc = (0xA1<<0),  /* Timer/Counter B0 overflow */
    EVSYS_CHANNEL3_TCB1_CAPT_gc = (0xA2<<0),  /* Timer/Counter B1 capture */
    EVSYS_CHANNEL3_TCB1_OVF_gc = (0xA3<<0),  /* Timer/Counter B1 overflow */
    EVSYS_CHANNEL3_TCB2_CAPT_gc = (0xA4<<0),  /* Timer/Counter B2 capture */
    EVSYS_CHANNEL3_TCB2_OVF_gc = (0xA5<<0),  /* Timer/Counter B2 overflow */
    EVSYS_CHANNEL3_TCB3_CAPT_gc = (0xA6<<0),  /* Timer/Counter B3 capture */
    EVSYS_CHANNEL3_TCB3_OVF_gc = (0xA7<<0)  /* Timer/Counter B3 overflow */
} EVSYS_CHANNEL3_t;

/* Channel generator select */
typedef enum EVSYS_CHANNEL4_enum
{
    EVSYS_CHANNEL4_OFF_gc = (0x00<<0),  /* Off */
    EVSYS_CHANNEL4_UPDI_SYNCH_gc = (0x01<<0),  /* UPDI SYNCH character */
    EVSYS_CHANNEL4_RTC_OVF_gc = (0x06<<0),  /* Real Time Counter overflow */
    EVSYS_CHANNEL4_RTC_CMP_gc = (0x07<<0),  /* Real Time Counter compare */
    EVSYS_CHANNEL4_CCL_LUT0_gc = (0x10<<0),  /* Configurable Custom Logic LUT0 */
    EVSYS_CHANNEL4_CCL_LUT1_gc = (0x11<<0),  /* Configurable Custom Logic LUT1 */
    EVSYS_CHANNEL4_CCL_LUT2_gc = (0x12<<0),  /* Configurable Custom Logic LUT2 */
    EVSYS_CHANNEL4_CCL_LUT3_gc = (0x13<<0),  /* Configurable Custom Logic LUT3 */
    EVSYS_CHANNEL4_AC0_OUT_gc = (0x20<<0),  /* Analog Comparator 0 out */
    EVSYS_CHANNEL4_AC1_OUT_gc = (0x21<<0),  /* Analog Comparator 1 out */
    EVSYS_CHANNEL4_ADC0_RES_gc = (0x24<<0),  /* ADC 0 Result Ready */
    EVSYS_CHANNEL4_ADC0_SAMP_gc = (0x25<<0),  /* ADC 0 Sample Ready */
    EVSYS_CHANNEL4_ADC0_WCMP_gc = (0x26<<0),  /* ADC 0 Window Compare */
    EVSYS_CHANNEL4_USART0_XCK_gc = (0x60<<0),  /* USART 0 XCK */
    EVSYS_CHANNEL4_USART1_XCK_gc = (0x61<<0),  /* USART 1 XCK */
    EVSYS_CHANNEL4_USART2_XCK_gc = (0x62<<0),  /* USART 2 XCK */
    EVSYS_CHANNEL4_SPI0_SCK_gc = (0x68<<0),  /* SPI 0 SCK */
    EVSYS_CHANNEL4_TCA0_OVF_LUNF_gc = (0x80<<0),  /* Timer/Counter A0 overflow / low byte timer underflow */
    EVSYS_CHANNEL4_TCA0_HUNF_gc = (0x81<<0),  /* Timer/Counter A0 high byte timer underflow */
    EVSYS_CHANNEL4_TCA0_CMP0_LCMP0_gc = (0x84<<0),  /* Timer/Counter A0 compare 0 / low byte timer compare 0 */
    EVSYS_CHANNEL4_TCA0_CMP1_LCMP1_gc = (0x85<<0),  /* Timer/Counter A0 compare 1 / low byte timer compare 1 */
    EVSYS_CHANNEL4_TCA0_CMP2_LCMP2_gc = (0x86<<0),  /* Timer/Counter A0 compare 2 / low byte timer compare 2 */
    EVSYS_CHANNEL4_TCA1_OVF_LUNF_gc = (0x88<<0),  /* Timer/Counter A1 overflow / low byte timer underflow */
    EVSYS_CHANNEL4_TCA1_HUNF_gc = (0x89<<0),  /* Timer/Counter A1 high byte timer underflow */
    EVSYS_CHANNEL4_TCA1_CMP0_LCMP0_gc = (0x8C<<0),  /* Timer/Counter A1 compare 0 / low byte timer compare 0 */
    EVSYS_CHANNEL4_TCA1_CMP1_LCMP1_gc = (0x8D<<0),  /* Timer/Counter A1 compare 1 / low byte timer compare 1 */
    EVSYS_CHANNEL4_TCA1_CMP2_LCMP2_gc = (0x8E<<0),  /* Timer/Counter A1 compare 2 / low byte timer compare 2 */
    EVSYS_CHANNEL4_TCB0_CAPT_gc = (0xA0<<0),  /* Timer/Counter B0 capture */
    EVSYS_CHANNEL4_TCB0_OVF_gc = (0xA1<<0),  /* Timer/Counter B0 overflow */
    EVSYS_CHANNEL4_TCB1_CAPT_gc = (0xA2<<0),  /* Timer/Counter B1 capture */
    EVSYS_CHANNEL4_TCB1_OVF_gc = (0xA3<<0),  /* Timer/Counter B1 overflow */
    EVSYS_CHANNEL4_TCB2_CAPT_gc = (0xA4<<0),  /* Timer/Counter B2 capture */
    EVSYS_CHANNEL4_TCB2_OVF_gc = (0xA5<<0),  /* Timer/Counter B2 overflow */
    EVSYS_CHANNEL4_TCB3_CAPT_gc = (0xA6<<0),  /* Timer/Counter B3 capture */
    EVSYS_CHANNEL4_TCB3_OVF_gc = (0xA7<<0)  /* Timer/Counter B3 overflow */
} EVSYS_CHANNEL4_t;

/* Channel generator select */
typedef enum EVSYS_CHANNEL5_enum
{
    EVSYS_CHANNEL5_OFF_gc = (0x00<<0),  /* Off */
    EVSYS_CHANNEL5_UPDI_SYNCH_gc = (0x01<<0),  /* UPDI SYNCH character */
    EVSYS_CHANNEL5_RTC_OVF_gc = (0x06<<0),  /* Real Time Counter overflow */
    EVSYS_CHANNEL5_RTC_CMP_gc = (0x07<<0),  /* Real Time Counter compare */
    EVSYS_CHANNEL5_CCL_LUT0_gc = (0x10<<0),  /* Configurable Custom Logic LUT0 */
    EVSYS_CHANNEL5_CCL_LUT1_gc = (0x11<<0),  /* Configurable Custom Logic LUT1 */
    EVSYS_CHANNEL5_CCL_LUT2_gc = (0x12<<0),  /* Configurable Custom Logic LUT2 */
    EVSYS_CHANNEL5_CCL_LUT3_gc = (0x13<<0),  /* Configurable Custom Logic LUT3 */
    EVSYS_CHANNEL5_AC0_OUT_gc = (0x20<<0),  /* Analog Comparator 0 out */
    EVSYS_CHANNEL5_AC1_OUT_gc = (0x21<<0),  /* Analog Comparator 1 out */
    EVSYS_CHANNEL5_ADC0_RES_gc = (0x24<<0),  /* ADC 0 Result Ready */
    EVSYS_CHANNEL5_ADC0_SAMP_gc = (0x25<<0),  /* ADC 0 Sample Ready */
    EVSYS_CHANNEL5_ADC0_WCMP_gc = (0x26<<0),  /* ADC 0 Window Compare */
    EVSYS_CHANNEL5_USART0_XCK_gc = (0x60<<0),  /* USART 0 XCK */
    EVSYS_CHANNEL5_USART1_XCK_gc = (0x61<<0),  /* USART 1 XCK */
    EVSYS_CHANNEL5_USART2_XCK_gc = (0x62<<0),  /* USART 2 XCK */
    EVSYS_CHANNEL5_SPI0_SCK_gc = (0x68<<0),  /* SPI 0 SCK */
    EVSYS_CHANNEL5_TCA0_OVF_LUNF_gc = (0x80<<0),  /* Timer/Counter A0 overflow / low byte timer underflow */
    EVSYS_CHANNEL5_TCA0_HUNF_gc = (0x81<<0),  /* Timer/Counter A0 high byte timer underflow */
    EVSYS_CHANNEL5_TCA0_CMP0_LCMP0_gc = (0x84<<0),  /* Timer/Counter A0 compare 0 / low byte timer compare 0 */
    EVSYS_CHANNEL5_TCA0_CMP1_LCMP1_gc = (0x85<<0),  /* Timer/Counter A0 compare 1 / low byte timer compare 1 */
    EVSYS_CHANNEL5_TCA0_CMP2_LCMP2_gc = (0x86<<0),  /* Timer/Counter A0 compare 2 / low byte timer compare 2 */
    EVSYS_CHANNEL5_TCA1_OVF_LUNF_gc = (0x88<<0),  /* Timer/Counter A1 overflow / low byte timer underflow */
    EVSYS_CHANNEL5_TCA1_HUNF_gc = (0x89<<0),  /* Timer/Counter A1 high byte timer underflow */
    EVSYS_CHANNEL5_TCA1_CMP0_LCMP0_gc = (0x8C<<0),  /* Timer/Counter A1 compare 0 / low byte timer compare 0 */
    EVSYS_CHANNEL5_TCA1_CMP1_LCMP1_gc = (0x8D<<0),  /* Timer/Counter A1 compare 1 / low byte timer compare 1 */
    EVSYS_CHANNEL5_TCA1_CMP2_LCMP2_gc = (0x8E<<0),  /* Timer/Counter A1 compare 2 / low byte timer compare 2 */
    EVSYS_CHANNEL5_TCB0_CAPT_gc = (0xA0<<0),  /* Timer/Counter B0 capture */
    EVSYS_CHANNEL5_TCB0_OVF_gc = (0xA1<<0),  /* Timer/Counter B0 overflow */
    EVSYS_CHANNEL5_TCB1_CAPT_gc = (0xA2<<0),  /* Timer/Counter B1 capture */
    EVSYS_CHANNEL5_TCB1_OVF_gc = (0xA3<<0),  /* Timer/Counter B1 overflow */
    EVSYS_CHANNEL5_TCB2_CAPT_gc = (0xA4<<0),  /* Timer/Counter B2 capture */
    EVSYS_CHANNEL5_TCB2_OVF_gc = (0xA5<<0),  /* Timer/Counter B2 overflow */
    EVSYS_CHANNEL5_TCB3_CAPT_gc = (0xA6<<0),  /* Timer/Counter B3 capture */
    EVSYS_CHANNEL5_TCB3_OVF_gc = (0xA7<<0)  /* Timer/Counter B3 overflow */
} EVSYS_CHANNEL5_t;

// end of code