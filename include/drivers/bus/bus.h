#ifndef _AOS_BUS_
#define _AOS_BUS_

#include "../../device.h"
#include "../../aos-defs.h"

#define BUS_ENABLE                          0x1C0000007FUL

typedef struct aos_bus_driver
{
    uint32_t base_addr;
} PACKED Bus_Driver_t, *pBus_Driver_t;

extern void enable_bus_driver(void);

#endif
