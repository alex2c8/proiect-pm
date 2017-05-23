// LCD library
#include "lcd.h"

#include "font.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpu6050/mpu6050.h"


int _x1 = 100;
int _x2 = 115;
int _y1 = 70;
int _y2 = 85;
int offset = 5;

char buf[100];
#define LIMIT 0.2

void acc_test()
{
	double x = 0;
	double y = 0;
	double z = 0;
	double gxds = 0;
	double gyds = 0;
	double gzds = 0;

	mpu6050_getConvData(&x, &y, &z, &gxds, &gyds, &gzds);
	// UP
	if(x > LIMIT) {
		PORTD |= (1 << PD7);
		print_string("UP", 50, 50, 0);
		_delay_ms(10);
	}
	// DOWN
	else if(x < -LIMIT) {
		PORTD &= ~(1 << PD7);
		print_string("DOWN", 50, 50, 0);
		_delay_ms(10);
	}


	// LEFT
	if(y > LIMIT) {
		PORTD |= (1 << PD7);
		print_string("LEFT", 50, 70, 0);
		_delay_ms(10);
	}
	// RIGHT
	else if(y < -LIMIT) {
		PORTD &= ~(1 << PD7);
		print_string("RIGHT", 50, 70, 0);
		_delay_ms(10);
	}
}

int main(void)
{

	DDRD &= ~(1 << PD6);
	PORTD |= (1 << PD6);

	DDRD |= (1 << PD7);
	PORTD &= ~(1 << PD7);

	init_lcd(LANDSCAPE);



	set_font(SmallFont);

	char str_lives[] = "Hello, world";

	fill_screen(0, 0, 0);
	_delay_ms(50);

	mpu6050_init();


	while (1) {
		print_string(str_lives, 60, 0, 0);

		acc_test();
	}

	return 0;
}
