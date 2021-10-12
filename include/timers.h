#ifndef _TIMERS_H
#define _TIMERS_H

#include <sys/types.h>

struct timer;
typedef void (*timer_func_t)(time_t *t_ptr);

typedef union
{
    int ta_int;
    long ta_long;
    void *ta_ptr;
} tmr_arg_t;

typedef struct time
{
    struct timer *next;
    clock_t expiration_time;
    timer_func_t timer_func;
    tmr_arg_t tmr_arg;
} timer_t;

#endif
