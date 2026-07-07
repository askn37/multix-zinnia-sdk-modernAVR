#!/usr/bin/env bash -e -
# AVRDUDEROOT=~/Library/Arduino15/packages/MultiX-Zinnia/tools/avrdude/8.1-avrdude/bin
AVRDUDEROOT=../../../../../tools/avrdude/8.1-avrdude/bin
PORT=/dev/cu.usbserial-230
PGM=jtag2updi
PART=avr128db32
BOOTS=./boot_avr128db64.hex

# The BOOTCODE granularity for this series is 512 bytes, so write 1 to FUSE8.

${AVRDUDEROOT}/avrdude -P $PORT -c $PGM -p $PART \
  -U syscfg0:w:0xf9:m \
  -U bootsize:w:1:m \
  -U flash:w:$BOOTS:i
