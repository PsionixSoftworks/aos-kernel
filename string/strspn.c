#include <string.h>

/* Get the span of a character in a string */
size_t
strspn(const char *_s1, const char *_s2)
{
    size_t ret = 0;
    while (*_s1 && strchr(_s2, *_s1++))
        ret++;
    return (ret);
}
