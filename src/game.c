#include "game.h"

#include <math.h>

char g_buffer[BUF_MAX_LEN];


const uint16_t level_pattern[5] = {
	0xAAAA, // level 1 (odd bits)
	0x5554, // level 2 (even bits)
	0xAEE2, // level 3 (M)
	0xAFEA, // level 4 (double H)
	0xFFFE  // level 5 (full)
};


uint8_t level1_bitmap[LINES + 1][COLUMNS] = {
	{30, 20, 15, 10, 8},   // base_x, base_y, width, height, gap
	{1, 0, 1, 0, 1, 0, 1}, // line 1
	{0, 1, 0, 1, 0, 1, 0}, // line 2
	{1, 0, 1, 0, 1, 0, 1}, // line 3
	{0, 1, 0, 1, 0, 1, 0}, // line 4
	{1, 0, 1, 0, 1, 0, 1}  // line 5
};

uint8_t level_bitmap_shadow[LINES][COLUMNS] = {
	{0, 0, 0, 0, 0, 0, 0}, // line 1
	{0, 0, 0, 0, 0, 0, 0}, // line 2
	{0, 0, 0, 0, 0, 0, 0}, // line 3
	{0, 0, 0, 0, 0, 0, 0}, // line 4
	{0, 0, 0, 0, 0, 0, 0}  // line 5
};

#define get_level1_base_x level1_bitmap[0][0]
#define get_level1_base_y level1_bitmap[0][1]
#define get_level1_width level1_bitmap[0][2]
#define get_level1_height level1_bitmap[0][3]
#define get_level1_gap level1_bitmap[0][4]


int remaining_blocks;

// TODO
uint8_t **level_bitmap;

// static functions
static void get_accelerometer_data(void);

static void reset_player(void)
{
	g_player.lives = 3;
	g_player.score = 0;
}

static void reset_paddle(void)
{
	g_paddle.width = 40;
	g_paddle.height = 8;
	g_paddle.speed = 30;
	g_paddle.base_x = DISPLAY_Y_SIZE / 2 - g_paddle.width / 2;
	g_paddle.base_y = DISPLAY_X_SIZE - 1 - g_paddle.height;
}

static void reset_ball(void)
{
	g_ball.radius = 4;
	g_ball.speed_x = 5;
	g_ball.speed_y = 5;
	g_ball.center_x = g_paddle.base_x + g_paddle.width / 2;
	g_ball.center_y = g_paddle.base_y - 4 - g_ball.radius / 2;
}

static void clear_paddle_area(void)
{
	set_foreground_color(g_bcolor_red, g_bcolor_green, g_bcolor_blue);

	draw_filled_rectangle(0, g_paddle.base_y - 10, DISPLAY_Y_SIZE, DISPLAY_X_SIZE);

	set_foreground_color(WHITE);
}

static void restore_level_bitmap(int level)
{
	// suppress warning
	(void)level;

	int i, j;

	for (i = 1; i < LINES + 1; i++) {
		for (j = 0; j < COLUMNS; j++) {
			level1_bitmap[i][j] |= level_bitmap_shadow[i-1][j];

			// clear
			level_bitmap_shadow[i-1][j] = 0;
		}
	}
}


void game_init(void)
{
	// init player
	reset_player();

	// init paddle
	reset_paddle();

	// init ball
	reset_ball();

	// TODO: fix this
	remaining_blocks = 18;
}

// each time ball falls off the screen
static void redraw_num_lives(void)
{
	sprintf(g_buffer, "%d", g_player.lives);
	print_string(g_buffer, 210, 1, 0);
}

// each time a ball-block collision is detcted
static void redraw_score(void)
{
	sprintf(g_buffer, "%d", g_player.score);
	print_string(g_buffer, 1, 1, 0);
}

void init_level(int level)
{
	sprintf(g_buffer, "%d", g_player.score);
	print_string(g_buffer, 1, 1, 0);

	sprintf(g_buffer, "LEVEL %d", level);
	print_string(g_buffer, 80, 1, 0);

	sprintf(g_buffer, "%d", g_player.lives);
	print_string(g_buffer, 210, 1, 0);

	// draw block layout for the current level
	arrange_blocks(level);
}


// main game logic for given level
uint8_t loop_level(int level)
{
	handle_paddle();
	_delay_ms(10);

	handle_ball();
	_delay_ms(10);

	if (g_player.lives == 0) {
		g_player.prev_score = g_player.score;

		game_init();
		restore_level_bitmap(level);

		return PLAYER_LOST;
	}

	if (remaining_blocks == 0) {
		g_player.prev_score = g_player.score;

		game_init();
		restore_level_bitmap(level);

		return PLAYER_WON;
	}

	return LOOP;
}



static void get_accelerometer_data(void)
{
	double x = 0, y = 0, z = 0;
	double gxds = 0, gyds = 0, gzds = 0;

	mpu6050_getConvData(&x, &y, &z, &gxds, &gyds, &gzds);

	_delay_ms(ACC_DELAY);


	// LEFT
	if(x < -ACC_THRESHOLD) {
		if (g_paddle.base_x + x * g_paddle.speed >= 2)
			g_paddle.base_x += x * g_paddle.speed;
	}
	// RIGHT
	else if(x > ACC_THRESHOLD) {
		if (g_paddle.base_x + g_paddle.width + x * g_paddle.speed <= DISPLAY_Y_SIZE - 2)
			g_paddle.base_x += x * g_paddle.speed;
	}
}


