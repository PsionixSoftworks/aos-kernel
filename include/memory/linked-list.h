#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <drivers/tty.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory/memory-util.h>

/* Make it visible from the source file. */
struct node;

extern void linked_list_add(int data);
extern void linked_list_set(int pos, int data);
extern struct node *linked_list_remove(void);
extern struct node *linked_list_remove_at(int pos);
extern bool linked_list_empty(void);
extern size_t linked_list_size(void);
extern int linked_list_find(int pos);
extern void linked_list_sort(void);
extern void linked_list_reverse(struct node **head_ref);
extern void linked_list_to_string(void);
extern struct node *linked_list_get_head(void);

#endif
