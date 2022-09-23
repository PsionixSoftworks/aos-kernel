#ifndef _KERNEL_DRIVER_TTY_H
#define _KERNEL_DRIVER_TTY_H

#include <stdint.h>

struct tty {
    uint8_t background;
    uint8_t foreground;
    uint8_t width;
    uint8_t height;
};

extern uint8_t tty_init(uint16_t* mode);
extern void tty_clear(void);
extern void tty_set_background(uint8_t color);
extern void tty_set_foreground(uint8_t color);
extern void tty_set_colors(uint8_t background, uint8_t foreground);
extern uint8_t tty_get_background(void);
extern uint8_t tty_get_foreground(void);
extern void tty_scroll(void);

#endif