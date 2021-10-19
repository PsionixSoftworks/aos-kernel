/**
 * NOTE: THIS SOURCE FILE IS TAKEN FROM http://www.jamesmolloy.co.uk/tutorial_html/7.-The%20Heap.html
 * It is a temporary heap allocator for use within the Virtual File System and other memory related
 * functions.
 * 
 * Almost everything in here will be replaced once understood!
 *
 **/

#include <memory/memory-util.h>
#include <memory/ordered-array.h>
#include <memory/paging.h>
#include <stdint.h>
#include <assert.h>

// End is defined in the linker script.
extern uint32_t end;
uint32_t placement_address = (uint32_t)&end;
extern page_directory_t *kernel_directory;
heap_t *kheap=0;

extern void free_frame(page_t *_page);

uint32_t
kmalloc_int(uint32_t _sz, int _align, uint32_t *_phys)
{
	if (kheap != 0)
	{
		void *addr = alloc(_sz, (uint8_t)_align, kheap);
		if (_phys != 0)
		{
			page_t *page = get_page((uint32_t)addr, 0, kernel_directory);
			*_phys = page->frame * 0x1000 + ((uint32_t)addr & 0xFF);
		}
		return (uint32_t)addr;
	}
	else
	{
		if (_align == 1 && (placement_address & 0x00000FFF))
		{
			// Align the placement address:
			placement_address &= 0xFFFFF000;
			placement_address += 0x1000;
		}
		if (_phys)
		{
			*_phys = placement_address;
		}
		uint32_t tmp = placement_address;
		placement_address += _sz;
		return tmp;
	}
}

void
kfree(void *p)
{
	free(p, kheap);
}

uint32_t
kmalloc_a(uint32_t _sz)
{
	return kmalloc_int(_sz, 1, 0);
}

uint32_t
kmalloc_p(uint32_t _sz, uint32_t *_phys)
{
	return kmalloc_int(_sz, 0, _phys);
}

uint32_t
kmalloc_ap(uint32_t _sz, uint32_t *_phys)
{
	return kmalloc_int(_sz, 1, _phys);
}

uint32_t kmalloc(uint32_t _sz)
{
	return kmalloc_int(_sz, 0, 0);
}

static void
expand(uint32_t _new_size, heap_t *_heap)
{
	// Sanity check:
	ASSERT(_new_size > _heap->end_address - _heap->start_address);

	// Get the nearest following page boundary:
	if ((_new_size & 0xFFFFF000) != 0)
	{
		_new_size &= 0xFFFFF000;
		_new_size += 0x1000;
	}

	// Make sure we are not overreaching ourselves:
	ASSERT(_heap->start_address + _new_size <= _heap->max_address);

	// This should always be on a page boundary:
	uint32_t old_size = _heap->end_address - _heap->start_address;
	uint32_t i = old_size;
	while (i < _new_size)
	{
		alloc_frame(get_page(_heap->start_address + i, 1, kernel_directory),
					(_heap->supervisor) ? 1 : 0, (_heap->readonly) ? 0 : 1);
		i += 0x1000 /* page size */;
	}
	_heap->end_address = _heap->start_address + _new_size;
}

static uint32_t
contract(uint32_t _new_size, heap_t *_heap)
{
	ASSERT(_new_size < _heap->end_address - _heap->start_address);

	// Get the nearest following page boundary:
	if (_new_size & 0x1000)
	{
		_new_size &= 0x1000;
		_new_size += 0x1000;
	}

	// Don't contract too far:
	if (_new_size < HEAP_MIN_SIZE)
		_new_size = HEAP_MIN_SIZE;
	uint32_t old_size = _heap->end_address - _heap->start_address;
	uint32_t i = old_size - 0x1000;
	while (_new_size < i)
	{
		free_frame(get_page(_heap->start_address + i, 0, kernel_directory));
		i -= 0x1000;
	}
	_heap->end_address = _heap->start_address + _new_size;
	return _new_size;
}

static int32_t
find_smallest_hole(uint32_t _size, uint8_t _page_align, heap_t *_heap)
{
	// Find the smallest hole that will fit:
	int32_t iterator = 0;
	while (iterator < _heap->index.size)
	{
		header_t *header = (header_t *)lookup_ordered_array(iterator, &_heap->index);

		// If the user has requested the memory be page-aligned:
		if (_page_align > 0)
		{
			// Page-align the starting point of this header:
			uint32_t location = (uint32_t)header;
			int32_t offset = 0;
			if (((location + sizeof(header_t)) & 0xFFFFF000) != 0)
				offset = 0x1000 /* page size */ - (location+sizeof(header_t))%0x1000;
			int32_t hole_size = (int32_t)header->size - offset;
			// Can we fit now?
			if (hole_size >= (int32_t)_size)
				break;
		}
		else if (header->size >= _size)
			break;
		iterator++;
	}

	// Why did the loop exit?
	if (iterator == _heap->index.size)
		return -1; // We got to the end and didn't find anything.
	else
		return iterator;
}

