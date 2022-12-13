/**
 * @file peripheral.h
 * @author askn (K.Sato) multix.jp
 * @brief
 * @version 0.1
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <api/HarfUART.h>
#include <api/TWIM.h>
#include <variant.h>

#ifdef __cplusplus
extern "C" {
#endif

/* configuration to "api/Portmux.cpp" */

/* USARTn in HarfUART.h */
#define Serial0 Serial0A
extern HarfUART_Class Serial0A;   /* upload.port=UART0_A0 */
extern HarfUART_Class Serial0B;   /* upload.port=UART0_A4 */

#define Serial1 Serial1A
extern HarfUART_Class Serial1A;   /* upload.port=UART1_C0 */
extern HarfUART_Class Serial1B;   /* upload.port=UART1_C4 */

#define Serial2 Serial2B
extern HarfUART_Class Serial2A;   /* upload.port=UART2_F0 */
extern HarfUART_Class Serial2B;   /* upload.port=UART2_F4 */

#define Serial3 Serial3B
extern HarfUART_Class Serial3A;   /* upload.port=UART2_B0 */
extern HarfUART_Class Serial3B;   /* upload.port=UART2_B4 */

#define Serial4 Serial4B
extern HarfUART_Class Serial4A;   /* upload.port=UART2_E0 */
extern HarfUART_Class Serial4B;   /* upload.port=UART2_E4 */

#define Serial5 Serial5B
extern HarfUART_Class Serial5A;   /* upload.port=UART2_G0 */
extern HarfUART_Class Serial5B;   /* upload.port=UART2_G4 */

/* struct UART_portmux_t in Portmux.h */
#define _PORTMUX_USART0A {&PORTMUX_USARTROUTEA, PORTMUX_USART0_gm, PORTMUX_USART0_DEFAULT_gc, &PORTA, PIN0_bm, PIN1_bm, &PORTA_PIN1CTRL}
#define _PORTMUX_USART0B {&PORTMUX_USARTROUTEA, PORTMUX_USART0_gm, PORTMUX_USART0_ALT1_gc   , &PORTA, PIN4_bm, PIN5_bm, &PORTA_PIN5CTRL}
#define _PORTMUX_USART1A {&PORTMUX_USARTROUTEA, PORTMUX_USART1_gm, PORTMUX_USART1_DEFAULT_gc, &PORTC, PIN0_bm, PIN1_bm, &PORTC_PIN1CTRL}
#define _PORTMUX_USART1B {&PORTMUX_USARTROUTEA, PORTMUX_USART1_gm, PORTMUX_USART1_ALT1_gc   , &PORTC, PIN4_bm, PIN5_bm, &PORTC_PIN5CTRL}
#define _PORTMUX_USART2A {&PORTMUX_USARTROUTEA, PORTMUX_USART2_gm, PORTMUX_USART2_DEFAULT_gc, &PORTF, PIN0_bm, PIN1_bm, &PORTF_PIN1CTRL}
#define _PORTMUX_USART2B {&PORTMUX_USARTROUTEA, PORTMUX_USART2_gm, PORTMUX_USART2_ALT1_gc   , &PORTF, PIN4_bm, PIN5_bm, &PORTF_PIN5CTRL}
#define _PORTMUX_USART3A {&PORTMUX_USARTROUTEA, PORTMUX_USART3_gm, PORTMUX_USART3_DEFAULT_gc, &PORTB, PIN0_bm, PIN1_bm, &PORTB_PIN1CTRL}
#define _PORTMUX_USART3B {&PORTMUX_USARTROUTEA, PORTMUX_USART3_gm, PORTMUX_USART3_ALT1_gc   , &PORTB, PIN4_bm, PIN5_bm, &PORTB_PIN5CTRL}
#define _PORTMUX_USART4A {&PORTMUX_USARTROUTEB, PORTMUX_USART4_gm, PORTMUX_USART4_DEFAULT_gc, &PORTE, PIN0_bm, PIN1_bm, &PORTE_PIN1CTRL}
#define _PORTMUX_USART4B {&PORTMUX_USARTROUTEB, PORTMUX_USART4_gm, PORTMUX_USART4_ALT1_gc   , &PORTE, PIN4_bm, PIN5_bm, &PORTE_PIN5CTRL}
#define _PORTMUX_USART5A {&PORTMUX_USARTROUTEB, PORTMUX_USART5_gm, PORTMUX_USART5_DEFAULT_gc, &PORTG, PIN0_bm, PIN1_bm, &PORTF_PIN1CTRL}
#define _PORTMUX_USART5B {&PORTMUX_USARTROUTEB, PORTMUX_USART5_gm, PORTMUX_USART5_ALT1_gc   , &PORTG, PIN4_bm, PIN5_bm, &PORTG_PIN5CTRL}

/* TWIn in TWIM.h */
#define Wire0 Wire0A
extern TWIM_Class Wire0A;
extern TWIM_Class Wire0B;
extern TWIM_Class Wire0C;

#define Wire1 Wire1A
extern TWIM_Class Wire1A;
extern TWIM_Class Wire1B;
extern TWIM_Class Wire1C;

/* struct TWI_portmux_t in Portmux.h */
#define _PORTMUX_TWI0A {&PORTMUX_TWIROUTEA, PORTMUX_TWI0_gm, PORTMUX_TWI0_DEFAULT_gc, &PORTA, PIN2_bm, PIN3_bm, &PORTA_PIN2CTRL, &PORTA_PIN3CTRL}
#define _PORTMUX_TWI0B {&PORTMUX_TWIROUTEA, PORTMUX_TWI0_gm, PORTMUX_TWI0_ALT1_gc   , &PORTA, PIN2_bm, PIN3_bm, &PORTA_PIN2CTRL, &PORTA_PIN3CTRL}
#define _PORTMUX_TWI0C {&PORTMUX_TWIROUTEA, PORTMUX_TWI0_gm, PORTMUX_TWI0_ALT2_gc   , &PORTC, PIN2_bm, PIN3_bm, &PORTC_PIN2CTRL, &PORTC_PIN3CTRL}
#define _PORTMUX_TWI1A {&PORTMUX_TWIROUTEA, PORTMUX_TWI1_gm, PORTMUX_TWI1_DEFAULT_gc, &PORTF, PIN2_bm, PIN3_bm, &PORTF_PIN2CTRL, &PORTF_PIN3CTRL}
#define _PORTMUX_TWI1B {&PORTMUX_TWIROUTEA, PORTMUX_TWI1_gm, PORTMUX_TWI1_ALT1_gc   , &PORTF, PIN2_bm, PIN3_bm, &PORTF_PIN2CTRL, &PORTF_PIN3CTRL}
#define _PORTMUX_TWI1C {&PORTMUX_TWIROUTEA, PORTMUX_TWI1_gm, PORTMUX_TWI1_ALT2_gc   , &PORTB, PIN2_bm, PIN3_bm, &PORTB_PIN2CTRL, &PORTB_PIN3CTRL}

#ifdef __cplusplus
} // extern "C"
#endif

// end of code
