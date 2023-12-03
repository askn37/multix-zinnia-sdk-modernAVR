#!/bin/sh

###
### AVR_DA/DB/DD Generic
###

### AVR_DA/DB/DD 28/32/48/64pin using USERT0.PA0 LED.PA7
make avr128db64 BOOTNAME=boot_avrdx_UART0 UART=A0 LED=A7

###
### AVR_DA/DB Alternate
###

### AVR DA/DB using USERT1.PC0 LED.PA7
make avr128db64 BOOTNAME=boot_avrdx_UART1 UART=C0 LED=A7

### AVR DA/DB using USERT2.PF0 LED.PA7
make avr128db64 BOOTNAME=boot_avrdx_UART2 UART=F0 LED=A7

### AVR DA/DB using USERT2.PF4 LED.PA7
make avr128db64 BOOTNAME=boot_avrdx_UART2 UART=F4 LED=A7

###
### AVR_DD Alternate
###

### AVR DD 28/32pin using USERT0.PD4 LED.PA7
make avr64dd32 BOOTNAME=boot_avrdd_UART0 UART=D4 LED=A7

### AVR_DD 14/20pin using UART0.PA0 LED.D7
make avr64dd20 BOOTNAME=boot_avrdd_UART0 UART=A0 LED=D7

### AVR_DD 14/20pin using UART1.PD6 LED.C2 (Xplained)
make avr64dd14 BOOTNAME=boot_avrdd_UART1 UART=D6 LED=C2

###
### Cleanup
###
make clean

# end of code
