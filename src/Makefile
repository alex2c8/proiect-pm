all: main.hex

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@
	avr-size main.elf

main.elf: main.c display_lib.c
	avr-gcc -mmcu=atmega324a -Os -Wall -o $@ $^

clean:
	rm -rf main.hex main.elf
