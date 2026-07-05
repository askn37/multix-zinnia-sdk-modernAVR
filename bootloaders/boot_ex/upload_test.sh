#!/bin/sh
AVRDUDEROOT=../../../../../tools/avrdude/8.1-avrdude/bin/avrdude
# AVRDUDEROOT=~/Library/Arduino15/packages/MultiX-Zinnia/tools/avrdude/8.1-avrdude/bin
PORT=/dev/cu.usbserial-230
PGM=jtag2updi
PART=avr64ea32
BOOTS=./boot_avr64ea32.hex

# The BOOTCODE granularity for this series is 256 bytes, so write 2 to FUSE8.

${AVRDUDEROOT}/avrdude -P $PORT -c $PGM -p $PART \
  -U syscfg0:w:0xf9:m \
  -U bootsize:w:2:m \
  -U flash:w:$BOOTS:i
