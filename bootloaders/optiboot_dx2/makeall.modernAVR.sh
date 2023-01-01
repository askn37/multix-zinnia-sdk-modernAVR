# export PACKS=../../temp/Atmel.AVR-Dx_DFP.....

###
### AVR DD 14pin-standard Default and Alternate USART : not exist LED.PA7 alternative
###

### LED=D7
make -f Makefile.modernAVR avr64dd20  TIMEOUT=1 BOOTNAME=boot_avrdd_UART0 UARTTX=A0 LED=D7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

### LED=C2
make -f Makefile.modernAVR avr64dd14  TIMEOUT=1 BOOTNAME=boot_avrdd_UART1 UARTTX=D6 LED=C2 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

###
### AVR DD 32pin-standard Alternate USART : not exist USERT2.PF4
###
make -f Makefile.modernAVR avr64dd32  TIMEOUT=1 BOOTNAME=boot_avrdd_UART0 UARTTX=D4 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

###
### AVR Dx Generic Upper 32pin Standard Alternate USART : using USART2.PF4 LED.A7 : but AVR DD
###
make -f Makefile.modernAVR avr128db32 TIMEOUT=1 BOOTNAME=boot_avrdx_UART2 UARTTX=F4 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

###
### AVR Dx Generic Upper 32pin Standard Default USART : using USERT0.PA0 LED.PA7
###
make -f Makefile.modernAVR avr128db48 TIMEOUT=1 BOOTNAME=boot_avrdx_UART0 UARTTX=A0 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

### using USERT1.PC0 LED.PA7
make -f Makefile.modernAVR avr128db48 TIMEOUT=1 BOOTNAME=boot_avrdx_UART1 UARTTX=C0 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

### using USERT2.PF0 LED.PA7
make -f Makefile.modernAVR avr128db48 TIMEOUT=1 BOOTNAME=boot_avrdx_UART2 UARTTX=F0 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1

###
### BIGBOOT
###

### LED=D7
# make -f Makefile.modernAVR avr32dd20  TIMEOUT=1 BOOTNAME=bigboot_avrdd_UART0 UARTTX=A0 LED=D7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1 BIGBOOT=1

### LED=A7
# make -f Makefile.modernAVR avr128db64 TIMEOUT=1 BOOTNAME=bigboot_avrdx_UART0 UARTTX=A0 LED=A7 BAUD_RATE=115200 SKIP_BOOTLOADER_ON_POR=1 BIGBOOT=1

###
### Cleanup
###
make -f Makefile.modernAVR clean

# end of code
