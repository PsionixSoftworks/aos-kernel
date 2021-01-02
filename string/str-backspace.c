#include <string.h>

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
