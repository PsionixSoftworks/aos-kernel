#include <string.h>

/* Insert a backspace */
inline size_t
str_backspace(char *_str, char c) 
{
    size_t i = strlen(_str);
    i--;
    while (1) 
    {
        i--;
        if (_str[i] == c) 
        {
            _str[i + 1] = 0;
            return (1);
        }
    }
    return (0);
}
