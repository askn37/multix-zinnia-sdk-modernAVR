###
### AVR Dx Generic Upper 32pin Standard Default USART : using USERT0.PA0 LED.PA7
###
make -f Makefile.modernAVR avr128db48 TIMEOUT=1 BOOTNAME=boot_avrdx_UART0 UARTTX=A0 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

# make -f Makefile.modernAVR avr128db48 TIMEOUT=1 BOOTNAME=boot_atmega_UART0 UARTTX=A0 LED=A7 USART=1 SKIP_BOOTLOADER_ON_POR=1

# end of code
