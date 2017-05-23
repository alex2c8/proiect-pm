CC = avr-gcc
TARGET = -mmcu=atmega324a
CFLAGS = -Os -Wall

LCD_OBJS += lcd.o
MAIN_OBJ += main.o

all: main.hex

%.o: %.c
	$(CC) -c $(TARGET) $(CFLAGS) -o  $@  $<

main.elf: $(LCD_OBJS) $(MAIN_OBJ)
	$(CC) -mmcu=atmega324a -o $@ $^

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@
	avr-size main.elf

clean:
	rm -rf main.hex main.elf $(LCD_OBJS) $(MAIN_OBJ)
