#include <memory/ordered-array.h>
#include <string.h>
#include <assert.h>

extern uint32_t kmalloc(uint32_t _sz);
extern void kfree(void *p);

int8_t
standard_lessthan_predicate(type_t a, type_t b)
{
   return (a < b) ? 1 : 0;
}

ordered_array_t
create_ordered_array(uint32_t _max_size, lessthan_predicate_t _less_than)
{
   ordered_array_t to_ret;
   to_ret.array = (void*)kmalloc(_max_size * sizeof(type_t));
   memset(to_ret.array, 0, _max_size * sizeof(type_t));
   to_ret.size = 0;
   to_ret.max_size = _max_size;
   to_ret.less_than = _less_than;
   return to_ret;
}

ordered_array_t
place_ordered_array(void *_addr, uint32_t _max_size, lessthan_predicate_t _less_than)
{
   ordered_array_t to_ret;
   to_ret.array = (type_t*)_addr;
   memset(to_ret.array, 0, _max_size*sizeof(type_t));
   to_ret.size = 0;
   to_ret.max_size = _max_size;
   to_ret.less_than = _less_than;
   return to_ret;
}

void
destroy_ordered_array(ordered_array_t *_array)
{
   kfree(_array->array);
}

void insert_ordered_array(type_t _item, ordered_array_t *_array)
{
   //ASSERT(_array->less_than);
   int32_t iterator = 0;
   while (iterator < _array->size && _array->less_than(_array->array[iterator], _item))
       iterator++;
   if (iterator == _array->size) // just add at the end of the array.
      _array->array[_array->size++] = _item;
   else
   {
      type_t tmp = _array->array[iterator];
      _array->array[iterator] = _item;
      while (iterator < _array->size)
      {
         iterator++;
         type_t tmp2 = _array->array[iterator];
         _array->array[iterator] = tmp;
         tmp = tmp2;
      }
      _array->size++;
   }
}

type_t
lookup_ordered_array(int32_t i, ordered_array_t *_array)
{
   //ASSERT(i < _array->size);
   return _array->array[i];
}

void
remove_ordered_array(int32_t i, ordered_array_t *_array)
{
   while (i < _array->size)
   {
       _array->array[i] = _array->array[i+1];
       i++;
   }
   _array->size--;
}
