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

#define DEVICE_SUCCESS  0
#define DEVICE_FAILURE  -1

#ifndef DEVICE_TYPE_MACROS
#define DEVICE_TYPE_OFFSET          0x1000
#define DEVICE_TYPE_SET(x)          (x | DEVICE_TYPE_OFFSET)
#define DEVICE_TYPE_NONE            DT_NONE
#define DEVICE_TYPE_USB             DEVICE_TYPE_SET(DT_USB)
#define DEVICE_TYPE_GRAPHIC_CARD    DEVICE_TYPE_SET(DT_GRAPHIC_CARD)
#define DEVICE_TYPE_IODEV           DEVICE_TYPE_SET(DT_IODEV)
#define DEVICE_TYPE_KEYBOARD        DEVICE_TYPE_SET(DT_KEYBOARD)
#define DEVICE_TYPE_MOUSE           DEVICE_TYPE_SET(DT_MOUSE)
#define DEVICE_TYPE_DISPLAY         DEVICE_TYPE_SET(DT_DISPLAY)
#define DEVICE_TYPE_PCI             DEVICE_TYPE_SET(DT_PCI)
#define DEVICE_TYPE_STORAGE         DEVICE_TYPE_SET(DT_STORAGE)
#define DEVICE_TYPE_TELETYPE        DEVICE_TYPE_SET(DT_TTY)
#endif

#ifndef IO_TYPE_MACROS
#define IO_TYPE_OFFSET              0x2000
#define IO_TYPE_SET(x)              (x | IO_TYPE_OFFSET)
#define IO_TYPE_NONE                IOT_NONE
#define IO_TYPE_SYNC                IO_TYPE_SET(IOT_SYNC)
#define IO_TYPE_ASYNC               IO_TYPE_SET(IOT_ASYNC)
#endif

enum device_type
{
    DT_NONE,
    DT_USB,
    DT_GRAPHIC_CARD,
    DT_IODEV,
    DT_KEYBOARD,
    DT_MOUSE,
    DT_DISPLAY,
    DT_PCI,
    DT_STORAGE,
    DT_TTY,
};

enum io_type
{
    IOT_NONE,
    IOT_SYNC,
    IOT_ASYNC,
};

struct device
{
    long device_id;
    char* device_name;
    enum device_type device_type;
    enum io_type io_type;
    uint16_t* port;
    struct device* next;
};

extern struct device* device_init(struct device*, char [MAX_NAME_LENGTH], enum device_type, enum io_type);  // Returns 0 on success, -1 on failure.
extern uint16_t* device_get_address(struct device*);
extern enum device_type device_get_type(struct device*);
extern char* device_get_type_str(struct device*);
extern uint16_t device_get_type_id(enum device_type);
extern enum io_type device_get_io_type(struct device*);
extern char* device_get_io_type_str(struct device*);
extern uint16_t* device_get_port(struct device*);

#endif
