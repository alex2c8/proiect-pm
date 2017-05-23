#ifndef DISPLAY_LIB_H
#define DISPLAY_LIB_H

/* GENERAL MACROS */
#define LEFT 0
#define RIGHT 9999
#define CENTER 9998

#define PORTRAIT 0
#define LANDSCAPE 1

/* HX8340-B (SERIAL) MACROS */
#define HX8340B_S 7
#define ITDB22SP 7

#define SERIAL_4PIN 4
#define SERIAL_5PIN 5

#define DISPLAY_X_SIZE 175L
#define DISPLAY_Y_SIZE 219L
#define DISPLAY_TRANSFER_MODE 1
#define DISPLAY_SERIAL_MODE 4

/* DRAWING MACROS */
#define HORIZONTAL_LINE 100
#define VERTICAL_LINE 101

/* AVR SPECIFIC HEADER */
#include "avr_specific.h"

/* C INCLUDES */
#include <string.h>

/* TYPE ALIASES */
typedef unsigned char uint8_t;
typedef int word_t;

typedef struct {
	uint8_t *font;
	uint8_t x_size, y_size;
	uint8_t offset;
	uint8_t numchars;
} font_t;



/* GLOBAL VARIABLES */
// display orientation
uint8_t g_disp_orient;

// foreground color
uint8_t g_fcolor_red, g_fcolor_green, g_fcolor_blue;

// background color
uint8_t g_bcolor_red, g_bcolor_green, g_bcolor_blue;

// register types and sizes
regtype *P_WR, *P_CS, *P_RST, *P_SDA, *P_SCL;
regsize B_WR, B_CS, B_RST, B_SDA, B_SCL;

// currently selected font
font_t g_font;



/* FUNCTIONS */

// low-level functions
void LCD_Writ_Bus(char VH, char VL, uint8_t mode);

void LCD_Write_COM(char VL);

void LCD_Write_DATA_hl(char VH,char VL);
void LCD_Write_DATA(char VL);

void LCD_Write_COM_DATA(char com1,int dat1);

void _set_direction_registers(uint8_t mode);

void _low_level_init();



// high-level functions (LCD API)
void init_lcd(uint8_t orientation);

void setXY(word_t x1, word_t y1, word_t x2, word_t y2);
void resetXY();

void fill_screen(uint8_t r, uint8_t g, uint8_t b);
void clear_screen();
void clear_region(word_t x1, word_t y1, word_t x2, word_t y2);

void set_pixel(uint8_t r, uint8_t g, uint8_t b);
void draw_pixel(int x, int y);

void set_foreground_color(uint8_t r, uint8_t g, uint8_t b);
void set_background_color(uint8_t r, uint8_t g, uint8_t b);

// text
void set_font(uint8_t *font);
void print_char(uint8_t c, int x, int y);
void print_string(char *st, int x, int y, int deg);

// drawing
void draw_straight_line(int x, int y, int l, int type);
void draw_empty_rectangle(int x1, int y1, int x2, int y2);
void draw_filled_rectangle(int x1, int y1, int x2, int y2);
void draw_empty_round_rectangle(int x1, int y1, int x2, int y2);

#endif
