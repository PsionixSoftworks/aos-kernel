#ifndef _AOS_KHEAP_H
#define _AOS_KHEAP_H

#include <stdint.h>

typedef struct _kheapblockbm
{
    struct _kheapblockbm    *next;
    uint32_t                size;
    uint32_t                used;
    uint32_t                bsize;
    uint32_t                lfb;
} kheapblockbm;

typedef struct _kheapbm
{
    kheapblockbm            *fblock;
} kheapbm;

void k_heapbm_init(kheapbm *heap);
int k_heapbm_add_block(kheapbm *heap, uintptr_t addr, uint32_t size, uint32_t bsize);
void *k_heapbm_alloc(kheapbm *heap, uint32_t size);
void k_heapbm_free(kheapbm *heap, void *ptr);

#endif  // !_AOS_KHEAP_H
