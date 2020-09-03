/*
 *  File: device.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _DEVICE_
#define _DEVICE_

#include "aos-defs.h"
#include "types.h"
#include "string.h"
#include "driver.h"

struct AOS_FileSystem;

typedef struct 
aos_device 
{
    udword              device_id;
    byte                device_status;
    byte                (*Read)(BYTE *Buffer, UDWORD Offset, UDWORD Length, VOID *Device);
    byte                (*Write)(BYTE *Buffer, UDWORD Offset, UDWORD Length, VOID *Device);
    string              device_name;
    struct              AOS_FileSystem *FileSystem;
} device_t;

enum 
DeviceType {
    DEVICE_UNKNOWN,
    DEVICE_CHAR,
    DEVICE_BLOCK,
};

EXTERN VOID AOS_DeviceInit(UDWORD, STRING);
EXTERN VOID AOS_DeviceAdd(struct aos_device *);
EXTERN VOID AOS_DeviceFree(VOID);
EXTERN struct aos_device AOS_DeviceGet(UDWORD);

#endif
