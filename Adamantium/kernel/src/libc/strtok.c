#include <string.h>

/* Split a string into tokens */
char *
strtok(char *_string, const char *_delim)
{
    static char *p = 0;
    if (_string)
        p = _string;
    else if (!p)
        return (0);
    _string = p + strspn(p, _delim);
    p = _string + strcspn(_string, _delim);
    if (p == _string)
        return (p = 0);
    p = *p ? *p = 0, p + 1 : 0;
    return (_string);
}
