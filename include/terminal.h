/*
 *  File: terminal.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _AOS_TERMINAL_
#define _AOS_TERMINAL_

#include "types.h"
#include "string.h"
#include "cpu.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define INFO(msg)				terminal_printf("[INFO]: %s\n", msg);
#define WARNING(msg)			terminal_printf("[WARNING]: %s\n", msg);
#define ERROR(msg)				terminal_printf("[ERROR]: %s\n", msg); cpu_halt();
#define PANIC(msg, i1, i2)		panic(msg, __FILE__, __LINE__);
#define ASSERT(b) 				((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

struct aos_terminal 
{
	bool is_initialized;
	uint32_t x;
	uint32_t y;
	uint8_t fore_color;
	uint8_t back_color;
} __attribute__((__packed__));
typedef struct aos_terminal terminal_t;

extern void terminal_init(uint8_t back_color, uint8_t fore_color);
extern void terminal_clear_screen(void);
extern void terminal_print(const char *c);
extern int terminal_printf(const char *format, ...);
extern void terminal_println(void);
extern void terminal_print_value(int32_t value, uint8_t base);
extern char terminal_getchar(char c);
extern char *terminal_gets(char *str);
extern void terminal_move_cursor(uint32_t x, uint32_t y);
extern uint32_t terminal_get_cursor_x();
extern uint32_t terminal_get_cursor_y();

extern void panic(const string msg, const string file, uint32_t line);
extern void panic_assert(const char *file, uint32_t line, const char *desc);

#if defined(__cplusplus)
}
#endif

#endif
