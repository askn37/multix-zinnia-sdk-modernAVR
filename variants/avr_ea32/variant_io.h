/**
 * @file variant_io.h
 * @author askn (K.Sato) multix.jp
 * @brief Macro/Micro API variant io header
 * @version 0.2
 * @date 2026-09-16
 * @copyright Copyright (c) 2026 askn37 at github.com
 * @link Product Potal : https://askn37.github.io/
 *         MIT License : https://askn37.github.io/LICENSE.html
 */

#pragma once
#if defined(ENABLE_MACRO_API) && !defined(DISABLE_MACRO_API) && (__AVR_ARCH__ >= 102)
#include <avr/io.h>
#define AVR_MEGAAVR_LIKE_MODERNAVR

#define __MSS_USART_RS485_INT__
#define __MSS_CLKCTRL_CLKSEL_OSCN__
#define __MSS_CLKCTRL_PDIV_NX__
#define __MSS_EVSYS_CH__
#define __MSS_EVSYS_CHS_EA__

/* C Language Only */
#if !defined (__ASSEMBLER__)

/* Dialects specific to AVR_EA/EB */
#define EVSYS_CHANNEL_RTC_EVGEN0_gc     EVSYS_CHANNEL_RTC_PITEV0_gc
#define EVSYS_CHANNEL_RTC_EVGEN1_gc     EVSYS_CHANNEL_RTC_PITEV1_gc

/* Dialects specific to AVR_EA/EB/LA */
#define EVSYS_CHANNEL_ADC0_RESRDY_gc    EVSYS_CHANNEL_ADC0_RES_gc

#endif

#include <api/macro_sugar.h>
#endif

// end of code