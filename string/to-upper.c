#include <string.h>

/* Make all characters in a string uppercase */
inline void
to_upper(char *_str)
{
    while (*_str != '\0')
    {
        if (*_str >= 0x61 && *_str <= 0x7A)
        {
            *_str = *_str - 32;
        }
        _str++;
    }
}
