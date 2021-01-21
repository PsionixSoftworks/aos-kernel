#include <kernel/memory/kheap.h>
#include <kernel/system/terminal.h>
#include <stdbool.h>

void
k_heapbm_init(kheapbm *heap)
{
    heap->fblock = 0;
}

int
k_heapbm_add_block(kheapbm *heap, uintptr_t addr, uint32_t size, uint32_t bsize)
{
    kheapblockbm    *b;
    uint32_t        bcnt;
    uint32_t        x;
    uint8_t         *bm;

    b = (kheapblockbm *)addr;
    b->size = size - sizeof(kheapblockbm);
    b->bsize = bsize;

    b->next = heap->fblock;
    heap->fblock = b;

    bcnt = b->size / b->size;
    bm = (uint8_t *)&b[1];

    for (x = 0; x < bcnt; ++x)
    {
        bm[x] = 0;
    }

    b->lfb = bcnt - 1;
    b->used = bcnt;

    return (1);
}

static uint8_t
k_heapbm_get_nid(uint8_t a, uint8_t b)
{
    uint8_t c;
    for (c = a + 1; c == b || c == 0; ++c);

    return (c);
}

void *
k_heapbm_alloc(kheapbm *heap, uint32_t size)
{
    kheapblockbm *b;
    uint8_t *bm;
    uint32_t bcnt;
    uint32_t x, y, z;
    uint32_t bneed;
    uint8_t nid;

    for (b = heap->fblock; b; b = b->next)
    {
        if (b->size - (b->used * b->size) >= size)
        {
            
        }
    }
}