#include <string.h>

/* Split a string by delimeter */
inline size_t 
strsplit(char *_str, char _delim) 
{
    size_t n = 0;
    uint32_t i = 0;
    while (_str[i]) 
    {
        if (_str[i] == _delim) 
        {
            _str[i] = 0;
            n++;
        }
        i++;
    }
    n++;
    return (n);
}
