#include "game.h"

char g_buffer[BUF_MAX_LEN];


const uint16_t level_pattern[5] = {
	0xAAAA, // level 1 (odd bits)
	0x5554, // level 2 (even bits)
	0xAEE2, // level 3 (M)
	0xAFEA, // level 4 (double H)
	0xFFFE  // level 5 (full)
};

// done
const uint8_t level1_bitmap[LINES + 1][COLUMNS] = {
	{30, 20, 15, 10, 8}, // base_x, base_y, width, height, gap
	{1, 0, 1, 0, 1, 0, 1}, // line 1
	{0, 1, 0, 1, 0, 1, 0}, // line 2
	{1, 0, 1, 0, 1, 0, 1}, // line 3
	{0, 1, 0, 1, 0, 1, 0}, // line 4
	{1, 0, 1, 0, 1, 0, 1}  // line 5
};



// 0 is reserved
// 1-15 used to set each rectangle
uint8_t **level_bitmap;





static void put_status_bar(int level)
{
	// put score
	int score = 1201;
	sprintf(g_buffer, "%d", score);
	print_string(g_buffer, 1, 1, 0);

	// put level name
	sprintf(g_buffer, "Level %d", level);
	print_string(g_buffer, DISPLAY_Y_SIZE / 2 - 20, 1, 0);

	// put lives
	int lives = 2;
	sprintf(g_buffer, "%d", lives);
	print_string(g_buffer, DISPLAY_Y_SIZE - 10, 1, 0);
}


static void handle_blocks(int level)
{
	int i, j;
	int x1, y1, x2, y2;

	//g_blocks_bitmap = level_pattern[level - 1];
	int base_x = level1_bitmap[0][0];
	int base_y = level1_bitmap[0][1];
	int width = level1_bitmap[0][2];
	int height = level1_bitmap[0][3];
	int gap = level1_bitmap[0][4];

	for (i = 1; i < LINES + 1; i++) {
		for (j = 0; j < COLUMNS; j++) {
			if (level1_bitmap[i][j] == 1) {
				x1 = base_x + j * (width + gap);
				y1 = base_y + (i - 1) * (height + gap);

				x2 = x1 + width;
				y2 = y1 + height;

				set_foreground_color(TEAL);
				draw_filled_rectangle(x1, y1, x2, y2);
				set_foreground_color(255, 255, 255);
			}
		}
	}
}

static void handle_paddle(void)
{
	// TODO

	set_foreground_color(LIMEISH);

	draw_empty_round_rectangle(
		g_paddle.base_x,
		g_paddle.base_y,
		g_paddle.base_x + g_paddle.width,
		g_paddle.base_y + g_paddle.height
	);

	set_foreground_color(WHITE);
}

static void handle_ball(void)
{
	// TODO

	set_foreground_color(GREY);

	draw_empty_circle(
		g_ball.center_x,
		g_ball.center_y,
		g_ball.radius
	);

	set_foreground_color(WHITE);
}


// main game logic for given level
bool_t game_level(int level)
{
	put_status_bar(level);
	handle_blocks(level);

	handle_paddle();
	handle_ball();


	// TODO: return false iff #lives = 0
	return TRUE;
}
