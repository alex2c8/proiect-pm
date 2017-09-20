#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include <string.h>

#include "common.h"
#include "lcd.h"

// accelerometer
#include "mpu6050/mpu6050.h"

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

#define BALL_HIT_SIDE 1
#define BALL_HIT_CEILING 2
#define BALL_FELL 3

#define ACC_THRESHOLD 0.06
#define ACC_DELAY 25

#define LOOP 1
#define PLAYER_WON 2
#define PLAYER_LOST 3

#define PI 3.141592f


typedef struct {
	uint8_t center_x, center_y;
	uint8_t radius;
	float speed_x, speed_y;
} ball_t;

typedef struct {
	uint8_t base_x, base_y;
	uint8_t width, height;
	uint8_t speed;
} paddle_t;

typedef struct {
	uint8_t lives;
	uint16_t score;
	uint16_t prev_score;
} player_t;


player_t g_player;
paddle_t g_paddle;
ball_t g_ball;


void game_init(void);

void init_level(int level);
uint8_t loop_level(int level);

void arrange_blocks(int level);
void handle_paddle(void);
void handle_ball(void);

#endif