static int8_t
header_t_less_than(void *a, void *b)
{
	return (((header_t *)a)->size < ((header_t *)b)->size) ? 1 : 0;
}

heap_t *
create_heap(uint32_t _start, uint32_t _end_addr, uint32_t _max, uint8_t _supervisor, uint8_t _readonly)
{
	heap_t *heap = (heap_t *)kmalloc(sizeof(heap_t));

	// All of our assumptions are nade on start_address and end_address being page-aligned:
	ASSERT(_start%0x1000 == 0);
	ASSERT(_end_addr%0x1000 == 0);

	// Initialize the index:
	heap->index = place_ordered_array((void *)_start, HEAP_INDEX_SIZE, &header_t_less_than);

	// Shift the start address forward to resemble where we can start putting data:
	_start += sizeof(type_t)*HEAP_INDEX_SIZE;

	// Make sure the start address is page-aligned:
	if ((_start & 0xFFFFF000) != 0)
	{
		_start &= 0xFFFFF000;
		_start += 0x1000;
	}

	// Write the start, end and max addresses into the heap structure:
	heap->start_address = _start;
	heap->end_address = _end_addr;
	heap->max_address = _max;
	heap->supervisor = _supervisor;
	heap->readonly = _readonly;

	//  We start off with one large hole in the index:
	header_t *hole = (header_t *)_start;
	hole->size = _end_addr - _start;
	hole->magic = HEAP_MAGIC;
	hole->is_hole = 1;
	insert_ordered_array((void *)hole, &heap->index);

	return heap;
}

void *
alloc(uint32_t _size, uint8_t _page_align, heap_t *_heap)
{
	// Make sure we take the size of the header/footer into account:
	uint32_t new_size = _size + sizeof(header_t) + sizeof(footer_t);

	// Find the smallest hole that will fit:
	int32_t iterator = find_smallest_hole(new_size, _page_align, _heap);

	if (iterator == -1)	// If we didn't find a suitable hole.
	{
		// Save some previous data:
		uint32_t old_length = _heap->end_address - _heap->start_address;
		uint32_t old_end_address = _heap->end_address;

		// We need to allocate some more space:
		expand(old_length + new_size, _heap);
		uint32_t new_length = _heap->end_address - _heap->start_address;

		// Find the endmost header. (Not in size, but in location):
		iterator = 0;

		// Vars to hold the index of, and value of, the endmost header found so far:
		int32_t idx = -1;	// << Bug waiting to happen! unsigned integers can't be negative!
		uint32_t value = 0x0;
		while (iterator < _heap->index.size)
		{
			uint32_t tmp = (uint32_t)lookup_ordered_array(iterator, &_heap->index);
			if (tmp > value)
			{
				value = tmp;
				idx = iterator;
			}
			iterator++;
		}

		// If we didn't find ANY headers, we need to add one:
		if (idx == -1)
		{
			header_t *header = (header_t *)old_end_address;
			header->magic = HEAP_MAGIC;
			header->size = new_length - old_length;
			header->is_hole = 1;
			footer_t *footer = (footer_t *)(old_end_address + header->size - sizeof(footer_t));
			footer->magic = HEAP_MAGIC;
			footer->header = header;
			insert_ordered_array((void *)header, &_heap->index);
		}
		else
		{
			// The last header needs adjusting:
			header_t *header = lookup_ordered_array(idx, &_heap->index);
			header->size += new_length - old_length;

			// Rewrite the footer:
			footer_t *footer = (footer_t *)((uint32_t)header + header->size - sizeof(footer_t));
			footer->header = header;
			footer->magic = HEAP_MAGIC;
		}

		// We now have enough space. Recurse, and call the function again:
		return alloc(_size, _page_align, _heap);
	}

	header_t *orig_hole_header = (header_t *)lookup_ordered_array(iterator, &_heap->index);
	uint32_t orig_hole_pos = (uint32_t)orig_hole_header;
	uint32_t orig_hole_size = orig_hole_header->size;

	// Here we want to work out if we should split the hole we found into two parts.
	// Is the original hole size - requested hole size less than the overhead for adding a new hole?:
	if (orig_hole_size - new_size < sizeof(header_t) + sizeof(footer_t))
	{
		// Then just increase the requested size to the size of the hole we found:
		_size += orig_hole_size - new_size;
		new_size += orig_hole_size;
	}

	if (_page_align && orig_hole_pos & 0xFFFFF000)
	{
		uint32_t new_location 	= orig_hole_pos + 0x1000 /* page size */ - (orig_hole_pos & 0xFFF) - sizeof(header_t);
		header_t *hole_header	= (header_t *)orig_hole_pos;
		hole_header->size		= 0x1000 /* page size */ - (orig_hole_pos & 0xFFF) - sizeof(header_t);
		hole_header->magic		= HEAP_MAGIC;
		hole_header->is_hole	= 1;
		footer_t *hole_footer	= (footer_t *)((uint32_t)new_location - sizeof(footer_t));
		hole_footer->magic		= HEAP_MAGIC;
		hole_footer->header		= hole_header;
		orig_hole_pos			= new_location;
		orig_hole_size 			= orig_hole_size - hole_header->size;
	}
	else
	{
		// Else we don't need this hole any more, delete it from the index:
		remove_ordered_array(iterator, &_heap->index);
	}

	// Overwrite the original header:
	header_t *block_header 		= (header_t *)orig_hole_pos;
	block_header->magic			= HEAP_MAGIC;
	block_header->is_hole		= 0;
	block_header->size			= new_size;

	// And the footer:
	footer_t *block_footer		= (footer_t *)(orig_hole_pos + sizeof(header_t) + _size);
	block_footer->magic			= HEAP_MAGIC;
	block_footer->header		= block_header;

	// We may need to write a new hole after the allocated block.
	// We do this only if the new hole would have positive size:
	if (orig_hole_size - new_size > 0)
	{
		header_t *hole_header 	= (header_t *)(orig_hole_pos + sizeof(header_t) + _size + sizeof(footer_t));
		hole_header->magic		= HEAP_MAGIC;
		hole_header->is_hole	= 1;
		hole_header->size		= orig_hole_size - new_size;
		footer_t *hole_footer	= (footer_t *)((uint32_t)hole_header + orig_hole_size - new_size - sizeof(footer_t));
		if ((uint32_t)hole_footer < _heap->end_address)
		{
			hole_footer->magic 	= HEAP_MAGIC;
			hole_footer->header	= hole_header;
		}
		
		// Put the new hole in the index:
		insert_ordered_array((void *)hole_header, &_heap->index);

		// And we're done!:
		return (void *)((uint32_t)block_header + sizeof(header_t));
	}

	return 0;
}

