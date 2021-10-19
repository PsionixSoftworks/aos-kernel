#include <string.h>

/* Make all characters in a string lowercase */
inline void 
to_lower(char *_str)
{
    while(*_str != '\0')
    {
        if(*_str >= 65 && *_str <= 90)
        {
            *_str = *_str + 32;
        }
        _str++;
    }
}
