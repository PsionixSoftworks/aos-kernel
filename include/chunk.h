#ifndef AOS_CHUNK_H
#define AOS_CHUNK_H

#include "aos-defs.h"
#include "types.h"

typedef struct aos_chunk chunk_t;

EXTERN uint32_t chunk_create(size_t size);

#endif
