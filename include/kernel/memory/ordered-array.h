#ifndef _ADAMANTINE_ORDERED_ARRAY_H
#define _ADAMANTINE_ORDERED_ARRAY_H

#define KERNEL_ONLY

#include <stdint.h>

typedef void *type_t;

typedef int8_t(*lessthan_predicate_t)(type_t, type_t);
typedef struct
{
    type_t                  *array;
    uint32_t                size;
    uint32_t                max_size;
    lessthan_predicate_t    less_than;
} ordered_array_t;

extern int8_t standard_lessthan_predicate(type_t a, type_t b);
extern ordered_array_t create_ordered_array(uint32_t max_size, lessthan_predicate_t less_than);
extern ordered_array_t place_ordered_array(void *addr, uint32_t max_size, lessthan_predicate_t less_than);
extern void destroy_ordered_array(ordered_array_t *array);
extern void insert_ordered_array(type_t item, ordered_array_t *array);
extern type_t lookup_ordered_array(uint32_t i, ordered_array_t *array);
extern void remove_ordered_array(uint32_t i, ordered_array_t *array);

#endif  // !_ADAMANTINE_ORDERED_ARRAY_H
