#include <drivers/device.h>
#include <memory/memory-util.h>
#include <adamantine/tty.h>
#include <string.h>

static volatile uint32_t index = 10;
static volatile uint32_t offset = 0;

uint32_t
device_init(device_t *dev, char *name)
{
     

    return 0;
}