# export PACKS=../../temp/Atmel.AVR-Ex_DFP.....

###
### AVR Ex Generic Upper 28/32/48pin Standard Default USART : using USERT0.PA0 LED.PA7
###
make -f Makefile.modernAVR avr64ea48 TIMEOUT=1 BOOTNAME=boot_avrex_UART0 UARTTX=A0 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

### using USERT1.PC0 LED.PC0
make -f Makefile.modernAVR avr64ea48 TIMEOUT=1 BOOTNAME=boot_avrex_UART1 UARTTX=C0 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

### using USERT2.PF0 LED.PA7
make -f Makefile.modernAVR avr64ea48 TIMEOUT=1 BOOTNAME=boot_avrex_UART2 UARTTX=F0 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

### using USERT2.PF4 LED.PA7
make -f Makefile.modernAVR avr64ea48 TIMEOUT=1 BOOTNAME=boot_avrex_UART2 UARTTX=F4 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

###
### BIGBOOT
###

### LED=A7
# make -f Makefile.modernAVR avr64ea48 TIMEOUT=1 BOOTNAME=bigboot_avrex_UART0 UARTTX=A0 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1 BIGBOOT=1

###
### Cleanup
###
make -f Makefile.modernAVR clean

# end of code
