#ifndef _DEVICE_H
#define _DEVICE_H

#include <macros.h>
#include <stdint.h>

#define DEVICE_TYPE_KEYBOARD    0x00
#define DEVICE_TYPE_MOUSE       0x01
#define DEVICE_TYPE_USB         0x02
#define DEVICE_TYPE_ETHERNET    0x03
#define DEVICE_TYPE_DATA_DISK   0x04
#define DEVICE_TYPE_PCI_BUS     0x05

#define DEV_TYPE_UNKNOWN    0
#define DEV_TYPE_BLOCK      1
#define DEV_TYPE_CHAR       2

#define MAX_DEVICES         32

struct device {
    int type;
    int subtype;

    size_t (*read)(struct device *, void *, size_t);
    size_t (*write)(struct device *, void *, size_t);

    unsigned long pos;
    char *name;
    void *priv;
};

extern struct device *block_devices[];
#define for_each_blockdev(dev) \
    for (int i = 0; (dev = block_devices[i] != NULL) && (i < MAX_DEVICES); i++)

void device_register(struct device *);
void device_initialize(void);
void device_seek(struct device *, int);

#endif
