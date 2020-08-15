#ifndef _OUTPUT_
#define _OUTPUT_

#include "types.h"

extern void write_portb(uint16_t port, uint8_t value);	        /* Writes to an 8-Bit port. */
extern void write_portw(uint16_t port, uint16_t value);	        /* Writes to a 16-Bit port. */
extern void write_portl(uint16_t port, uint32_t value);	        /* Writes to a 32-Bit port. */

#endif