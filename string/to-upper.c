#include <string.h>

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
