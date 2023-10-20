###
### AVR EB Generic Upper 14/20pin Standard Default USART : using USERT0.PA0 LED.PD7
###
make -f Makefile.modernAVR avr16eb14 TIMEOUT=1 BOOTNAME=boot_avreb_UART0 UARTTX=A0 LED=D7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

# make -f Makefile.modernAVR avr64ea48 TIMEOUT=1 BOOTNAME=boot_avrex_UART0 UARTTX=A0 LED=A7 USART=1 SKIP_BOOTLOADER_ON_POR=1

# end of code
