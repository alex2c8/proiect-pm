all: test_lcd.hex

test_lcd.hex: test_lcd.elf
	avr-objcopy  -j .text -j .data -O ihex $^ $@
	avr-size test_lcd.elf

test_lcd.elf: test_lcd.cpp UTFT.cpp DefaultFonts.c
	avr-g++ -mmcu=atmega324a -Os -Wall -o $@ $^
	
UTFT.elf: UTFT.cpp
	avr-g++ -mmcu=atmega324a -Os -lm -Wall -o $@ $^
	
clean:
	rm -rf test_lcd.elf test_lcd.hex
