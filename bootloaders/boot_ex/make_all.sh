#!/bin/sh

###
### AVR_EA Generic
###

### AVR_EA 28/32/48pin using USERT0.PA0 LED.PA7
make avr64ea48 BOOTNAME=boot_avrea_UART0 UART=A0 LED=A7

### with Pull-Up RxD
make avr64ea48 BOOTNAME=boot_avrea_UART0_PU UART=A0 LED=A7 PULLUP_RX=1

### AVR_EA 28/32/48pin using USERT0.PC0 LED.PA7
make avr64ea48 BOOTNAME=boot_avrea_UART1 UART=C0 LED=A7

### AVR_EA 28/32/48pin using USERT0.PF0 LED.PA7
make avr64ea48 BOOTNAME=boot_avrea_UART2 UART=F0 LED=A7

### AVR_EA 28/32/48pin using USERT0.PF4 LED.PA7
make avr64ea48 BOOTNAME=boot_avrea_UART2 UART=F4 LED=A7

###
### AVR_EB Generic
###

### AVR_EB 28/32pin using USERT0.PA0 LED.PA7
make avr16eb32 BOOTNAME=boot_avreb_UART0 UART=A0 LED=A7

### with Pull-Up RxD
make avr16eb32 BOOTNAME=boot_avreb_UART0_PU UART=A0 LED=A7 PULLUP_RX=1

### AVR_EB 14/20pin using USERT0.PA0 LED.PD7
make avr16eb14 BOOTNAME=boot_avreb_UART0 UART=A0 LED=D7

###
### Cleanup
###
make clean

# end of code
