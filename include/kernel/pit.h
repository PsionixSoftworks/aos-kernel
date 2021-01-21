/*
 *  File: pit.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _AOS_PIT_H
#define _AOS_PIT_H

#include <stdint.h>

#define PIT_BASE_FREQ       0x1234DC

#define PIT_CHANNEL_0       0x40
#define PIT_CHANNEL_1       0x41
#define PIT_CHANNEL_2       0x42
#define PIT_CMD_PORT        0x43

void pit_init(uint32_t fq);
void pit_install(int hz);
void pit_wait(int t);

#endif	// !_AOS_PIT_H
