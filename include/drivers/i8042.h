#ifndef _ADAMANTINE_I8042_H
#define _ADAMANTINE_I8042_H

#define KERNEL_ONLY

//#include <adamantine/adamantine.h>
#include <system/portio.h>
#include <drivers/driver.h>
#include <kernel/isr.h>
#include <kernel/irq.h>
#include <common.h>

/* Define macros */
#define DATA_PORT				0x60					// Read/Write
#define STATUS_REGISTER			0x64					// Read Only
#define COMMAND_REGISTER		0x64					// Write Only

static inline void
i8042_keyboard_initialize(void *cb)
{
    register_interrupt_handler(IRQ1, cb);
}

#endif
