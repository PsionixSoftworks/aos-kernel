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

#ifndef _AOS_TERMINAL_
#define _AOS_TERMINAL_

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>
#include <adamantine/aos-string.h>
#include <kernel/cpu.h>
#include <stdarg.h>

#define NONE				(udword)NULL
#define INFORMATION			0x01
#define WARNING				0x02
#define ERROR				0x03

#define _INFO(...)			terminal_printf("[INFO]: %s\n", __VA_ARGS__);
#define _WARNING(...)		terminal_printf("[WARNING]: %s\n", __VA_ARGS__);
#define _ERROR(...)			terminal_printf("[ERROR]: %s\n", __VA_ARGS__); cpu_halt();
#define _PANIC(msg)			panic(msg, __FILE__, __LINE__);
#define _ASSERT(b) 			((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

typedef struct aos_terminal terminal_t;
struct aos_terminal 
{
	bool				is_initialized;
	ubyte 				fore_color;
	ubyte 				back_color;
	udword 				x;
	udword 				y;
} PACKED;

EXTERN	DEPRECATED void terminal_init(ubyte back_color, ubyte fore_color);
EXTERN 	DEPRECATED void terminal_clear_creen(void);
EXTERN 	DEPRECATED void terminal_print(const string c);
EXTERN 	DEPRECATED void terminal_print_hex(udword value);
EXTERN 	DEPRECATED void terminal_print_dec(dword value);
EXTERN 	DEPRECATED dword terminal_printf(const string format, ...);
EXTERN 	DEPRECATED void terminal_println(void);
EXTERN 	DEPRECATED void terminal_print_value(dword value, ubyte base);
EXTERN 	DEPRECATED char terminal_get_char(char c);
EXTERN 	DEPRECATED string terminal_gets(string str);
EXTERN 	DEPRECATED void terminal_move_cursor(udword x, udword y);
EXTERN 	DEPRECATED udword terminal_get_cursor_x(void);
EXTERN 	DEPRECATED udword terminal_get_cursor_y(void);
EXTERN 	DEPRECATED void panic(const string message, const string file, udword line);
EXTERN 	DEPRECATED void panic_assert(const string file, udword line, const string description);

EXTERN 	void system_log_begin(void);
EXTERN	void system_log_end(void);
EXTERN 	bool system_logf(ubyte severity, string msg, ...);
EXTERN	void system_log_set_back_col(ubyte col);
EXTERN 	void system_log_set_fore_col(ubyte col);
EXTERN 	void system_log_reset_back_col(void);
EXTERN	void system_log_reset_fore_col(void);
EXTERN 	void system_log_clear_back_col(ubyte col);
EXTERN 	void system_log_clear(void);

#endif
