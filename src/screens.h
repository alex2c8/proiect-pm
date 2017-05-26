#ifndef SCREENS_H_
#define SCREENS_H_

#include <stdio.h>

#include "common.h"
#include "lcd.h"

#define BUF_MAX_LEN 30
#define SPLASH_SCREEN_DURATION 1500

// all possible screen states
enum {
	WELCOME_SCREEN,
	LEVEL1_SCREEN,
	LEVEL2_SCREEN,
	LEVEL3_SCREEN,
	LEVEL4_SCREEN,
	LEVEL5_SCREEN,
	FINISH_SCREEN
};


void welcome_screen();
void level_splash_screen(int level);

void player_level_finish_screen(int score, bool_t won);

#endif
