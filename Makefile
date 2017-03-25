CC=avr-gcc
MCU=atmega328
DEPS = portset.h

# Default Target
all : portset.hex

# Compile and Link
portset.o : portset.c
	$(CC) -g -Os -mmcu=$(MCU) -c portset.c

portset.elf : portset.o
	$(CC) -g -mmcu=$(MCU) -o portset.elf portset.o

portset.hex : portset.elf
	avr-objcopy -j .text -j .data -O ihex portset.elf portset.hex

.PHONY: clean
clean:
	rm -f *.elf *.o *~
