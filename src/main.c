// LCD library
#include "lcd.h"

#include "font.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int _x1 = 100;
int _x2 = 115;
int _y1 = 70;
int _y2 = 85;
int offset = 5;

char buf[100];


int main(void)
{

	DDRD &= (1 << PD6);
	PORTD |= (1 << PD6);

	DDRD |= (1 << PD7);
	PORTD &= ~(1 << PD7);


	init_lcd(LANDSCAPE);

	// init_system();
	// init_timer_isr();
	// touch_init();

	set_font(SmallFont);

	char str_score[] = "score: 1337";
	char str_lives[] = "lives: 3";

	fill_screen(0, 0, 0);
	_delay_ms(50);

	while (1) {
		// fill_screen(200, 0, 0);
		// _delay_ms(50);

		// fill_screen(0, 0, 200);
		// _delay_ms(50);

		set_foreground_color(100, 0, 0);

		print_string(str_score, 0, 0, 0);
		_delay_ms(50);

		print_string(str_lives, 150, 0, 0);
		_delay_ms(50);

		set_foreground_color(0, 200, 0);

		if ((PIND & (1 << PD6)) == 0) {
			PORTD |= (1 << PD7);

			_x1 += offset;
			_x2 += offset;

		}
		else {
			PORTD &= ~(1 << PD7);
		}

		draw_filled_rectangle(_x1, _y1, _x2, _y2);
		_delay_ms(10);

	}

	return 0;
}
