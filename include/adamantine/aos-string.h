/*
 *  File: string.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _STRING_
#define _STRING_

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

#if defined(__cplusplus)
extern "C" {
#endif

// Declare string functions:
char *strcat(char *dest, const char *src);
char *strchr(const char *str, int c);
int strcmp(const char *str1, const char *str2);
char *strcpy(char *dest, char *src);
char *itoa(int value, char *str, int base);
void to_lower(string str);
void to_upper(string str);
size_t strlen(const string s);
size_t str_backspace(string str, char c);
size_t strsplit(string str, char delim);

#if defined(__cplusplus)
}
#endif

#endif	// !_STRING_