void
free(void *p, heap_t *_heap)
{
	// Exit gracefully for null pointers.
   	if (p == 0)
       return;
	
	// Get the header and footer associated with this pointer.
   	header_t *header = (header_t*) ( (uint32_t)p - sizeof(header_t) );
   	footer_t *footer = (footer_t*) ( (uint32_t)header + header->size - sizeof(footer_t) );

	// Sanity checks.
   	ASSERT(header->magic == HEAP_MAGIC);
   	ASSERT(footer->magic == HEAP_MAGIC);

	// Make us a hole:
	header->is_hole = 1;

	// Do we want to add this header into the 'free holes' index?:
	char do_add = 1;

	// Unify left
	// If the thing immediately to the left of us is a hole:
	footer_t *test_footer = (footer_t *)((uint32_t)header - sizeof(footer_t));
	if (test_footer->magic == HEAP_MAGIC &&
		test_footer->header->is_hole == 1)
	{
		uint32_t cache_size = header->size;
		header = test_footer->header;
		footer->header = header;
		header->size += cache_size;
		do_add = 0;
	}

	// Unify right
	// If the thing immediately to the right of us is a header:
	header_t *test_header = (header_t *)((uint32_t)footer + sizeof(footer_t));
	if (test_header->magic == HEAP_MAGIC &&
		test_header->is_hole)
	{
		header->size += test_header->size;	// Increase our size.
		test_footer = (footer_t *)((uint32_t)test_header + // Rewrite its footer to point to our header.
									test_header->size - sizeof(footer_t));
		footer = test_footer;

		// Find and remove this header from the index:
		int32_t iterator = 0;
		while ((iterator < _heap->index.size) &&
				(lookup_ordered_array(iterator, &_heap->index) != (void *)test_header))
			iterator++;

		// Make sure it actually found the item:
		ASSERT(iterator < _heap->index.size);

		// Remove it:
		remove_ordered_array(iterator, &_heap->index);
	}

	// If the footer location is the end of address, we can contract:
	if ((uint32_t)footer + sizeof(footer_t) == _heap->end_address)
	{
		uint32_t old_length = _heap->end_address - _heap->start_address;
		uint32_t new_length = contract((uint32_t)header - _heap->start_address, _heap);

		// Check how big we'll be after resizing:
		if (header->size - (old_length - new_length) > 0)
		{
			// We will still exist, so resize us:
			header->size -= old_length - new_length;
			footer = (footer_t *)((uint32_t)header + header->size - sizeof(footer_t));
			footer->magic = HEAP_MAGIC;
			footer->header = header;
		}
		else
		{
			// We will no longer exist :(. Remove us from the index:
			int32_t iterator = 0;
			while ((iterator < _heap->index.size) &&
					(lookup_ordered_array(iterator, &_heap->index) != (void *)test_header))
				iterator++;
			
			// If we didn't find ourselves, we have nothing to remove:
			if (iterator < _heap->index.size)
				remove_ordered_array(iterator, &_heap->index);
		}
	}

	if (do_add == 1)
		insert_ordered_array((void *)header, &_heap->index);
}
