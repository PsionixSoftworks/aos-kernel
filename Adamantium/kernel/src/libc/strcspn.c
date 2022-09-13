#include <string.h>

/* Get span until character in string */
size_t
strcspn(const char *_s1, const char *_s2)
{
    size_t ret = 0;
    while (*_s1)
    {
        if (strchr(_s2, *_s1))
            return (ret);
        else
            _s1++, ret++;
    }
    return (ret);
}
