/*
 *  file: terminal.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _AOS_TERMINAL_H
#define _AOS_TERMINAL_H

#include <adamantine/aos-defs.h>
#include <kernel/drivers/vga.h>

#define DEFAULT_BACKGROUND_COLOR	SYSTEM_COLOR_BLACK
#define DEFAULT_FOREGROUND_COLOR	SYSTEM_COLOR_LT_GREEN

#define PANIC(MESSAGE)			panic(MESSAGE, __FILE__, __LINE__);
#define PANIC_ASSERT(MESSAGE)	panic_assert(__FILE__, __LINE__, MESSAGE);

#if defined(__cplusplus)
extern "C" {
#endif

void terminal_init(void);
void terminal_clear(void);
void terminal_set_background_color(uint8_t color);
void terminal_set_foreground_color(uint8_t color);
void terminal_reset_background_color(void);
void terminal_reset_foreground_color(void);
uint8_t terminal_get_background_color(void);
uint8_t terminal_get_foreground_color(void);
void terminal_print(char * str);
void terminal_printf(const char * str, ...);

void panic(const char * msg, const char * file, uint32_t line);
void panic_assert(const char * file, uint32_t line, const char * description);

#if defined(__cplusplus)
}
#endif

#endif  // !_AOS_TERMINAL_H
