#include "lcd.h"

void LCD_Writ_Bus(char VH, char VL, uint8_t mode)
{
	if (VH == 1)
		sbi(PORTB, (1 << PB0));
	else
		cbi(PORTB, (1 << PB0));
	pulse_low(PORTB, (1 << PB1));


	if (VL & 0x80)
		sbi(PORTB, (1 << PB0));
	else
		cbi(PORTB, (1 << PB0));
	pulse_low(PORTB, (1 << PB1));

	if (VL & 0x40)
		sbi(PORTB, (1 << PB0));
	else
		cbi(PORTB, (1 << PB0));
	pulse_low(PORTB, (1 << PB1));

	if (VL & 0x20)
		sbi(PORTB, (1 << PB0));
	else
		cbi(PORTB, (1 << PB0));
	pulse_low(PORTB, (1 << PB1));

	if (VL & 0x10)
		sbi(PORTB, (1 << PB0));
	else
		cbi(PORTB, (1 << PB0));
	pulse_low(PORTB, (1 << PB1));

	if (VL & 0x08)
		sbi(PORTB, (1 << PB0));
	else
		cbi(PORTB, (1 << PB0));
	pulse_low(PORTB, (1 << PB1));

	if (VL & 0x04)
		sbi(PORTB, (1 << PB0));
	else
		cbi(PORTB, (1 << PB0));
	pulse_low(PORTB, (1 << PB1));

	if (VL & 0x02)
		sbi(PORTB, (1 << PB0));
	else
		cbi(PORTB, (1 << PB0));
	pulse_low(PORTB, (1 << PB1));

	if (VL & 0x01)
		sbi(PORTB, (1 << PB0));
	else
		cbi(PORTB, (1 << PB0));
	pulse_low(PORTB, (1 << PB1));
}

void LCD_Write_COM(char VL)
{
	LCD_Writ_Bus(0x00, VL, DISPLAY_TRANSFER_MODE);
}

void LCD_Write_DATA_hl(char VH,char VL)
{
	LCD_Writ_Bus(0x01, VH, DISPLAY_TRANSFER_MODE);
	LCD_Writ_Bus(0x01, VL, DISPLAY_TRANSFER_MODE);
}

void LCD_Write_DATA(char VL)
{
	LCD_Writ_Bus(0x01 , VL, DISPLAY_TRANSFER_MODE);
}

void LCD_Write_COM_DATA(char com1, int dat1)
{
    LCD_Write_COM(com1);
    LCD_Write_DATA_hl(dat1 >> 8 , dat1);
}

void _set_direction_registers(uint8_t mode)
{
	DDRD = 0xFF;
	if (mode == 16) {
		DDRB |= 0x3F;
		DDRC |= 0x03;
	}
}



void _low_level_init()
{
	sbi(PORTB, (1 << PB3));
	_delay_ms(5);
	cbi(PORTB, (1 << PB3));
	_delay_ms(15);
	sbi(PORTB, (1 << PB3));
	_delay_ms(15);

	cbi(PORTB, (1 << PB4));

	LCD_Write_COM(0xC1);
	LCD_Write_DATA(0xFF);
	LCD_Write_DATA(0x83);
	LCD_Write_DATA(0x40);
	LCD_Write_COM(0x11);
	_delay_ms(100);
	LCD_Write_COM(0xCA);
	LCD_Write_DATA(0x70);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0xD9);
	LCD_Write_DATA(0x01);
	LCD_Write_DATA(0x11);

	LCD_Write_COM(0xC9);
	LCD_Write_DATA(0x90);
	LCD_Write_DATA(0x49);
	LCD_Write_DATA(0x10);
	LCD_Write_DATA(0x28);
	LCD_Write_DATA(0x28);
	LCD_Write_DATA(0x10);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x06);
	_delay_ms(20);
	LCD_Write_COM(0xC2);
	LCD_Write_DATA(0x60);
	LCD_Write_DATA(0x71);
	LCD_Write_DATA(0x01);
	LCD_Write_DATA(0x0E);
	LCD_Write_DATA(0x05);
	LCD_Write_DATA(0x02);
	LCD_Write_DATA(0x09);
	LCD_Write_DATA(0x31);
	LCD_Write_DATA(0x0A);

	LCD_Write_COM(0xc3);
	LCD_Write_DATA(0x67);
	LCD_Write_DATA(0x30);
	LCD_Write_DATA(0x61);
	LCD_Write_DATA(0x17);
	LCD_Write_DATA(0x48);
	LCD_Write_DATA(0x07);
	LCD_Write_DATA(0x05);
	LCD_Write_DATA(0x33);
	_delay_ms(10);
	LCD_Write_COM(0xB5);
	LCD_Write_DATA(0x35);
	LCD_Write_DATA(0x20);
	LCD_Write_DATA(0x45);

	LCD_Write_COM(0xB4);
	LCD_Write_DATA(0x33);
	LCD_Write_DATA(0x25);
	LCD_Write_DATA(0x4c);
	_delay_ms(10);
	LCD_Write_COM(0x3a);
	LCD_Write_DATA(0x05);
	LCD_Write_COM(0x29);
	_delay_ms(10);
	LCD_Write_COM(0x2a);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0xaf);
	LCD_Write_COM(0x2b);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0xdb);
	LCD_Write_COM(0x2c);

	sbi (PORTB, (1 << PB4));
}

