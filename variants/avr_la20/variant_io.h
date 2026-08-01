/**
 * @file variant_io.h
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2026-07-30
 *
 * @copyright Copyright (c) 2026 askn37 at github.com
 *
 */
// MIT License : https://askn37.github.io/LICENSE.html

#include <avr/io.h>
#define AVR_MEGAAVR_LIKE_MODERNAVR

#define SLEEP_MODE_ADC      SLEEP_MODE_STANDBY

/* C Language Only */
#if !defined (__ASSEMBLER__)

/* Clock select */
typedef enum CLKCTRL_CLKSEL_ALT_enum
{
    CLKCTRL_CLKSEL_OSC20M_gc = (0x00<<0),     /* 20MHz oscillator */
    CLKCTRL_CLKSEL_OSCULP32K_gc = (0x01<<0),  /* 32KHz oscillator */
} CLKCTRL_CLKSEL_ALT_t;

/* Prescaler division select */
typedef enum CLKCTRL_PDIV_ALT_enum
{
    CLKCTRL_PDIV_2X_gc  = (0x00<<1),  /* 2X */
    CLKCTRL_PDIV_4X_gc  = (0x01<<1),  /* 4X */
    CLKCTRL_PDIV_8X_gc  = (0x02<<1),  /* 8X */
    CLKCTRL_PDIV_16X_gc = (0x03<<1),  /* 16X */
    CLKCTRL_PDIV_32X_gc = (0x04<<1),  /* 32X */
    CLKCTRL_PDIV_64X_gc = (0x05<<1),  /* 64X */
    CLKCTRL_PDIV_6X_gc  = (0x08<<1),  /* 6X */
    CLKCTRL_PDIV_10X_gc = (0x09<<1),  /* 10X */
    CLKCTRL_PDIV_12X_gc = (0x0A<<1),  /* 12X */
    CLKCTRL_PDIV_24X_gc = (0x0B<<1),  /* 24X */
    CLKCTRL_PDIV_48X_gc = (0x0C<<1)   /* 48X */
} CLKCTRL_PDIV_ALT_t;

#endif

// end of code