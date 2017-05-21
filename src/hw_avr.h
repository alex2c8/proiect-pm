/**
 * Hardware-specific macros and functions
 */

#ifndef HW_AVR_H_
#define HW_AVR_H_

// 16 MHz
#define F_CPU 16000000L

// clear bit
#define cbi(reg, bitmask) *reg &= ~bitmask
// set bit
#define sbi(reg, bitmask) *reg |= bitmask
#define pulse_high(reg, bitmask) sbi(reg, bitmask); cbi(reg, bitmask);
#define pulse_low(reg, bitmask) cbi(reg, bitmask); sbi(reg, bitmask);

#define sport(port, data) port |= data
#define cport(port, data) port &= data

#define swap(type, i, j) {type t = i; i = j; j = t;}

#define fontbyte(x) pgm_read_byte(&g_font.font[x])

#define regtype volatile uint8_t
#define regsize uint8_t
#define bitmapdatatype unsigned int*

#endif
