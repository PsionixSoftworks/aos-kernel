#ifndef _MOUNT_H
#define _MOUNT_H

#include <system/types.h>
#include <drivers/device.h>
#include <stdlib.h>
#include <macros.h>

static struct device *fs_dev;

struct filesystem;

struct mount {
    char *point;
    struct filesystem *fs;
    struct device *device;
};

extern struct filesystem *fs_mount(struct device *_device);

/* When valid, should return 0. Otherwise returns -19 */
static inline int
verify_mount_point(void)
{
    struct filesystem *fs = NULL;

    fs = fs_mount(fs_dev);
    if (fs == NULL)
        return -ENODEV;
    return 0;
}

#endif
