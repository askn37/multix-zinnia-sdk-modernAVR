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

#define __MSS_CLKCTRL_CLKSEL_OSCN__
#define __MSS_CLKCTRL_PDIV_NX__
#define __MSS_EVSYS_SWEVENTN__

/* C Language Only */
#if !defined (__ASSEMBLER__)

/* Dialects specific to AVR_EA/EB/LA */
#define EVSYS_CHANNEL_ADC0_RESRDY_gc    EVSYS_CHANNEL_ADC0_RES_gc

#endif  /* C Language Only */

#ifndef FUSE_BROWSAVE
/* Alias FUSE_BOOTROWSAVE ​​for compatibility. */

#define FUSE_BROWSAVE     FUSE_BOOTROWSAVE      /* Boot Row Saved */
#define FUSE_BROWSAVE_bm  FUSE_BOOTROWSAVE_bm   /* Boot Row Saved bit mask. */
#define FUSE_BROWSAVE_bp  FUSE_BOOTROWSAVE_bp   /* Boot Row Saved bit position. */

#endif

#include <api/macro_sugar.h>
#endif

// end of code