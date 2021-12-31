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

extern int fs_mount(char *_path, struct device *_device);

#endif
