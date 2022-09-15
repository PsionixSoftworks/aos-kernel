#ifndef _AOSFS_H
#define _AOSFS_H

#include <drivers/device.h>
#include "vfs.h"

extern void aosfs_mount_to_device(struct device* dev, struct fs* fsptr);

#endif
