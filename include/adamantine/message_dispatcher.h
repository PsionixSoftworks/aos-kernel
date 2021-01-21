#ifndef _AOS_MESSAGE_DISPATCHER_H
#define _AOS_MESSAGE_DISPATCHER_H

#include <stdint.h>

typedef void(*msg_t)(uint8_t, char *);

static inline void
MESSAGE(msg_t cbfun, uint8_t type, char *msg)
{
    cbfun(type, msg);
}

#endif  // !_AOS_MESSAGE_DISPATCHER_H
