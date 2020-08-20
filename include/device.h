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

#if defined(__cplusplus)
extern "C" {
#endif

struct AOS_FileSystem;

typedef struct AOS_Device 
{
    UDWORD              DeviceID;
    BYTE                DeviceStatus;
    BYTE                (*Read)(BYTE *Buffer, UDWORD Offset, UDWORD Length, VOID *Device);
    BYTE                (*Write)(BYTE *Buffer, UDWORD Offset, UDWORD Length, VOID *Device);
    STRING              DeviceName;
    STRUCT              AOS_FileSystem *FileSystem;
} Device_t;

enum DeviceType {
    DEVICE_UNKNOWN,
    DEVICE_CHAR,
    DEVICE_BLOCK,
};

EXTERN VOID (AOS_DeviceInit(UDWORD, STRING));
EXTERN VOID (AOS_DeviceAdd(STRUCT AOS_Device *));
EXTERN VOID (AOS_DeviceFree(VOID));
EXTERN STRUCT AOS_Device AOS_DeviceGet(UDWORD);

#if defined(__cplusplus)
}
#endif
#endif
