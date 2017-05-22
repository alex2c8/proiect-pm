// LCD library
#include "display_lib.h"
// QTouch library
#include "touch.h"
#include "touch_api.h"


#include "font.h"


#define __delay_cycles(n)     __builtin_avr_delay_cycles(n)
#define __enable_interrupt()  sei()

#define GET_SENSOR_STATE(SENSOR_NUMBER) qt_measure_data.qt_touch_status.sensor_states[(SENSOR_NUMBER/8)] & (1 << (SENSOR_NUMBER % 8))
#define GET_ROTOR_SLIDER_POSITION(ROTOR_SLIDER_NUMBER) qt_measure_data.qt_touch_status.rotor_slider_values[ROTOR_SLIDER_NUMBER]

extern void touch_measure();
extern void touch_init( void );
extern void init_system( void );
extern void init_timer_isr(void);
extern void set_timer_period(uint16_t);

/* Timer period in msec. */
uint16_t qt_measurement_period_msec = QT_MEASUREMENT_PERIOD_MS;
uint16_t time_ms_inc=0;

/* flag set by timer ISR when it's time to measure touch */
volatile uint8_t time_to_measure_touch = 0u;

/* current time, set by timer ISR */
volatile uint16_t current_time_ms_touch = 0u;

/* Qtouch record value. */
uint8_t lastvalue = 0;

int main(void)
{
	init_lcd(LANDSCAPE);

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

		set_foreground_color(127, 0, 250);

		draw_filled_rectangle(5, 70, 50, 100);
		_delay_ms(50);
	}

	return 0;
}
