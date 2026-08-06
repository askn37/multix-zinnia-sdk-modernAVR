#!/bin/sh -e

###
### AVR_SD Famiry
###

### AVR_SD 28/32/48pin using USART0.PA0 LED.PA7
make avr32sd32 BOOTNAME=boot_avrsd_UART0 UART=A0 LED=A7 PULLUP_RX=1

### AVR_SD 20/28/32/48pin using USART1.PD6 LED.PC3
make avr32sd32 BOOTNAME=boot_avrsd_UART1 UART=D6 LED=C3 PULLUP_RX=1

### AVR32SD32 32pin using USART0.PD4 LED.PD2 for AVR32SD32 Curiosity Nano
make avr32sd32 BOOTNAME=boot_avrsd_UART0 UART=D4 LED=D2 PULLUP_RX=1

###
### Cleanup
###
make clean

# end of code
