#ifndef _DEVICE_H
#define _DEVICE_H

#include <stdint.h>
#include <macros.h>

#define MAX_DEVICES     256     // This number is subject to change...

#define DEVICE_BUSY     0
#define DEVICE_RDY      1

#ifndef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH 24
#endif

enum device_type
{
    DT_USB,
    DT_GRAPHIC_CARD,
    DT_IODEV,
    DT_KEYBOARD,
    DT_MOUSE,
    DT_DISPLAY,
    DT_PCI,
    DT_STORAGE,
};

enum io_type
{
    IOT_SYNC,
    IOT_ASYNC,
};

struct device
{
    long device_id;
    char device_name[MAX_NAME_LENGTH];
    enum device_type device_type;
    enum io_type io_type;
    struct device* next;
};

extern struct device* device_init(struct device*, char [MAX_NAME_LENGTH], enum device_type, enum io_type);  // Returns 0 on success, -1 on failure.
extern int8_t device_install(struct device*);                                                       // Returns 0 on success, -1 on failure.

#endif
