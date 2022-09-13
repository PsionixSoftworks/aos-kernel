#include <stdlib.h>

/* Move memory from one location to another */
void *
memmove(void *_dest, const void *_src, size_t n)
{
    char *d = _dest;
    const char *s = _src;
    
    if (d < s)
    {
        while (n--)
        {
            *d++ = *s++;
        }
    }
    else
    {
        const char *lasts = s + (n - 1);
        char *lastd = d + (n - 1);
        while (n--)
        {
            *lastd-- = *lasts--;
        }
    }
    return (_dest);
}