void init_lcd(uint8_t orientation)
{
	g_disp_orient = orientation;

	// SDA is on PB0
	DDRB |= (1 << PB0);
	// SCL is on PB1
	DDRB |= (1 << PB1);
	// CS (SS) is on PB4
	DDRB |= (1 << PB4);
	// RST is on PB3
	DDRB |= (1 << PB3);

	_low_level_init();

	set_foreground_color(255, 255, 255);
	set_background_color(0, 0, 0);
}



void setXY(word_t x1, word_t y1, word_t x2, word_t y2)
{
	if (g_disp_orient == LANDSCAPE)
	{
		swap(word_t, x1, y1);
		swap(word_t, x2, y2)
		y1 = DISPLAY_Y_SIZE - y1;
		y2 = DISPLAY_Y_SIZE - y2;
		swap(word_t, y1, y2)
	}

	LCD_Write_COM(0x2a);
  	LCD_Write_DATA(x1>>8);
  	LCD_Write_DATA(x1);
  	LCD_Write_DATA(x2>>8);
  	LCD_Write_DATA(x2);
	LCD_Write_COM(0x2b);
  	LCD_Write_DATA(y1>>8);
  	LCD_Write_DATA(y1);
  	LCD_Write_DATA(y2>>8);
  	LCD_Write_DATA(y2);
	LCD_Write_COM(0x2c);
}

void resetXY()
{
	if (g_disp_orient == PORTRAIT)
		setXY(0, 0, DISPLAY_X_SIZE, DISPLAY_Y_SIZE);
	else
		setXY(0, 0, DISPLAY_Y_SIZE, DISPLAY_X_SIZE);
}



void fill_screen(uint8_t r, uint8_t g, uint8_t b)
{
	long i;
	long screen_size;
	char ch, cl;

	ch = ((r & 248) | g >> 5);
	cl = ((g & 28) << 3 | b >> 3);

	cbi(PORTB, (1 << PB4));
	resetXY();

	screen_size = ((long)DISPLAY_X_SIZE + 1) * ((long)DISPLAY_Y_SIZE + 1);

	for (i = 0; i < screen_size; i++) {
		LCD_Writ_Bus(1, ch, DISPLAY_TRANSFER_MODE);
		LCD_Writ_Bus(1, cl, DISPLAY_TRANSFER_MODE);
	}

	sbi(PORTB, (1 << PB4));
}

void clear_screen()
{
	long i;
	long screen_size;

	cbi(PORTB, (1 << PB4));
	resetXY();

	screen_size = ((long)DISPLAY_X_SIZE + 1) * ((long)DISPLAY_Y_SIZE + 1);

	for (i = 0; i < screen_size; i++) {
		LCD_Writ_Bus(1, 0, DISPLAY_TRANSFER_MODE);
		LCD_Writ_Bus(1, 0, DISPLAY_TRANSFER_MODE);
	}

	sbi(PORTB, (1 << PB4));
}

void clear_region(word_t x1, word_t y1, word_t x2, word_t y2)
{
	uint8_t old_r = g_fcolor_red;
	uint8_t old_g = g_fcolor_green;
	uint8_t old_b = g_fcolor_blue;

	set_foreground_color(g_bcolor_red, g_bcolor_green, g_bcolor_blue);

	draw_empty_round_rectangle(x1, y1, x2, y2);

	set_foreground_color(old_r, old_g, old_b);
}


void set_pixel(uint8_t r, uint8_t g, uint8_t b)
{
	// rrrrr gggggg bbbbb
	LCD_Write_DATA_hl(((r & 248) | g >> 5), ((g & 28) << 3 | b >> 3));
}

void draw_pixel(int x, int y)
{
	cbi(PORTB, (1 << PB4));

	setXY(x, y, x, y);

	set_pixel(g_fcolor_red, g_fcolor_green, g_fcolor_blue);

	sbi(PORTB, (1 << PB4));

	resetXY();
}


