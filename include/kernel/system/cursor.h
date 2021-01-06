#ifndef _AOS_TEXT_MODE_CURSOR
#define _AOS_TEXT_MODE_CURSOR

#include <kernel/system/io.h>
#include <stdint.h>

void cursor_enable(uint8_t start, uint8_t end);
void cursor_disable(void);
void cursor_update(uint32_t x, uint32_t y);
uint16_t cursor_get_pos(void);

#endif
