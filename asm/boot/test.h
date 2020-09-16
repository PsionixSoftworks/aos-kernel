/*
 *  File: test.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF ITS AUTHOR(S).
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef TEST
#define TEST

#ifdef __ASSEMBLER__
#define TESTER      10
#else
#include <adamantine/aos-types.h>

extern uint32_t test_func(void);
#endif

#endif
