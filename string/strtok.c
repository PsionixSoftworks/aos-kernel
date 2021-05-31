#include <string.h>

/* Split a string into tokens */
char *
strtok(char *string, const char *delim)
{
    static char *p = 0;
    if (string)
        p = string;
    else if (!p)
        return (0);
    string = p + strspn(p, delim);
    p = string + strcspn(string, delim);
    if (p == string)
        return (p = 0);
    p = *p ? *p = 0, p + 1 : 0;
    return (string);
}
