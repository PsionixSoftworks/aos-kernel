#define KERNEL32    1

#include "bus.h"
#include "../../aos-defs.h"

pBus_Driver_t bus;

void HOT
enable_bus_driver(void)
{
    bus->base_addr = BUS_ENABLE;

}
