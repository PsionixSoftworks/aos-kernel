#ifndef _ADAMANTINE_CURSOR_H
#define _ADAMANTINE_CURSOR_H

#define KERNEL_ONLY

#include <stdint.h>

extern void cursor_enable(uint8_t start, uint8_t end);
extern void cursor_disable(void);
extern void cursor_update(uint32_t x, uint32_t y);
extern uint16_t cursor_get_pos(void);

#endif  // !_ADAMANTINE_CURSOR_H
