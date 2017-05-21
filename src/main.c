#include "display_lib.h"
//#include "font.h"

int main(void)
{

	init_lcd(PORTRAIT);

	fill_screen(0, 0, 0);
	_delay_ms(50);

	while (1) {
		fill_screen(200, 0, 0);
		_delay_ms(50);

		fill_screen(0, 0, 200);
		_delay_ms(50);
	}

	return 0;
}
