#include <adamantine/adamantine.h>
#include <drivers/driver.h>
#include <memory/memory-util.h>

#ifndef _SYS_TYPES
#include <sys/types.h>
#endif

#define MAX_DEVICES     32

void
driver_init(driver_t *d_ptr, char *name)
{
    /* If this is an invalid device pointer, exit this code block */
    if (!d_ptr)
        return;
    
    /* Assign this a device */
    device_t *curr_device;
    curr_device = (device_t *)kmalloc(sizeof(device_t) * MAX_DEVICES);
    curr_device->device_base = 0;
    curr_device->device_size = sizeof(device_t);

    /* Assign the driver attributes */
    d_ptr->name[MAX_NAME_LENGTH] = name;
    //d_ptr->driver_id = driver_get_id();
}

unsigned long
driver_get_id(void)
{
    static int id = 1000L;
    return id++;
}
