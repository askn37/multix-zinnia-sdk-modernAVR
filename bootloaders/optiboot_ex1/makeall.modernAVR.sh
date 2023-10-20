# export PACKS=../../temp/Atmel.AVR-Ex_DFP.....

###
### AVR EA Generic Upper 28/32/48pin Standard Default USART : using USERT0.PA0 LED.PA7
###
make -f Makefile.modernAVR avr64ea48 TIMEOUT=1 BOOTNAME=boot_avrea_UART0 UARTTX=A0 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

### using USERT1.PC0 LED.PC0
make -f Makefile.modernAVR avr64ea48 TIMEOUT=1 BOOTNAME=boot_avrea_UART1 UARTTX=C0 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

### using USERT2.PF0 LED.PA7
make -f Makefile.modernAVR avr64ea48 TIMEOUT=1 BOOTNAME=boot_avrea_UART2 UARTTX=F0 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

### using USERT2.PF4 LED.PA7
make -f Makefile.modernAVR avr64ea48 TIMEOUT=1 BOOTNAME=boot_avrea_UART2 UARTTX=F4 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

###
### AVR EB Generic Upper 20/28/32pin Standard Default USART : using USERT0.PA0 LED.PA7
###
make -f Makefile.modernAVR avr16eb32 TIMEOUT=1 BOOTNAME=boot_avreb_UART0 UARTTX=A0 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

###
### AVR EB Generic Upper 14pin Standard Default USART : using USERT0.PA0 LED.PD7
###
make -f Makefile.modernAVR avr16eb14 TIMEOUT=1 BOOTNAME=boot_avreb_UART0 UARTTX=A0 LED=D7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

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
