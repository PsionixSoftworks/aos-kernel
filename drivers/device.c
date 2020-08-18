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

MODULE("Device", "0.01a");

typedef struct AOS_Device Device_t;
static Device_t *Device = 0;

VOID 
AOS_DeviceInit(UDWORD DeviceID, STRING DeviceName) 
{
    SIZE Size = 64 * sizeof(Device_t);

    Device = (Device_t *)Malloc(Size);
    MemSet(Device, 0, Size);

    Device->DeviceID        = DeviceID;
    Device->DeviceName      = DeviceName;
    Device->DeviceStatus    = 1;

    INFO("Initialization of device complete: ");
    TerminalPrint(DeviceName);
    TerminalPrintln();
    return;
}

VOID
AOS_DeviceFree(VOID) 
{
    Free(Device);
}
