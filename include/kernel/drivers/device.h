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

#ifndef _DEVICE_H
#define _DEVICE_H

#include <stdint.h>

struct aos_file_system;

typedef struct 
aos_device 
{
    uint32_t                    device_id;
    uint8_t                     device_status;
    uint8_t                     (*read)(uint8_t *buffer, uint32_t Offset, uint32_t length, void *device);
    uint8_t                     (*Write)(uint8_t *buffer, uint32_t Offset, uint32_t length, void *device);
    char                        *device_name;
    struct                      aos_file_system *file_system;
} device_t;

enum 
DeviceType {
    DEVICE_UNKNOWN,
    DEVICE_CHAR,
    DEVICE_BLOCK,
};

#if defined(__cplusplus)
extern "C" {
#endif

void aos_device_init(uint32_t, char *);
void aos_device_add(struct aos_device *);
void aos_device_free(void);
struct aos_device aos_device_get(uint32_t);

#if defined(__cplusplus)
}
#endif

#endif  // !_DEVICE_H
