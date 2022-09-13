#include <string.h>

/* Locate a character within a string */
char *
strchr(const char *s, int c)
{
    while (*s != (char)c)
        if (!*s++)
            return (0);
    return (char *)s;
}
