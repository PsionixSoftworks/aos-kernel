#include <memory/linked-list.h>

struct node
{
    int data;
    int key;
    struct node *next;
};

static struct node *head       = NULL;
static struct node *current    = NULL;
static int index = 0;

static inline void
print_list(void)
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
insert_at(int key, int data)
{
    struct node *link = (struct node *)kmalloc(sizeof(struct node));

    link->key = key;
    link->data = data;

    link->next = head;

    head = link;
}

struct node *
delete_first(void)
{
    struct node *tmp = head;
    head = head->next;
    return tmp;
}

bool
is_empty(void)
{
    return head == NULL;
}

int
length(void)
{
    int len = 0;
    struct node *current;

    for (current = head; current != NULL; current = current->next)
    {
        len++;
    }
    return len;
}

struct node *
find(int key)
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

struct node *
delete(int key)
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

void
sort(void)
{
    int i, j, k, tmpkey, tmpdata;
    struct node *current;
    struct node *next;

    int size = length();
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

void
reverse(struct node **head_ref)
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

void
linked_list_add(int data)
{
    insert_at(index++, data);
}

void
linked_list_set(int pos, int data)
{
    insert_at(pos, data);
}

struct node *
linked_list_remove(void)
{
    delete_first();
}

struct node *
linked_list_remove_at(int pos)
{
    delete(pos);
}

bool
linked_list_empty(void)
{
    bool result;
    result = is_empty();
    return result;
}

size_t
linked_list_size(void)
{
    size_t result;
    result = length();
    return result;
}

int
linked_list_find(int pos)
{
    struct node *result;
    result = find(pos);
    return result->data;
}

void
linked_list_sort(void)
{
    sort();
}

void
linked_list_reverse(struct node **head_ref)
{
    reverse(head_ref);
}

void
linked_list_to_string(void)
{
    print_list();
}

struct node *
linked_list_get_head(void)
{
    return &head;
}