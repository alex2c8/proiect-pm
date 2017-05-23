// LCD
#include "lcd.h"
#include "font.h"

// accelerometer
#include "mpu6050/mpu6050.h"

// C
#include <string.h>

#define LIMIT 0.2
#define abs(X) ((X < 0) ? (-X) : (X))

int width = 20;
int height = 15;

int _x1 = 1;
int _x2 = 61;
int _y1 = DISPLAY_X_SIZE - 10;
int _y2 = DISPLAY_X_SIZE;

int offset = 12;


char buf[100];


uint8_t acc_test()
{
	uint8_t r = 0;

	double x = 0;
	double y = 0;
	double z = 0;
	double gxds = 0;
	double gyds = 0;
	double gzds = 0;

	mpu6050_getConvData(&x, &y, &z, &gxds, &gyds, &gzds);

	_delay_ms(50);

	// // UP
	// if(x > LIMIT) {
	// 	_y1 -= offset;
	// 	_y2 -= offset;
	// 	r = 1;
	// }
	// // DOWN
	// else if(x < -LIMIT) {
	// 	_y1 += offset;
	// 	_y2 += offset;
	// 	r = 1;
	// }

	// LEFT
	if(y > LIMIT) {
		if (_x1 - y * offset >= 0) {
			_x1 -= y * offset;
			_x2 -= y * offset;
			r = 1;
		}
	}
	// RIGHT
	else if(y < -LIMIT) {
		if (_x2 -y * offset <= DISPLAY_Y_SIZE) {
			_x1 += -y * offset;
			_x2 += -y * offset;
			r = 1;
		}
	}

	return r;
}

int main(void)
{

	// DDRD &= ~(1 << PD6);
	// PORTD |= (1 << PD6);

	// DDRD |= (1 << PD7);
	// PORTD &= ~(1 << PD7);

	init_lcd(LANDSCAPE);
	set_font(SmallFont);

	set_background_color(0, 200, 0);

	fill_screen(0, 200, 0);
	_delay_ms(50);

	mpu6050_init();

	while (1) {
		//print_string(str_lives, 60, 0, 0);

		int old_x1 = _x1;
		int old_x2 = _x2;
		int old_y1 = _y1;
		int old_y2 = _y2;


		if(acc_test()) {
			clear_region(old_x1, old_y1, old_x2, old_y2);
			// _delay_ms(25);
			draw_empty_round_rectangle(_x1, _y1, _x2, _y2);
			_delay_ms(25);
		}
	}

	return 0;
}
