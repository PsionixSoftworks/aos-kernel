#ifndef STRING
#define STRING

#include "types.h"

typedef char *string;

// Declare string functions:
extern char *itoa( int value, char * str, int base );		// Converts integer to string.
extern int strcmp(string  str1, string str2);
extern string strcpy(string src, string dest);
extern string strcat(string src, string dest);
extern size_t strlen(const string s);
extern size_t str_backspace(string str, char c);

#endif	// !STRING