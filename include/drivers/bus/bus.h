/*
 *  File: bus.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _AOS_BUS_
#define _AOS_BUS_

#include "../../device.h"
#include "../../aos-defs.h"

#define BUS_ENABLE                          0x1C0000007FUL

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct AOS_BusDriver
{
    UDWORD              BaseAddr;
} PACKED BusDriver_t, *PBusDriver_t;

EXTERN  SET_VOID(EnableBusDriver(VOID));

#if defined(__cplusplus)
}
#endif
#endif