void set_foreground_color(uint8_t r, uint8_t g, uint8_t b)
{
	g_fcolor_red = r;
	g_fcolor_green = g;
	g_fcolor_blue = b;
}

void set_background_color(uint8_t r, uint8_t g, uint8_t b)
{
	g_bcolor_red = r;
	g_bcolor_green = g;
	g_bcolor_blue = b;
}



void set_font(uint8_t *font)
{
	g_font.font = font;
	g_font.x_size = fontbyte(0);
	g_font.y_size = fontbyte(1);
	g_font.offset = fontbyte(2);
	g_font.numchars = fontbyte(3);
}

void font_cmpxchg(uint8_t *font)
{
	if (g_font.font == font)
		return;

	set_font(font);
}

void print_char(uint8_t c, int x, int y)
{
	uint8_t i, ch;
	word_t j, k;
	word_t temp;

	cbi(PORTB, (1 << PB4));

	if (g_disp_orient == PORTRAIT) {
		setXY(x, y, x + g_font.x_size - 1, y + g_font.y_size - 1);

		temp = ((c-g_font.offset) * ((g_font.x_size/8) * g_font.y_size)) + 4;

		for (j = 0; j < ((g_font.x_size/8) * g_font.y_size); j++) {

			ch = pgm_read_byte(&g_font.font[temp]);

			for (i = 0; i < 8; i++) {
				if ((ch & (1 << (7 - i))) != 0)
					set_pixel(g_fcolor_red, g_fcolor_green, g_fcolor_blue);
				else
					set_pixel(g_bcolor_red, g_bcolor_green, g_bcolor_blue);
			}

			temp++;
		}
	}
	// orientation == LANDSCAPE
	else {
		temp = ((c-g_font.offset) * ((g_font.x_size/8) * g_font.y_size)) + 4;

		for (j = 0; j < ((g_font.x_size/8)*g_font.y_size); j += (g_font.x_size/8)) {

			setXY(x, y + (j/(g_font.x_size/8)), x + g_font.x_size-1, y + (j/(g_font.x_size/8)));

			for (k = (g_font.x_size/8) - 1; k >= 0; k--) {

				ch = pgm_read_byte(&g_font.font[temp+k]);

				for (i = 0; i < 8; i++)
				{
					if ((ch & (1 << i)) != 0)
						set_pixel(g_fcolor_red, g_fcolor_green, g_fcolor_blue);
					else
						set_pixel(g_bcolor_red, g_bcolor_green, g_bcolor_blue);
				}
			}

			temp += (g_font.x_size / 8);
		}
	}

	sbi(PORTB, (1 << PB4));
	resetXY();
}

void print_string(char *st, int x, int y, int deg)
{
	int stl, i;

	stl = strlen(st);

	if (g_disp_orient == PORTRAIT) {
		if (x == RIGHT)
			x = (DISPLAY_X_SIZE + 1) - (stl * g_font.x_size);

		if (x == CENTER)
			x = ((DISPLAY_X_SIZE + 1) - (stl * g_font.x_size)) / 2;
	}
	// orientation == LANDSCAPE
	else
	{
		if (x == RIGHT)
			x = (DISPLAY_Y_SIZE + 1) - (stl * g_font.x_size);

		if (x == CENTER)
			x = ((DISPLAY_Y_SIZE + 1) - (stl * g_font.x_size)) / 2;
	}

	for (i = 0; i < stl; i++) {
		if (deg == 0)
			print_char(*st++, x + (i * (g_font.x_size)), y);
		// else
		// 	rotateChar(*st++, x, y, i, deg);
	}
}



void draw_straight_line(int x, int y, int l, int type)
{
	int i;
	char ch, cl;

	int limit = l;

	ch = ((g_fcolor_red & 248) | g_fcolor_green >> 5);
	cl = ((g_fcolor_green & 28) << 3 | g_fcolor_blue >> 3);

	cbi(PORTB, (1 << PB4));

	if (type == HORIZONTAL_LINE) {
		limit = l + 1;
		setXY(x, y, x + l, y);
	} else if (type == VERTICAL_LINE) {
		limit = l;
		setXY(x, y, x, y + l);
	}

	for (i = 0; i < limit; i++)
		LCD_Write_DATA_hl(ch, cl);

	sbi(PORTB, (1 << PB4));
	resetXY();
}

