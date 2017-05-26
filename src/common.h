#ifndef COMMON_H
#define COMMON_H

// C
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define isset_bit(byte, index) ((byte & (1 << index)) != 0)
#define set_bit(byte, index) (byte |= (1 << index))


// TYPE ALIASES
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef int word_t;
typedef enum {FALSE, TRUE} bool_t;

// COLORS
#define BLACK 0,0,0
#define WHITE 255,255,255

#define ARCADE_PURPLE 140,22,140
#define GREY 110,120,120
#define LIMEISH 0,255,120
#define CYAN 60,230,230
#define RED 220,0,0
#define YELLOW 240,220,70

#define LEVEL2 0,180,0
#define LEVEL3 0,0,180
#define LEVEL4 0,0,180
#define LEVEL5 0,0,180
#define DIED 0,0,180
#define WON 0,0,180

#endif