void arrange_blocks(int level)
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
			// skip inexistent blocks
			if (level1_bitmap[i][j] == 0)
				continue;

			x1 = base_x + j * (width + gap);
			y1 = base_y + (i - 1) * (height + gap);

			x2 = x1 + width;
			y2 = y1 + height;

			set_foreground_color(CYAN);
			draw_filled_rectangle(x1, y1, x2, y2);
			set_foreground_color(WHITE);
		}
	}
}

void handle_paddle(void)
{
	int old_x = g_paddle.base_x;
	int old_y = g_paddle.base_y;

	// TODO
	get_accelerometer_data();


	// clear old paddle
	set_foreground_color(BLACK);

	draw_empty_round_rectangle(old_x, old_y,
		old_x + g_paddle.width, old_y + g_paddle.height);


	// redraw paddle
	set_foreground_color(LIMEISH);

	draw_empty_round_rectangle(
		g_paddle.base_x,
		g_paddle.base_y,
		g_paddle.base_x + g_paddle.width,
		g_paddle.base_y + g_paddle.height
	);

	set_foreground_color(WHITE);
}



static int ball_paddle_delta(void)
{
	bool_t in_right = g_ball.center_x >= g_paddle.base_x;
	bool_t in_left = g_ball.center_x <= g_paddle.base_x + g_paddle.width;

	if (in_right && in_left &&
		(g_ball.center_y + g_ball.radius >= g_paddle.base_y))
		return 1;

	return 0;
}

static int ball_hit_margins(void)
{
	// left
	if (g_ball.center_x <= g_ball.radius)
		return BALL_HIT_SIDE;

	// right
	if (g_ball.center_x >= DISPLAY_Y_SIZE - g_ball.radius)
		return BALL_HIT_SIDE;

	// up
	if (g_ball.center_y <= g_ball.radius + 10)
		return BALL_HIT_CEILING;

	// down => lives--
	if (g_ball.center_y >= DISPLAY_X_SIZE - g_ball.radius)
		return BALL_FELL;

	// no hit
	return 0;
}


static void clear_block(int x1, int y1, int x2, int y2)
{
	set_foreground_color(BLACK);

	draw_filled_rectangle(x1, y1, x2, y2);

	set_foreground_color(WHITE);
}

static bool_t ball_block_collision(void)
{
	int i, j;

	int base_x = level1_bitmap[0][0];
	int base_y = level1_bitmap[0][1];
	int width = level1_bitmap[0][2];
	int height = level1_bitmap[0][3];
	int gap = level1_bitmap[0][4];

	// block coordinates
	int blx, bly;
	// ball coordonates;
	int cx, cy, r;

	cx = g_ball.center_x;
	cy = g_ball.center_y;
	r = g_ball.radius;


	for (i = 1; i < LINES + 1; i++) {
		for (j = 0; j < COLUMNS; j++) {
			// skip inexistent blocks
			if (level1_bitmap[i][j] == 0)
				continue;

			// get current block coordinates
			blx = base_x + j * (width + gap);
			bly = base_y + (i - 1) * (height + gap);

			// if collision => clear block & increment score
			if ((cx + r >= blx) &&
				(cx - r <= blx + width) &&
				(cy + r >= bly) &&
				(cy - r <= bly + height)) {

				clear_block(blx, bly, blx + width, bly + height);

				_delay_ms(10);

				g_player.score += 20;

				remaining_blocks--;

				// disable the current block
				level1_bitmap[i][j] = 0;
				// 'shadow it'
				level_bitmap_shadow[i-1][j] = 1;

				return TRUE;
			}
		}
	}


	return FALSE;
}

void handle_ball(void)
{
	int old_x = g_ball.center_x;
	int old_y = g_ball.center_y;

	float delta;


	// update ball's position
	g_ball.center_x += g_ball.speed_x;
	g_ball.center_y += g_ball.speed_y;


	// check collision with paddle
	delta = ball_paddle_delta();
	if (delta) {
		// TODO: fix this
		g_ball.speed_y *= -1;
	}


	// check collision with screen margins
	switch (ball_hit_margins()) {
		case BALL_HIT_SIDE:
			g_ball.center_x = old_x;
			g_ball.center_y = old_y;
			g_ball.speed_x *= -1;
			break;

		case BALL_HIT_CEILING:
			g_ball.center_x = old_x;
			g_ball.center_y = old_y;
			g_ball.speed_y *= -1;
			break;

		case BALL_FELL:
			g_player.lives--;
			redraw_num_lives();

			if (g_player.lives == 0)
				return;

			// retry
			clear_paddle_area();
			_delay_ms(500);

			reset_paddle();
			reset_ball();
			break;
	}


	// check collision with block
	if (ball_block_collision()) {
		redraw_score();
	}


	// clear old ball
	set_foreground_color(BLACK);

	draw_filled_circle(old_x, old_y, g_ball.radius);


	// redraw ball
	set_foreground_color(RED);

	draw_filled_circle(
		g_ball.center_x,
		g_ball.center_y,
		g_ball.radius
	);

	set_foreground_color(WHITE);
}
