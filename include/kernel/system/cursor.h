#ifndef _ADAMANTINE_CURSOR_H
#define _ADAMANTINE_CURSOR_H

#include <stdint.h>

void cursor_enable(uint8_t start, uint8_t end);
void cursor_disable(void);
void cursor_update(uint32_t x, uint32_t y);
uint16_t cursor_get_pos(void);

#endif  // !_ADAMANTINE_CURSOR_H
