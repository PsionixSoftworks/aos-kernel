#include <stdlib.h>
#include <stddef.h>
#include <kernel/memory/memory-util.h>

/* Locate a character within a block of memory */
void *
memchr(register const void *str, int c, size_t n)
{
    const uint8_t *source = (const uint8_t *)str;

    while (n-- > 0)
    {
        if (*source == c)
        {
            return (void *)source;
        }
        source++;
    }
    return (NULL);
}
