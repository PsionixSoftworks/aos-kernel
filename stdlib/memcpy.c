#include <stdlib.h>

/* Copy the contents in memory with aset size */
void *
memcpy(void *restrict _dstptr, const void *restrict _srcptr, size_t _size)
{
	unsigned char *dst = (unsigned char *)_dstptr;
	const unsigned char *src = (const unsigned char *)_srcptr;
	for (size_t i = 0; i < _size; i++)
		dst[i] = src[i];
	return (_dstptr);
}
