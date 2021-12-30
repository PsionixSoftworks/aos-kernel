#define __DEBUG__   1

#include <drivers/device.h>
#include <memory/memory-util.h>
#include <memory/linked-list.h>
#include <adamantine/tty.h>
#include <string.h>
#include <debug.h>

struct device *block_devices[MAX_DEVICES];
struct device *other_devices[MAX_DEVICES];

void
device_initialize(void)
{
    memset(block_devices, 0, sizeof(block_devices));
    memset(other_devices, 0, sizeof(other_devices));
    
    show_debug_info("Device subsystem is initialized.");
}

void
device_seek(struct device *_device, int _pos)
{
    _device->pos = _pos;
}

void
device_register(struct device *_device)
{
    if (_device->type == DEV_TYPE_BLOCK)
    {
        for (int i = 0; i < MAX_DEVICES; i++)
        {
            if (block_devices[i] == NULL)
            {
                block_devices[i] = _device;
                return;
            }
        }
    }
    else
    {
        for (int i = 0; i < MAX_DEVICES; i++)
        {
            if (other_devices[i] == NULL)
            {
                other_devices[i] = _device;
                return;
            }
        }
    }
}
