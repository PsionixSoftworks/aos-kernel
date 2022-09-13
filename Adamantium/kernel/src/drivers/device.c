#include <drivers/device.h>
#include <memory/memory-util.h>
#include <string.h>

static inline long __create_new_device(void);

struct device*
device_init(struct device* dev, char name[MAX_NAME_LENGTH], enum device_type device_type, enum io_type io_type)
{
    struct device* parent   = (struct device*)kmalloc(sizeof(struct device*) * MAX_DEVICES);
    dev->device_id          = __create_new_device();

    if (dev->device_id != 0)
    {
        strcpy(dev->device_name, name);
        dev->device_type    = device_type;
        dev->io_type        = io_type;
    }
    
    return parent;
}

/* Don't worry, this will have more to it later. */
static inline long
__create_new_device(void)
{
    static long __id;
    return __id++;
}
