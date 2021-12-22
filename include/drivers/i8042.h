#ifndef _ADAMANTINE_I8042_H
#define _ADAMANTINE_I8042_H

#include <stdint.h>

#define I8042_DATA      0x60        /* Read/Write */
#define I8042_STATUS    0x64        /* Read */
#define I8042_COMMAND   0x64        /* Write */

unsigned char i8042_kb_initialize(void);
uint8_t i8042_read_status_register(void);
unsigned char i8042_read_data(void);

#endif
