#define KERNEL32	1

#include "../include/device.h"
#include "../include/driver.h"
#include "../include/mem_util.h"
#include "../include/mutex.h"
#include "../include/io.h"
#include "../include/terminal.h"
#include "../include/aos-defs.h"

MODULE("device", "0.01a");

typedef struct aos_device device_t;
static device_t *device = 0;

void 
aos_device_init(uint32_t device_id, string device_name) 
{
    size_t size = 64 * sizeof(device_t);

    device = (device_t *)malloc(size);
    memset(device, 0, size);

    device->device_id       = device_id;
    device->device_name     = device_name;
    device->device_status   = 1;

    INFO("Initialization of device complete: ");
    terminal_print(device_name);
    terminal_println();
    return;
}

void 
aos_device_free(void) 
{
    free(device);
}
