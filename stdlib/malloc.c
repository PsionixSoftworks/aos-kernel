#include <stdlib.h>
#include <kernel/memory/mm.h>

void *
malloc(size_t size) 
{
	if (!size) return 0;
	uint8_t *mem = (uint8_t *)heap_begin;
	while ((uint32_t)mem < last_alloc) 
	{
		alloc_t *a = (alloc_t *)mem;
		if (!a->size)
			goto nalloc;
		if (a->status) 
		{
			mem += a->size;
			mem += sizeof(alloc_t);
			mem += 4;
			continue;
		}

		if (a->size >= size) 
		{
			a->status = 1;

			//terminal_printf("RE:Allocated %d bytes from %d to %d...\n", size, mem + sizeof(alloc_t), mem + sizeof(alloc_t) + size);

			memset(mem + sizeof(alloc_t), 0, size);
			memory_used += size + sizeof(alloc_t);
			return ((void *)(mem + sizeof(alloc_t)));
		}
		mem += a->size;
		mem += sizeof(alloc_t);
		mem += 4;
	}

	nalloc:;
	if (last_alloc + size + sizeof(alloc_t) >= heap_end) 
	{
		terminal_printf("Cannot allocate. Out of memory...\n");
	}
	alloc_t *alloc = (alloc_t *)last_alloc;
	alloc->status = 1;
	alloc->size = size;

	last_alloc += size;
	last_alloc += sizeof(alloc_t);
	last_alloc += 4;

	memory_used += size + 4 + sizeof(alloc_t);
	memset((void *)((uint32_t)alloc + sizeof(alloc_t)), 0, size);

	return ((void *)((uint32_t)alloc + sizeof(alloc_t)));
}
