#ifndef GAME_H_
#define GAME_H_

#include "common.h"
#include "lcd.h"

// 3 x 5 grid
#define LINES 3
#define COLS 5

#define BASE_X 10
#define BASE_Y 10
#define GAP 20
#define WIDTH 20
#define HEIGHT 15

bool_t game_level(int level);

#endif
