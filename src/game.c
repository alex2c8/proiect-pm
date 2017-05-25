#include "game.h"

const uint16_t level_pattern[5] = {
	0xAAAA, // level 1 (odd bits)
	0x5554, // level 2 (even bits)
	0xAEE2, // level 3 (M)
	0xAFEA, // level 4 (double H)
	0xFFFE  // level 5 (full)
};

// 0 is reserved
// 1-15 used to set each rectangle
uint16_t g_blocks_bitmap;

static void arrange_blocks(int level)
{
	int i;
	int lin, col;
	int x1, y1, x2, y2;

	g_blocks_bitmap = level_pattern[level - 1];

	for (i = 1; i <= 15; i++) {
		if (isset_bit(g_blocks_bitmap, i)) {
			lin = (i-1) / COLS;
			col = (i-1) % COLS;

			x1 = BASE_X + col * (WIDTH + GAP);
			y1 = BASE_Y + lin * (HEIGHT + GAP);

			x2 = x1 + WIDTH;
			y2 = y1 + HEIGHT;

			set_foreground_color(100, 100, 20);
			draw_filled_rectangle(x1, y1, x2, y2);
			set_foreground_color(255, 255, 255);
		}
	}
}

// main game logic for given level
bool_t game_level(int level)
{
	arrange_blocks(level);

	// TODO: return false iff #lives = 0
	return TRUE;
}
