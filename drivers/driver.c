#include <adamantine/adamantine.h>
#include <drivers/driver.h>
#include <memory/memory-util.h>
#include <drivers/device.h>
#include <system/portio.h>
#include <adamantine/tty.h>

#ifndef _SYS_TYPES_H
#include <sys/types.h>
#endif

void *
device_driver_setup(int (*config_func)(void), int flags)
{
    config_func();
}
