/*
 * This file, <drivers/driver.h> is an abstraction of all available device drivers
 * for the system. Similar to the virtual filesystem, this module will act
 * as a base or parent file to all devices that use it.
 */

#ifndef _KERNEL_DRIVER_H
#define _KERNEL_DRIVER_H

#include <macros.h>
#include <kernel/kernel.h>

typedef struct driver driver_t;
typedef struct device device_t;

struct driver {
    /* Initial device name & pointers to other devices */
    char *name[MAX_NAME_LENGTH];
    struct driver *prev;
    struct driver *next;

    /* Function pointers to universal driver bases */
    char *(*driver_name)(void);
    unsigned long (*driver_id)(void);
    int (*driver_open)(struct driver *, void *);
    unsigned int (*driver_read)(struct driver *, void *);
    unsigned int (*driver_write)(struct driver *, void *, unsigned char);
    void (*driver_close)(int, void *);
};

struct device {
    unsigned int device_base;
    unsigned int device_size;
};

KERNEL_API __GLOBAL void driver_init(driver_t *d_ptr, char *name);
KERNEL_API __GLOBAL unsigned long driver_get_id(void);

#endif
