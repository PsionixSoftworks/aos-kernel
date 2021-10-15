#ifndef _ADAMANTINE_I8042_H
#define _ADAMANTINE_I8042_H

#define KERNEL_ONLY

#include <adamantine/adamantine.h>
#include <system/ioctrl.h>
#include <stdint.h>
#include <drivers/driver.h>

/* Define macros */
#define DATA_PORT				0x60					// Read/Write
#define STATUS_REGISTER			0x64					// Read Only
#define COMMAND_REGISTER		0x64					// Write Only

driver_t keybd_drv;
driver_t mouse_drv;

/* Read an 8-bit value from the status register (read only access) */
static inline uint8_t
i8042_read_status_register(void)
{
	return inb(STATUS_REGISTER);
}

/* Read an 8-bit value from the data port (read/write access) */
static inline uint8_t
i8042_read_data(void)
{
	return inb(DATA_PORT);
}

/* Write some 8-bit data into the data port (read/write) */
static inline void
i8042_write_data(uint8_t data)
{
	outb(DATA_PORT, data);
}

/* Write some 8-bit data to the command register (write only) */
static inline void
i8042_write_command(uint8_t cmd)
{
	outb(COMMAND_REGISTER, cmd);
}

#endif
