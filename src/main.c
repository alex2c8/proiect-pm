#include "common.h"

// LCD
#include "lcd.h"
#include "screens.h"

// accelerometer
#include "mpu6050/mpu6050.h"

// game logic
#include "game.h"

// fonts
extern uint8_t SmallFont[1144];
extern uint8_t BigFont[3044];


// defines
#define LIMIT 0.2



// global variables
uint8_t g_screen_bitmask = (1 << WELCOME_SCREEN);


int width = 20;
int height = 15;

int _x1 = 1;
int _x2 = 61;
int _y1 = DISPLAY_X_SIZE - 10;
int _y2 = DISPLAY_X_SIZE;

int offset = 12;

// routine for interrupt on PD6
ISR(PCINT3_vect)
{
	// TODO: switch state based on bit state
	if ((PIND & (1 << PD6)) == 0) {

		// led switch (indicator)
		PORTD ^= (1 << PD7);

		// welcome screen -> level 1
		if (isset_bit(g_screen_bitmask, WELCOME_SCREEN)) {
			g_screen_bitmask = 0;
			set_bit(g_screen_bitmask, LEVEL1_SCREEN);
		}


	}
}


uint8_t acc_test()
{
	uint8_t r = 0;

	double x = 0;
	double y = 0;
	double z = 0;
	double gxds = 0;
	double gyds = 0;
	double gzds = 0;

	mpu6050_getConvData(&x, &y, &z, &gxds, &gyds, &gzds);

	_delay_ms(50);

	// // UP
	// if(x > LIMIT) {
	// 	_y1 -= offset;
	// 	_y2 -= offset;
	// 	r = 1;
	// }
	// // DOWN
	// else if(x < -LIMIT) {
	// 	_y1 += offset;
	// 	_y2 += offset;
	// 	r = 1;
	// }

	// LEFT
	if(y > LIMIT) {
		if (_x1 - y * offset >= 0) {
			_x1 -= y * offset;
			_x2 -= y * offset;
			r = 1;
		}
	}
	// RIGHT
	else if(y < -LIMIT) {
		if (_x2 -y * offset <= DISPLAY_Y_SIZE) {
			_x1 += -y * offset;
			_x2 += -y * offset;
			r = 1;
		}
	}

	return r;
}

static void IO_init(void)
{
	// set PD6 button as input
	DDRD &= ~(1 << PD6);
	// set pull-up
	PORTD |= (1 << PD6);

	// set PD7 led as output
	DDRD |= (1 << PD7);
	PORTD &= ~(1 << PD7);
}

static void interrupts_init(void)
{
	// activate interrupts of button PD6
	PCICR = (1 << PCIE3);
	PCMSK3 = (1 << PCINT30);
}

// initialize entire system
static void system_init(void)
{
	// initialize LCD
	init_lcd(LANDSCAPE);

	// enable interrupts
	sei();

	IO_init();
	interrupts_init();

	// initialize accelerometer
	mpu6050_init();
}

static void reset_colors(void)
{
	set_background_color(BLACK);
	set_foreground_color(WHITE);

	fill_screen(BLACK);
}

static void game_init(void)
{
	// init player
	g_player.lives = 3;
	g_player.score = 0;

	// init paddle
	g_paddle.width = 40;
	g_paddle.height = 8;
	g_paddle.speed = 12;
	g_paddle.base_x = DISPLAY_Y_SIZE / 2 - g_paddle.width / 2;
	g_paddle.base_y = DISPLAY_X_SIZE - 1 - g_paddle.height;

	// init ball
	g_ball.radius = 4;
	g_ball.speed = 12;
	g_ball.center_x = g_paddle.base_x + g_paddle.width / 2;
	g_ball.center_y = g_paddle.base_y - 3 - g_ball.radius / 2;
}

int main(void)
{
	srand(1337);

	system_init();

	game_init();

	// initially use the big font
	set_font(BigFont);

	for (; ;) {
		// continuously draw welcome screen until BTN is pressed
		fill_screen(ARCADE_PURPLE);
		while (isset_bit(g_screen_bitmask, WELCOME_SCREEN))
			welcome_screen();
		_delay_ms(10);


		// BTN was pressed, switch to level 1
		if (isset_bit(g_screen_bitmask, LEVEL1_SCREEN)) {
			fill_screen(TEAL);
			level_splash_screen(1);
		}

		// transition
		reset_colors();
		font_cmpxchg(SmallFont);

		// start level 1
		while(game_level(1));





		// reset
		_delay_ms(10);
		g_screen_bitmask = (1 << WELCOME_SCREEN);
	}

	return 0;
}
