CC = avr-gcc
PLATFORM = -mmcu=atmega324a
CFLAGS = -Wall -Os

#ACC_OBJS += i2chw\twimastertimeout.o mpu6050\mpu6050.o mpu6050\mpu6050dmp6.o

OBJS += \
	lcd.o screens.o fonts.o \
	i2chw\twimastertimeout.o mpu6050\mpu6050.o \
	game.o \
	main.o

DEFINES += -DF_CPU=16000000

all: main.hex

%.o: %.c
	$(CC) -c $(PLATFORM) $(DEFINES) $(CFLAGS) -o  $@  $<

main.elf: $(OBJS)
	$(CC) $(PLATFORM) -o $@ $^

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@
	avr-size main.elf main.hex

clean:
	rm -rf main.hex main.elf $(OBJS)
