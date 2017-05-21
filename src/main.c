#include "display_lib.h"
#include "font.h"

int main(void)
{
	init_lcd(LANDSCAPE);

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

		set_foreground_color(127, 0, 250);

		draw_filled_rectangle(5, 70, 50, 100);
		_delay_ms(50);
	}

	return 0;
}
