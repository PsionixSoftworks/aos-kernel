#include <memory/linked-list.h>

struct node
{
    int data;
    int key;
    struct node *next;
};

static struct node *head       = NULL;
static int index = 0;

static inline void __list_print(void);
static inline void __list_insert_at(int key, int data);
static inline struct node *__list_delete_first(void);
static inline bool __list_is_empty(void);
static inline int __list_length(void);
static inline struct node *__list_find(int key);
static inline struct node *__list_delete(int key);
static inline void __list_sort(void);
static inline void __list_reverse(struct node **head_ref);

void
linked_list_add(int data)
{
    __list_insert_at(index++, data);
}

void
linked_list_set(int pos, int data)
{
    __list_insert_at(pos, data);
}

struct node *
linked_list_remove(void)
{
    return __list_delete_first();
}

struct node *
linked_list_remove_at(int pos)
{
    return __list_delete(pos);
}

bool
linked_list_empty(void)
{
    bool result;
    result = __list_is_empty();
    return result;
}

size_t
linked_list_size(void)
{
    size_t result;
    result = __list_length();
    return result;
}

int
linked_list_find(int pos)
{
    struct node *result;
    result = __list_find(pos);
    return result->data;
}

void
linked_list_sort(void)
{
    __list_sort();
}

void
linked_list_reverse(struct node **head_ref)
{
    __list_reverse(head_ref);
}

void
linked_list_to_string(void)
{
    __list_print();
}

struct node *
linked_list_get_head(void)
{
    return head;
}

static inline void
__list_print(void)
{
    struct node *ptr = head;
    k_tty_printf("\n[ ");

    while (ptr != NULL)
    {
        k_tty_printf("(%d, %d) ", ptr->key, ptr->data);
        ptr = ptr->next;
    }

    k_tty_printf(" ]");
}

static inline void
__list_insert_at(int key, int data)
{
    struct node *link = (struct node *)kmalloc(sizeof(struct node));

    link->key = key;
    link->data = data;

    link->next = head;

    head = link;
}

static inline struct node *
__list_delete_first(void)
{
    struct node *tmp = head;
    head = head->next;
    return tmp;
}

static inline bool
__list_is_empty(void)
{
    return head == NULL;
}

static inline int
__list_length(void)
{
    int len = 0;
    struct node *current;

    for (current = head; current != NULL; current = current->next)
    {
        len++;
    }
    return len;
}

static inline struct node *
__list_find(int key)
{
    struct node *current = head;

    if (head == NULL)
        return NULL;
    
    while (current->key != key)
    {
        if (current->next == NULL)
            return NULL;
        else
            current = current->next;
    }
    return current;
}

static inline struct node *
__list_delete(int key)
{
    struct node *current = head;
    struct node *previous = NULL;

    if (head == NULL)
        return NULL;
    
    while (current->key != key)
    {
        if (current->next == NULL)
            return NULL;
        else
        {
            previous = current;
            current = current->next;
        }
    }

    if (current == head)
        head = head->next;
    else
        previous->next = current->next;
    return current;
}

static inline void
__list_sort(void)
{
    int i, j, k, tmpkey, tmpdata;
    struct node *current;
    struct node *next;

    int size = __list_length();
    k = size;

    for (i = 0; i < size - 1; i++, k--)
    {
        current = head;
        next = head->next;

        for (j = 1; j < k; j++)
        {
            if (current->data > next->data)
            {
                tmpdata = current->data;
                current->data = next->data;
                next->data = tmpdata;

                tmpkey = current->key;
                current->key = next->key;
                next->key = tmpkey;
            }

            current = current->next;
            next = next->next;
        }
    }
}

static inline void
__list_reverse(struct node **head_ref)
{
    struct node *prev = NULL;
    struct node *current = *head_ref;
    struct node *next;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head_ref = prev;
}
