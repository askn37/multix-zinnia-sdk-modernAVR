#!/bin/sh -e

###
### AVR_DA/DB Famiry
###

### AVR_DA/DB/DD 28/32/48/64pin using USART0.PA0 LED.PA7
make avr128db64 BOOTNAME=boot_avrdx_UART0 UART=A0 LED=A7 PULLUP_RX=1

### AVR DA/DB 28/32/48/64pin using USART2.PF0 LED.PA7
make avr128db64 BOOTNAME=boot_avrdx_UART2 UART=F0 LED=A7 PULLUP_RX=1

### AVR DA/DB 32/48/64pin using USART2.PF4 LED.PA7
make avr128db64 BOOTNAME=boot_avrdx_UART2 UART=F4 LED=A7 PULLUP_RX=1

### AVR128DB48 48pin using USART3.PB0 LED.PB3 for AVR128DB48 Curiosity Nano
make avr128db48 BOOTNAME=boot_avrdx_UART3 UART=B0 LED=B3 PULLUP_RX=1

### AVR128DA48 48pin using USART1.PC0 LED.PC6 for AVR128DA48 Curiosity Nano
make avr128da48 BOOTNAME=boot_avrdx_UART1 UART=C0 LED=C6 PULLUP_RX=1

###
### AVR_DD Famiry
###

### AVR_DD 20/28/32pin using USART0.PA0 LED.PA7
make avr64dd32 BOOTNAME=boot_avrdd_UART0 UART=A0 LED=A7 PULLUP_RX=1

### AVR DD 14/20/28/32pin using USART0.PD4 LED.PC3
make avr64dd32 BOOTNAME=boot_avrdd_UART0 UART=D4 LED=C3 PULLUP_RX=1

### AVR_DD 14/20/28/32pin using USART1.PD6 LED.PC3
make avr64dd32 BOOTNAME=boot_avrdd_UART1 UART=D6 LED=C3 PULLUP_RX=1

### AVR64DD32 32pin using USART0.PD4 LED.PF5 for AVR64DD32 Curiosity Nano
make avr64dd32 BOOTNAME=boot_avrdd_UART0 UART=D4 LED=F5 PULLUP_RX=1

###
### AVR_DU Famiry (NVMCTRL version 4)
###

### AVR_DU 14/20/28/32pin using USART0.PA0 LED.PA7 (14pin is PA7 not implimented)
make avr64du32 BOOTNAME=boot_avrdu_UART0 UART=A0 LED=A7 PULLUP_RX=1

### AVR_DU 14/20/28/32pin using USART0.PD4 LED.PC3 (PC3 is LUT1_OUT)
make avr64du32 BOOTNAME=boot_avrdu_UART0 UART=D4 LED=C3 PULLUP_RX=1

### AVR_DU 14/20/28/32pin using USART1.PD6 LED.PC3 (PC3 is LUT1_OUT)
make avr64du32 BOOTNAME=boot_avrdu_UART1 UART=D6 LED=C3 PULLUP_RX=1

### AVR_DU 32pin using USART1.PD6 LED.PF2 for AVR64DU32 Curiosity Nano
make avr64du32 BOOTNAME=boot_avrdu_UART1 UART=D6 LED=F2 PULLUP_RX=1

###
### Cleanup
###
make clean

# end of code
