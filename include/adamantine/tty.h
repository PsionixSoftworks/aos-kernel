#ifndef _ADAMANTINE_TTY_H
#define _ADAMANTINE_TTY_H

#define KERNEL_ONLY

#include <stdint.h>

#define CURSOR_CMD		0x3D4
#define CURSOR_DATA		0x3D5

typedef struct TTY tty_t;
struct TTY
{
	uint16_t *mode_addr;
	uint8_t background_color;
	uint8_t foreground_color;
	uint8_t x;
	uint8_t y;
};

extern void tty_init(uint16_t *);
extern void tty_clear(void);
extern void tty_putchar(char);
extern void tty_puts(char *);
extern void tty_printf(const char *__restrict, ...);
extern void tty_println(void);
extern void tty_cursor_enable(uint8_t, uint8_t);
extern void tty_cursor_disable(void);
extern void tty_cursor_update(void);
extern void tty_cursor_set_pos(uint8_t, uint8_t);
extern uint16_t tty_cursor_get_pos(void);
extern void tty_set_background(uint8_t);
extern void tty_set_foreground(uint8_t);
extern void tty_set_colors(uint8_t, uint8_t);
extern uint8_t tty_get_background(void);
extern uint8_t tty_get_foreground(void);

#endif