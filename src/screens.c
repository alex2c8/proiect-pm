#include "screens.h"

char g_buffer[BUF_MAX_LEN];

static void reset_fb_colors()
{
	set_foreground_color(WHITE);
	set_background_color(BLACK);
}

void welcome_screen()
{
	int y = 30;
	int y_offset = 20;

	set_background_color(ARCADE_PURPLE);

	print_string("Welcome to", 25, y, 0);
	print_string("AVR DX-Ball", 20, y + y_offset, 0);


	print_string("Press BTN", 25, y + 3 * y_offset, 0);
	print_string("to continue", 20, y + 4 * y_offset, 0);
	_delay_ms(500);

	// clear text
	set_foreground_color(ARCADE_PURPLE);
	draw_filled_rectangle(1, y + 3 * y_offset, DISPLAY_Y_SIZE, DISPLAY_X_SIZE);

	reset_fb_colors();
}

static void set_level_bgcolor(int level)
{
	switch (level) {
		case 1:
			set_background_color(TEAL); break;
		// case 2:
		// 	set_background_color(LEVEL2); break;
		// case 3:
		// 	set_background_color(LEVEL3); break;
		// case 4:
		// 	set_background_color(LEVEL4); break;
		// case 5:
		// 	set_background_color(LEVEL5); break;
		default:
			set_background_color(BLACK);
	}
}

void level_splash_screen(int level)
{
	// switch bg color depending on level
	set_level_bgcolor(level);

	// print
	sprintf(g_buffer, "Level %d", level);
	print_string(g_buffer, DISPLAY_Y_SIZE / 2 - 70, DISPLAY_X_SIZE / 2 , 0);

	_delay_ms(SPLASH_SCREEN_DURATION);

	reset_fb_colors();
}
