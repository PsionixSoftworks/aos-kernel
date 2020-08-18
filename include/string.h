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

#ifndef STRING
#define STRING

#include "types.h"

#if defined(__cplusplus)
typedef const char *string;
#else
typedef char *string;
#endif

#if defined(__cplusplus)
extern "C" {
#endif

// Declare string functions:
extern char *itoa(int value, char * str, int base);		// Converts integer to string.
extern int strcmp(string  str1, string str2);
extern string strcpy(string src, string dest);
extern string strcat(string dest, string src);
extern void to_lower(string str);
extern void to_upper(string str);
extern size_t strlen(const string s);
extern size_t str_backspace(string str, char c);
extern size_t strsplit(string str, char delim);

#if defined(__cplusplus)
}
#endif

#endif	// !STRING