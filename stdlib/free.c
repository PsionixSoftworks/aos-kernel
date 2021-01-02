#include <stdlib.h>
#include <kernel/memory/mm.h>

void 
free(void *mem) 
{
	alloc_t *alloc = (mem - sizeof(alloc_t));
	memory_used -= alloc->size + sizeof(alloc_t);
	alloc->status = 0;
}
