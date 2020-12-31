/*
 *  File: char *c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include <adamantine/adamantine.h>

char *
itoa(int value, char * str, int base) 
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
	
    // Terminating the char *
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

int
strcmp(const char *str1, const char *str2) 
{
	register const uint8_t *s1 = (const uint8_t *)str1;
    register const uint8_t *s2 = (const uint8_t *)str2;
    uint8_t c1;
    uint8_t c2;

    do
    {
        c1 = (uint8_t) *s1++;
        c2 = (uint8_t) *s2++;
        if (c1 == '\0')
        {
            return (c1 - c2);
        }
    } while (c1 == c2);
    
    return (c1 - c2);
}

char *
strcpy(char *dest, char *src) 
{
	return (memcpy(dest, src, strlen(src) + 1));
}

char *
strcat(char *dest, const char *src) 
{
	strcpy(dest + strlen(dest), src);
    return (dest);
}

size_t
strlen(const char *s) 
{
	size_t i = 0;
	while (s[i] != 0) i++;
	return (i);
}

inline size_t
str_backspace(char *str, char c) 
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

inline size_t 
strsplit(char *str, char delim) 
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
to_lower(char *str)
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
to_upper(char *str)
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
