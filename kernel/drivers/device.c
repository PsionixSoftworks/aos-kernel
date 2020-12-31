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

#include <adamantine/adamantine.h>

typedef struct aos_device device_t;
static device_t *device = 0;

void 
aos_device_init(uint32_t device_id, char *device_name)
{
    size_t size = 64 * sizeof(device_t);

    device = (device_t *)malloc(size);
    memset(device, 0, size);

    device->device_id       = device_id;
    device->device_name     = device_name;
    device->device_status   = 1;

    //_INFO("Initialization of device complete: %s.\n", device_name);
    return;
}

void
AOS_deviceFree(void)
{
    free(device);
}