void draw_empty_rectangle(int x1, int y1, int x2, int y2)
{
	if (x1 > x2)
		swap(int, x1, x2);

	if (y1 > y2)
		swap(int, y1, y2);

	draw_straight_line(x1, y1, x2 - x1, HORIZONTAL_LINE);
	draw_straight_line(x1, y2, x2 - x1, HORIZONTAL_LINE);
	draw_straight_line(x1, y1, y2 - y1, VERTICAL_LINE);
	draw_straight_line(x2, y1, y2 - y1, VERTICAL_LINE);
}


void draw_filled_rectangle(int x1, int y1, int x2, int y2)
{
	int i;

	if (x1 > x2)
		swap(int, x1, x2);

	if (y1 > y2)
		swap(int, y1, y2);

	if (g_disp_orient == PORTRAIT) {
		for (i = 0; i < ((y2 - y1) / 2) + 1; i++) {
			draw_straight_line(x1, y1 + i, x2 - x1, HORIZONTAL_LINE);
			draw_straight_line(x1, y2 - i, x2 - x1, HORIZONTAL_LINE);
		}
	} else {
		for (i = 0; i < ((x2 - x1) / 2) + 1; i++) {
			draw_straight_line(x1 + i, y1, y2 - y1, VERTICAL_LINE);
			draw_straight_line(x2 - i, y1, y2 - y1, VERTICAL_LINE);
		}
	}
}

void draw_empty_round_rectangle(int x1, int y1, int x2, int y2)
{
	if (x1 > x2)
		swap(int, x1, x2);

	if (y1 > y2)
		swap(int, y1, y2);

	if ((x2 - x1) > 4 && (y2 - y1) > 4)
	{
		draw_pixel(x1+1,y1+1);
		draw_pixel(x2-1,y1+1);
		draw_pixel(x1+1,y2-1);
		draw_pixel(x2-1,y2-1);

		draw_straight_line(x1+2, y1, x2-x1-4, HORIZONTAL_LINE);
		draw_straight_line(x1+2, y2, x2-x1-4, HORIZONTAL_LINE);
		draw_straight_line(x1, y1+2, y2-y1-4, VERTICAL_LINE);
		draw_straight_line(x2, y1+2, y2-y1-4, VERTICAL_LINE);
	}
}

void draw_empty_circle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
	char ch, cl;

	ch = ((g_fcolor_red & 248) | g_fcolor_green >> 5);
	cl = ((g_fcolor_green & 28) << 3 | g_fcolor_blue >> 3);

	cbi(PORTB, (1 << PB4));
	setXY(x, y + radius, x, y + radius);
	LCD_Write_DATA_hl(ch,cl);
	setXY(x, y - radius, x, y - radius);
	LCD_Write_DATA_hl(ch,cl);
	setXY(x + radius, y, x + radius, y);
	LCD_Write_DATA_hl(ch,cl);
	setXY(x - radius, y, x - radius, y);
	LCD_Write_DATA_hl(ch,cl);

	while(x1 < y1) {
		if(f >= 0) {
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;
		setXY(x + x1, y + y1, x + x1, y + y1);
		LCD_Write_DATA_hl(ch,cl);
		setXY(x - x1, y + y1, x - x1, y + y1);
		LCD_Write_DATA_hl(ch,cl);
		setXY(x + x1, y - y1, x + x1, y - y1);
		LCD_Write_DATA_hl(ch,cl);
		setXY(x - x1, y - y1, x - x1, y - y1);
		LCD_Write_DATA_hl(ch,cl);
		setXY(x + y1, y + x1, x + y1, y + x1);
		LCD_Write_DATA_hl(ch,cl);
		setXY(x - y1, y + x1, x - y1, y + x1);
		LCD_Write_DATA_hl(ch,cl);
		setXY(x + y1, y - x1, x + y1, y - x1);
		LCD_Write_DATA_hl(ch,cl);
		setXY(x - y1, y - x1, x - y1, y - x1);
		LCD_Write_DATA_hl(ch,cl);
	}
	sbi(PORTB, (1 << PB4));
	resetXY();
}

void draw_filled_circle(int x, int y, int radius)
{
	int x1, y1;

	int r2 = radius * radius;

	cbi(PORTB, (1 << PB4));

	for(y1 = -radius; y1 <= radius; y1++)
		for(x1 = -radius; x1 <= radius; x1++)
			if(x1 * x1 + y1 * y1 <= r2) {
				setXY(x + x1, y + y1, x + x1, y + y1);

				LCD_Write_DATA_hl(
					((g_fcolor_red & 248) | g_fcolor_green >> 5),
					((g_fcolor_green & 28) << 3 | g_fcolor_blue >> 3));
			}

	sbi(PORTB, (1 << PB4));

	resetXY();
}
