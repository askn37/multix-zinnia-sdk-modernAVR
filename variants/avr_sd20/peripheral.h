/**
 * @file peripheral.h
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2024 askn37 at github.com
 *
 */
// MIT License : https://askn37.github.io/LICENSE.html

#include <api/HarfUART.h>
#include <api/TWIM.h>

#ifdef __cplusplus
extern "C" {
#endif

/* configuration to "api/Portmux.cpp" */

/* USARTn in HarfUART.h */
#define Serial0 Serial0A
extern HarfUART_Class Serial0A;   /* upload.port=UART0_A0 */
extern HarfUART_Class Serial0B;   /* upload.port=UART0_A4 */
extern HarfUART_Class Serial0C;   /* upload.port=UART0_A2 */
extern HarfUART_Class Serial0D;   /* upload.port=UART0_D4 */
extern HarfUART_Class Serial0E;   /* upload.port=UART0_C1 */

#define Serial1 Serial1C
extern HarfUART_Class Serial1A;   /* upload.port=UART1_C0 */ /* TX:PIN_PC0 not implemented */
/* Serial1B not implemented DD14 */
extern HarfUART_Class Serial1C;   /* upload.port=UART1_D6 */

/* struct UART_portmux_t in Portmux.h */
#define _PORTMUX_USART0A {&PORTMUX_USARTROUTEA, PORTMUX_USART0_gm, PORTMUX_USART0_DEFAULT_gc, &PORTA, PIN0_bm, PIN1_bm, &PORTA_PIN1CTRL}
#define _PORTMUX_USART0B {&PORTMUX_USARTROUTEA, PORTMUX_USART0_gm, PORTMUX_USART0_ALT1_gc   , &PORTA, PIN4_bm, PIN5_bm, &PORTA_PIN5CTRL}
#define _PORTMUX_USART0C {&PORTMUX_USARTROUTEA, PORTMUX_USART0_gm, PORTMUX_USART0_ALT2_gc   , &PORTA, PIN2_bm, PIN3_bm, &PORTA_PIN3CTRL}
#define _PORTMUX_USART0D {&PORTMUX_USARTROUTEA, PORTMUX_USART0_gm, PORTMUX_USART0_ALT3_gc   , &PORTD, PIN4_bm, PIN5_bm, &PORTD_PIN5CTRL}
#define _PORTMUX_USART0E {&PORTMUX_USARTROUTEA, PORTMUX_USART0_gm, PORTMUX_USART0_ALT4_gc   , &PORTC, PIN1_bm, PIN2_bm, &PORTC_PIN2CTRL}
#define _PORTMUX_USART1A {&PORTMUX_USARTROUTEA, PORTMUX_USART1_gm, PORTMUX_USART1_DEFAULT_gc, &PORTC, PIN0_bm, PIN1_bm, &PORTC_PIN1CTRL}
#define _PORTMUX_USART1C {&PORTMUX_USARTROUTEA, PORTMUX_USART1_gm, PORTMUX_USART1_ALT2_gc   , &PORTD, PIN6_bm, PIN7_bm, &PORTD_PIN7CTRL}

/* TWIn in TWIM.h */
#define Wire0 Wire0A
extern TWIM_Class Wire0A;
extern TWIM_Class Wire0C;
extern TWIM_Class Wire0D;

/* struct TWI_portmux_t in Portmux.h */
#define _PORTMUX_TWI0A {&PORTMUX_TWIROUTEA, PORTMUX_TWI0_gm, PORTMUX_TWI0_DEFAULT_gc, &PORTA, PIN2_bm, PIN3_bm, &PORTA_PIN2CTRL, &PORTA_PIN3CTRL}
#define _PORTMUX_TWI0C {&PORTMUX_TWIROUTEA, PORTMUX_TWI0_gm, PORTMUX_TWI0_ALT2_gc   , &PORTC, PIN2_bm, PIN3_bm, &PORTC_PIN2CTRL, &PORTC_PIN3CTRL}
#define _PORTMUX_TWI0D {&PORTMUX_TWIROUTEA, PORTMUX_TWI0_gm, PORTMUX_TWI0_ALT3_gc   , &PORTA, PIN0_bm, PIN1_bm, &PORTA_PIN0CTRL, &PORTA_PIN1CTRL}

#ifdef __cplusplus
} // extern "C"
#endif

// end of code
