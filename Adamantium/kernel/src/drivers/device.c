#include <drivers/device.h>
#include <memory/memory-util.h>
#include <drivers/vga.h>
#include <system/portio.h>
#include <string.h>

#define DEVICE_START_ID     0       // Could be zero or one, but has to be within the 8-bit limit (for now).

static inline uint8_t __create_new_device(void);

extern uint16_t* vidmode;

struct device*
device_init(struct device* dev, char name[MAX_NAME_LENGTH], enum device_type device_type, enum io_type io_type)
{
    struct device* parent = (struct device*)kmalloc(sizeof(struct device*) * 64);
    memset(parent, 0, sizeof(struct device*) * 64);

    switch (device_type)
    {
    case DT_DISPLAY:
        break;
    case DT_GRAPHIC_CARD:
        break;
    case DT_IODEV:
        break;
    case DT_KEYBOARD:
        break;
    case DT_MOUSE:
        break;
    case DT_PCI:
        break;
    case DT_STORAGE:
        break;
    case DT_TTY:
        dev->device_id      = __create_new_device();
        dev->device_name    = name;
        dev->device_type    = device_type;
        dev->io_type        = io_type;
        dev->port           = (uint16_t*)VGA_ADDRESS;
        break;
    case DT_USB:
        break;
    case DT_NONE:
        break;
    };

    dev->next = parent;

    if (dev->device_id < 0)
        return dev;
    return NULL;
}

uint16_t*
device_get_address(struct device* dev)
{
    return dev->port;
}

enum device_type
device_get_type(struct device* dev)
{
    return dev->device_type;
}

char*
device_get_type_str(struct device* dev)
{
    switch (device_get_type(dev))
    {
    case DT_DISPLAY:
        return "DEVICE_TYPE_DISPLAY";
    case DT_GRAPHIC_CARD:
        return "DEVICE_TYPE_GRAPHIC_CARD";
    case DT_IODEV:
        return "DEVICE_TYPE_IODEV";
    case DT_KEYBOARD:
        return "DEVICE_TYPE_KEYBOARD";
    case DT_MOUSE:
        return "DEVICE_TYPE_MOUSE";
    case DT_PCI:
        return "DEVICE_TYPE_PCI";
    case DT_STORAGE:
        return "DEVICE_TYPE_STORAGE";
    case DT_TTY:
        return "DEVICE_TYPE_TTY";
    case DT_USB:
        return "DEVICE_TYPE_USB";
    default:
        return "DEVICE_TYPE_NONE";
    };
}

uint16_t
device_get_type_id(enum device_type type)
{
    if (type >= 0 && type < 9)
        return DEVICE_TYPE_SET(type);
    return DEVICE_TYPE_NONE;
}

enum io_type
device_get_io_type(struct device* dev)
{
    return dev->io_type;
}

char*
device_get_io_type_str(struct device* dev)
{
    switch (dev->io_type)
    {
    case IOT_SYNC:
        return "IO_TYPE_SYNC";
    case IOT_ASYNC:
        return "IO_TYPE_ASYNC";
    default:
        return IOT_NONE;
    };
}

uint16_t*
device_get_port(struct device* dev)
{
    return dev->port;
}

static uint8_t __id = DEVICE_START_ID;

/* Don't worry, this will have more to it later. */
static inline uint8_t
__create_new_device(void)
{
    return __id++;
}
