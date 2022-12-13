/**
 * @file variant_io.h
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
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

// end of code