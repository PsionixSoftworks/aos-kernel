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
    struct device *device;
};

#endif
