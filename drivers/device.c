/*
 *  File: device.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/aos-defs.h"
#include "../include/device.h"
#include "../include/driver.h"
#include "../include/mem-util.h"
#include "../include/mutex.h"
#include "../include/io.h"
#include "../include/terminal.h"

MODULE("device", "0.01a");

typedef struct aos_device device_t;
static device_t *device = 0;

VOID 
AOS_DeviceInit(UDWORD device_id, STRING device_name)
{
    SIZE Size = 64 * sizeof(device_t);

    device = (device_t *)Malloc(Size);
    MemSet(device, 0, Size);

    device->device_id       = device_id;
    device->device_name     = device_name;
    device->device_status   = 1;

    INFO("Initialization of device complete: %s.\n", device_name);
    return;
}

VOID
AOS_deviceFree(VOID) 
{
    Free(device);
}
