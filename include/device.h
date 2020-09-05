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

struct aos_file_system;

typedef struct 
aos_device 
{
    udword              device_id;
    byte                device_status;
    byte                (*read)(byte *buffer, udword Offset, udword length, void *device);
    byte                (*Write)(byte *buffer, udword Offset, udword length, void *device);
    string              device_name;
    struct              aos_file_system *file_system;
} device_t;

enum 
DeviceType {
    DEVICE_UNKNOWN,
    DEVICE_CHAR,
    DEVICE_BLOCK,
};

EXTERN void aos_device_init(udword, string);
EXTERN void aos_device_add(struct aos_device *);
EXTERN void aos_device_free(void);
EXTERN struct aos_device aos_device_get(udword);

#endif
