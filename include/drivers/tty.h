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

typedef struct {
    uint8_t background_color;
    uint8_t foreground_color;
    uint32_t pos;
} TTY, *P_TTY;

__GLOBAL KERNEL_API void tty_setup(void);
__GLOBAL KERNEL_API P_VGA k_tty_get_vgahandle(void);
__GLOBAL KERNEL_API void k_tty_initialize(uint32_t _mode);
__GLOBAL KERNEL_API void k_tty_clear(void);
__GLOBAL KERNEL_API void k_tty_putc(char c);
__GLOBAL KERNEL_API void k_tty_puts(char *str);
__GLOBAL KERNEL_API void k_tty_printf(const char *restrict, ...);
__GLOBAL KERNEL_API void k_tty_println(void);
__GLOBAL KERNEL_API void k_tty_cursor_enable(void);
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
