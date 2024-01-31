# @file Makefile - for boot_dx.c
# @author askn (K.Sato) multix.jp
# @brief
# @version 3.7
# @date 2023-11-30
#
# @copyright Copyright (c) 2023 askn37 at github.com

### Default values
MCU_TARGET = avr128db64
PROGRAM = boot_avrdx_UART0
SOURCE = boot_dx.c

### LED PortPin
LED = A7

### If this is 0 or disabled, the LEDs will blink alternately.
LED_BLINK = 6

### UART TxD PortPin : RxD pin is determined automatically.
UART = A0

### Enable pullup on RxD pin
# PULLUP_RX = 1

### USART synchronous mode
### TxD pin is specified by UART variable.
### XCK pin is determined automatically.
# USART = 1

### RS485 (HARDWARE) XDIR pin support.
### XDIR pin is automatically determined from UART variable.
### RS485_SINGLE is in single wire mode so it does not use RxD pin.
# RS485 = 1
# RS485_SINGLE = 1
# RS485_INVERT = 1

### The default 4MHz frequency drive has a maximum speed of 225kbps.
### To increase it beyond that, change F_CPU as well.
### Ignored in USART mode.
BAUD_RATE = 115200

### WDT Limit 1,2,4,8 second. 0 is 0.5 second.
TIMEOUT = 1

### Selectable values for F_CPU_Scale: 1,2,3,4,5,6
F_CPU_Scale = 1

### Global settings
MF := $(MAKEFILE_LIST)
LDSECTIONS = -Wl,-section-start=.text=0 -Wl,--section-start=.appcode=0x200

AVRGCCROOT = ../../../../../tools/avr-gcc/7.3.0-avr8-gnu-toolchain/bin
# AVRGCCROOT = ~/Library/Arduino15/packages/MultiX-Zinnia/tools/avr-gcc/7.3.0-avr8-gnu-toolchain/bin

CC = $(AVRGCCROOT)/avr-gcc
OPTIMIZE = -Os -fno-split-wide-types -mrelax
JOINING  = -j .text -j .data -j --set-section-flags
CFLAGS   = -g -Wall $(OPTIMIZE) -save-temps=obj
LDFLAGS  = $(LDSECTIONS) -Wl,--relax -nostartfiles -nostdlib

OBJCOPY = $(AVRGCCROOT)/avr-objcopy
OBJDUMP = $(AVRGCCROOT)/avr-objdump
SIZE    = $(AVRGCCROOT)/avr-size
LISTING = $(OBJDUMP) -S

PERL := $(shell which perl)
GENCRC = ../gencrc.pl
GENCRCOPT = -u -c6

### Resolving abstract specifications

OPTIONS = -mmcu=$*

ifdef F_CPU_Scale
OPTIONS += -DF_CPU_Scale=$(F_CPU_Scale)
endif

ifdef UART
OPTIONS += -DUART=$(UART)
else
ifdef USART
OPTIONS += -DUSART
ifdef USART_INVERT
OPTIONS += -DUSART_INVERT
endif
endif
endif

ifdef PULLUP_RX
OPTIONS += -DPULLUP_RX
endif

ifdef PORSTRAP
OPTIONS += -DPORSTRAP
endif

ifdef RS485
OPTIONS += -DRS485
endif

ifdef RS485_INVERT
OPTIONS += -DRS485_INVERT
endif

ifdef LED
OPTIONS += -DLED=$(LED)
endif

ifdef LED_BLINK
OPTIONS += -DLED_BLINK=$(LED_BLINK)
endif

ifdef BAUD_RATE
OPTIONS += -DBAUD_RATE=$(BAUD_RATE)
endif

ifdef TIMEOUT
OPTIONS += -DTIMEOUT=$(TIMEOUT)
endif

### make section

boot_%.hex: boot_%.elf
ifneq ($(PERL),'')
	$(OBJCOPY) $(JOINING) -O binary $< boot_$*.tmp
	$(PERL) $(GENCRC) $(GENCRCOPT) -i boot_$*.tmp -o $@
else
	$(OBJCOPY) $(JOINING) -O ihex $< $@
endif
	@echo "******************************"
	@echo "*** Bare Bootloader size:"
	$(SIZE) $@

boot_%.elf:	$(SOURCE) FORCE
	@echo "******************************"
	@echo "*** Options:" $(MCU_TARGET) \
		BOOTNAME=$(PROGRAM) UART=$(UART) LED=$(LED) \
		BAUD_RATE=$(BAUD_RATE) TIMEOUT=$(TIMEOUT)
	$(CC) $(CFLAGS) $(OPTIONS) $(LDFLAGS) -o $@ $<
	$(LISTING) $@ > boot_$*.lst

avr%:
	$(MAKE) -f $(MF) boot_avr$*.hex
	$(OBJCOPY) -I ihex -O binary boot_avr$*.hex boot_avr$*.bin
	@echo "******************************"
	@echo "*** Output:"
	# mv boot_avr$*.lst ../hex/${BOOTNAME}_${UART}_${BAUD_RATE}_L${LED}.lst
	cp boot_avr$*.hex ../hex/${BOOTNAME}_${UART}_${BAUD_RATE}_L${LED}.hex
	cp boot_avr$*.bin ../bin/${BOOTNAME}_${UART}_${BAUD_RATE}_L${LED}.bin

all:
	$(MAKE) -f $(MF) $(MCU_TARGET) BOOTNAME=$(PROGRAM)

FORCE:

clean:
	@echo "******************************"
	@echo "*** Cleanup:"
	@touch __temp_.o __temp_.map __temp_.i __temp_.s __temp_.sym __temp_.lss __temp_.srec
	@touch __temp_.bin __temp_.hex __temp_.lst __temp_.eep __temp_.elf __temp_.tmp.sh __temp_.tmp
	rm -rf *.o *.elf *.lst *.map *.i *.s *.sym *.lss *.eep *.srec *.bin *.hex *.tmp.sh *.tmp

%.lst: %.elf FORCE
	$(OBJDUMP) -h -S $< > $@

%.srec: %.elf FORCE
	$(OBJCOPY) $(JOINING) -O srec $< $@

# %.bin: %.hex FORCE
# 	$(OBJCOPY) -I ihex -O binary $< $@

### end of makefile
