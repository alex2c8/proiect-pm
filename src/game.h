#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include <string.h>
#include "common.h"
#include "lcd.h"

#define BUF_MAX_LEN 30

#define NUM_LEVELS 5

// LINES x COLUMNS grid
#define LINES 5
#define COLUMNS 7

#define BASE_X 15
#define BASE_Y 20
#define GAP 8
#define WIDTH 15
#define HEIGHT 10

bool_t game_level(int level);

typedef struct {
	uint8_t center_x, center_y;
	uint8_t radius;
	uint8_t speed;
} ball_t;

typedef struct {
	uint8_t base_x, base_y;
	uint8_t width, height;
	uint8_t speed;
} paddle_t;

typedef struct {
	uint8_t lives;
	uint16_t score;
} player_t;


player_t g_player;
paddle_t g_paddle;
ball_t g_ball;

#endif
