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

// Declare string functions:
EXTERN char *itoa(udword value, char * str, udword base);		// Converts integer to string.
EXTERN udword strcmp(string  str1, string str2);
EXTERN string strcpy(string src, string dest);
EXTERN string strcat(string dest, string src);
EXTERN void to_lower(string str);
EXTERN void to_upper(string str);
EXTERN size_t strlen(const string s);
EXTERN size_t str_backspace(string str, char c);
EXTERN size_t strsplit(string str, char delim);

#endif	// !_STRING_