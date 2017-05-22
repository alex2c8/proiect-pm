// LCD library
#include "lcd.h"
// QTouch library
#include "touch.h"
#include "touch_api.h"


#include "font.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define __delay_cycles(n)     __builtin_avr_delay_cycles(n)
#define __enable_interrupt()  sei()

#define GET_SENSOR_STATE(SENSOR_NUMBER) qt_measure_data.qt_touch_status.sensor_states[(SENSOR_NUMBER/8)] & (1 << (SENSOR_NUMBER % 8))
#define GET_ROTOR_SLIDER_POSITION(ROTOR_SLIDER_NUMBER) qt_measure_data.qt_touch_status.rotor_slider_values[ROTOR_SLIDER_NUMBER]

extern void touch_measure();
extern void touch_init( void );
extern void init_system( void );
extern void init_timer_isr(void);
extern void set_timer_period(uint16_t);

// Timer period in msec.
uint16_t qt_measurement_period_msec = QT_MEASUREMENT_PERIOD_MS;
uint16_t time_ms_inc=0;

// flag set by timer ISR when it's time to measure touch
volatile uint8_t time_to_measure_touch = 0u;

// current time, set by timer ISR
volatile uint16_t current_time_ms_touch = 0u;

// Qtouch record value.
uint8_t lastvalue = 0;


int _x1 = 100;
int _x2 = 115;
int _y1 = 70;
int _y2 = 85;
int offset = 2;

char buf[5];

uint8_t qt_val = 0;

static void qtouch_test(void)
{
	MCUCR |= (1u << PUD);
	touch_measure();
    MCUCR &= ~(1u << PUD);

    qt_val = GET_ROTOR_SLIDER_POSITION(0);
}


int main(void)
{
	init_lcd(LANDSCAPE);

	init_system();
	init_timer_isr();
	touch_init();

	set_font(SmallFont);

	char str_score[] = "score: 1337";
	char str_lives[] = "lives: 3";

	fill_screen(0, 0, 0);
	_delay_ms(50);

	while (1) {
		// fill_screen(200, 0, 0);
		// _delay_ms(50);

		// fill_screen(0, 0, 200);
		// _delay_ms(50);

		set_foreground_color(100, 0, 0);

		print_string(str_score, 0, 0, 0);
		_delay_ms(50);

		print_string(str_lives, 150, 0, 0);
		_delay_ms(50);

		set_foreground_color(0, 200, 0);

		qtouch_test();

		itoa(qt_val, buf, 10);
		print_string(buf, 50, 50, 0);
    	_delay_ms(50);
	}

	return 0;
}
