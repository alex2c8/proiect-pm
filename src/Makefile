INCLUDE_DIRS=-Iqtouch/ -I.

# QTOUCH_OBJS +=  \
# 		qtouch/BitBangSPI_Master.o \
# 		qtouch/eeprom_access.o \
# 		qtouch/init_mcu_atmega324.o \
# 		qtouch/QDebug.o \
# 		qtouch/QDebugTransport.o \
# 		qtouch/qt_asm_tiny_mega.o \
# 		qtouch/SPI_Master.o \
# 		qtouch/TWI_Master.o \
# 		touch.o

QTOUCH_OBJS +=  \
		qtouch/init_mcu_atmega324.o \
		qtouch/qt_asm_tiny_mega.o \
		touch.o

LCD_OBJS += lcd.o

MAIN_OBJ += main.o

CC = avr-gcc
TARGET = -mmcu=atmega324a
CFLAGS = -Os -Wall

all: main.hex

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@
	avr-size main.elf

%.o: %.c
	$(CC) -c $(TARGET) $(CFLAGS) $(INCLUDE_DIRS)  -o  $@  $<

qtouch/%.o: qtouch/%.c
	$(CC) -c $(TARGET) $(CFLAGS) $(INCLUDE_DIRS)  -o  $@  $<

qtouch/qt_asm_tiny_mega.o: qtouch/qt_asm_tiny_mega.s
	$(CC) -x assembler-with-cpp -c $(TARGET) $(CFLAGS) $(INCLUDE_DIRS)  -o  $@  $<

qtouch/%.o: qtouch/%.s
	$(CC) -x assembler-with-cpp -c $(TARGET) $(CFLAGS) $(INCLUDE_DIRS)  -o  $@  $<


main.elf: $(QTOUCH_OBJS) $(LCD_OBJS) $(MAIN_OBJ)
	$(CC) -mmcu=atmega324a -o $@ $^ -lavr5g1-4qt-k-1rs -Lqtouch

clean:
	rm -rf main.hex main.elf $(QTOUCH_OBJS) $(LCD_OBJS) $(MAIN_OBJ)
