/*
 * This file, <drivers/driver.h> is an abstraction of all available device drivers
 * for the system. Similar to the virtual filesystem, this module will act
 * as a base or parent file to all devices that use it.
 */

#ifndef _KERNEL_DRIVER_H
#define _KERNEL_DRIVER_H

#include <kernel/kernel.h>
#include <drivers/device.h>
#include <system/types.h>
#include <macros.h>

struct driver {
    char name[MAX_NAME_LENGTH];
    uid_t id;

    struct driver *(*config)(int);
};
typedef struct driver driver_t;

__GLOBAL KERNEL_API int driver_config(void);        // Setup in main.c.
__GLOBAL KERNEL_API void *device_driver_setup(int (*config_func)(void), int flags);

#endif
