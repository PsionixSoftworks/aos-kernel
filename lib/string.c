/*
 *  File: string.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/string.h"

inline char *
itoa( udword value, char * str, udword base ) 
{
    char *rc;
    char *ptr;
    char *low;
    // Check for supported base.
    if ((base < 2) || (base > 36)) 
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    
	// Set '-' for negative decimals.
    if ((value < 0) && (base == 10)) 
    {
        *ptr++ = '-';
    }
	
    // Remember where the numbers start.
    low = ptr;
	
    // The actual conversion.
    do 
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
	
    // Terminating the string.
    *ptr-- = '\0';
	
    // Invert the numbers.
    while (low < ptr) 
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return (rc);
}

inline udword
strcmp(string str1, string str2) 
{
	udword i = 0;
	udword failed = 0;
	while ((str1[i] != '\0') && (str2[i] != '\0')) 
    {
		if (str1[i] != str2[i]) 
        {
			failed = 1;
			break;
		}
		i++;
	}
	if (((str1[i] == '\0') && (str2[i] != '\0')) || ((str1[i] != '\0') && (str2[i] == '\0'))) 
    {
		failed = 1;
	}
	return (failed);
}

inline string
strcpy(string src, string dest) 
{
	unsigned i;
    for (i = 0; src[i] != '\0'; ++i)
        dest[i] = src[i];
    dest[i] = '\0';

    return (dest);
}

inline string
strcat(string dest, string src) 
{
	size_t i, j;
    for (i = 0; dest[i] != '\0'; i++);
    for (j = 0; src[j] != '\0'; j++)
        dest[i + j] = src[j];
    dest[i + j] = '\0';
    return dest;
}

inline size_t
strlen(const string s) 
{
	size_t i = 0;
	while (s[i] != 0) i++;
	return (i);
}

inline size_t
str_backspace(string str, char c) 
{
    size_t i = strlen(str);
    i--;
    while (1) 
    {
        i--;
        if (str[i] == c) 
        {
            str[i + 1] = 0;
            return (1);
        }
    }
    return (0);
}

inline size_t strsplit(string str, char delim) 
{
    size_t n = 0;
    uint32_t i = 0;
    while (str[i]) 
    {
        if (str[i] == delim) 
        {
            str[i] = 0;
            n++;
        }
        i++;
    }
    n++;
    return (n);
}

inline void 
to_lower(string str)
{
    while(*str != '\0')
    {
        if(*str >= 65 && *str <= 90)
        {
            *str = *str + 32;
        }
        str++;
    }
}

inline void
to_upper(string str)
{
    while (*str != '\0')
    {
        if (*str >= 0x61 && *str <= 0x7A)
        {
            *str = *str - 32;
        }
        str++;
    }
}
