INCLUDEDIR=-Isrc/QTouch/ -I.

OBJS +=  \
		main.o \
		display_lib.o \
		src/QTouch/BitBangSPI_Master.o \
		src/QTouch/eeprom_access.o \
		src/QTouch/init_mcu_atmega324.o \
		src/QTouch/QDebug.o \
		src/QTouch/QDebugTransport.o \
		src/QTouch/qt_asm_tiny_mega.o \
		src/QTouch/SPI_Master.o \
		src/QTouch/TWI_Master.o \
		touch.o

all: main.hex

%.o: %.c
	avr-gcc -c -mmcu=atmega324a -Os -Wall $(INCLUDEDIR)  -o  $@  $<

src/QTouch/%.o: src/QTouch/%.c
	avr-gcc -c -mmcu=atmega324a -Os -Wall $(INCLUDEDIR)  -o  $@  $<

src/QTouch/qt_asm_tiny_mega.o: src/QTouch/qt_asm_tiny_mega.s
	avr-gcc -x assembler-with-cpp -c -mmcu=atmega324a -Os -Wall $(INCLUDEDIR)  -o  $@  $<

src/QTouch/%.o: ../src/QTouch/%.s
	avr-gcc -x assembler-with-cpp -c -mmcu=atmega324a -Os -Wall $(INCLUDEDIR)  -o  $@  $<

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@
	avr-size main.elf

main.elf: $(OBJS)
	avr-gcc -mmcu=atmega324a -o $@ $^ -lavr5g1-4qt-k-1rs -Lsrc/QTouch

clean:
	rm -rf main.hex main.elf $(OBJS)
