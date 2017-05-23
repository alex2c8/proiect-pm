CC = avr-gcc
TARGET = -mmcu=atmega324a
CFLAGS = -Wall -Os

LCD_OBJS += lcd.o
MAIN_OBJ += main.o

#ACC_OBJS += i2chw\twimastertimeout.o mpu6050\mpu6050.o mpu6050\mpu6050dmp6.o
ACC_OBJS += i2chw\twimastertimeout.o mpu6050\mpu6050.o

DEFINES += -DF_CPU=16000000

all: main.hex

%.o: %.c
	$(CC) -c $(TARGET) $(DEFINES) $(CFLAGS) -o  $@  $<

main.elf: $(LCD_OBJS) $(MAIN_OBJ) $(ACC_OBJS)
	$(CC) $(TARGET) -o $@ $^

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@
	avr-size main.elf
	avr-size main.hex

clean:
	rm -rf main.hex main.elf $(LCD_OBJS) $(MAIN_OBJ) $(ACC_OBJS)
