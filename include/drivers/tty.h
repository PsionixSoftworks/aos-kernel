#ifndef _KERNEL_DRIVER_TTY_H
#define _KERNEL_DRIVER_TTY_H

#include <adamantine/adamantine.h>
#include <drivers/vga.h>
#include <macros.h>

#define TTY_VIDEO_MODE      vga_mode.VGA_TEXT_MODE_COLOR
#define TTY_DISPLAY_WIDTH   VGA_WIDTH
#define TTY_DISPLAY_HEIGHT  VGA_HEIGHT

/* Macros for the Text Mode cursor */
#define CURSOR_CMD		0x03D4										// Cursor Command
#define CURSOR_DATA		0x03D5										// Cursor Data

/* Define macros for the Text Mode cusror */
#if defined(CURSOR_TYPE) && (CURSOR_TYPE == 0)						// This will make a block cursor, all others will be an underline (for now).
#define CURSOR_START	0xE											// Top=14
#define CURSOR_END		0xF											// Bottom=15
#else
#define CURSOR_START	0x0											// Top=0
#define CURSOR_END		0xF											// Bottom=15
#endif

typedef unsigned short *vBuff_t;

struct s_tty_in {
    char(*k_getc)(void);
    char *(*k_gets)(void);
};
typedef struct s_tty_in in_t;

struct s_tty_out {
    void(*k_putc)(char c);
    void(*k_puts)(char *str, size_t len);
    void(*k_print)(char *str);
    void(*k_printf)(const char *restrict fmt, ...);
};
typedef struct s_tty_out out_t;

struct s_tty {
    uint16_t *mode_addr;
    vBuff_t vBuff;
    uint32_t tty_rows;
    uint32_t tty_cols;
    uint8_t tty_backcol;
    uint8_t tty_forecol;
    uint8_t tty_cursor_x;
    uint8_t tty_cursor_y;

    in_t in;
    out_t out;
};

__GLOBAL KERNEL_API void k_tty_initialize(uint16_t *mode);
__GLOBAL KERNEL_API void k_tty_clear(void);
__GLOBAL KERNEL_API void k_tty_putc(char c);
__GLOBAL KERNEL_API void k_tty_puts(char *str);
__GLOBAL KERNEL_API void k_tty_printf(const char *restrict fmt, ...);
__GLOBAL KERNEL_API void k_tty_println(void);
__GLOBAL KERNEL_API void k_tty_cursor_enable(uint8_t start, uint8_t end);
__GLOBAL KERNEL_API void k_tty_cursor_disable(void);
__GLOBAL KERNEL_API void k_tty_cursor_update(void);
__GLOBAL KERNEL_API void k_tty_cursor_set_pos(uint8_t x, uint8_t y);
__GLOBAL KERNEL_API uint16_t k_tty_cursor_get_pos(void);
__GLOBAL KERNEL_API void k_tty_set_background(uint8_t _color);
__GLOBAL KERNEL_API void k_tty_set_foreground(uint8_t _color);
__GLOBAL KERNEL_API void k_tty_set_colors(uint8_t _bg, uint8_t _fg);
__GLOBAL KERNEL_API uint8_t k_tty_get_background(void);
__GLOBAL KERNEL_API uint8_t k_tty_get_foreground(void);
__GLOBAL KERNEL_API void k_tty_scroll(void);

__GLOBAL KERNEL_API void panic(const char *_message, const char *_file, uint32_t _line);
__GLOBAL KERNEL_API void panic_assert(const char *_file, uint32_t _line, const char *_desc);

#endif
