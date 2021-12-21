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

struct driver;

struct device {
    char name[MAX_NAME_LENGTH];
    struct driver *driver;

    int(*create)(int);
    int(*destroy)(int);
    int(*install)(int);
};

typedef struct device device_t;
uint32_t device_init(device_t *dev, char *name);

#endif
