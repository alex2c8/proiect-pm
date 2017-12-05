#include "common.h"

// LCD
#include "lcd.h"
#include "screens.h"

// game logic
#include "game.h"

// fonts
extern uint8_t SmallFont[1144];
extern uint8_t BigFont[3044];


// global variables
uint8_t g_screen_bitmask = (1 << WELCOME_SCREEN);


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

		// reset
		if (isset_bit(g_screen_bitmask, FINISH_SCREEN)) {
			g_screen_bitmask = 0;
			set_bit(g_screen_bitmask, WELCOME_SCREEN);
		}


	}
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
	// activate interrupts for button PD6
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

int main(void)
{
	uint8_t level_status = 0;

	system_init();

	game_init();

	// initially use the big font
	set_font(BigFont);

	// game loop
	while (TRUE) {
		// continuously draw welcome screen until BTN is pressed
		fill_screen(ARCADE_PURPLE);
		while (isset_bit(g_screen_bitmask, WELCOME_SCREEN))
			welcome_screen();
		_delay_ms(10);


		// BTN was pressed, switch to level 1
		if (isset_bit(g_screen_bitmask, LEVEL1_SCREEN)) {
			fill_screen(YELLOW);
			level_splash_screen(1);
		}

		// transition
		reset_colors();
		font_cmpxchg(SmallFont);

		// initialize level 1
		init_level(1);
		while((level_status = loop_level(1)) == LOOP);

		font_cmpxchg(BigFont);
		// reset_colors();


		// draw "You win" / "You lost" screens accordingly
		g_screen_bitmask = (1 << FINISH_SCREEN);

		fill_screen(ARCADE_PURPLE);
		while (isset_bit(g_screen_bitmask, FINISH_SCREEN))
			player_level_finish_screen(g_player.prev_score, level_status == PLAYER_WON);

		// reset
		level_status = 0;
	}

	return 0;
}
