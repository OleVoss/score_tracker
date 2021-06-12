#!/bin/bash

# setup
set -e
avr_lib=./libs/lcd
# get filename
file=$(basename $1 .c)

# compile .c to .elf
avr-gcc -mmcu=atmega328p -Wall -Os  -o $file.elf $file.c $avr_lib/lcdpcf8574/lcdpcf8574.c $avr_lib/pcf8574/pcf8574.c $avr_lib/i2chw/twimaster.c
# -DF_CPU=1280000UL

# copy elf sections
avr-objcopy -j .text -j .data -O ihex $file.elf $file.hex

# flash to atmega328p
avrdude -p m328p -c usbasp -e -U flash:w:$file.hex

# clean temorary files
rm $file.elf $file.hex
