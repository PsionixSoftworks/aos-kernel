#ifndef _AOS_MESSAGE_DISPATCHER_H
#define _AOS_MESSAGE_DISPATCHER_H

#include <stdint.h>
#include <adamantine/aos-defs.h>

#define dispatch_inf(msg)       __dispatcher_info(msg);
#define dispatch_wrn(msg)       __dispatcher_warn(msg);
#define dispatch_err(msg)       __dispatcher_err(msg);

typedef void(*msg_t)(uint8_t, char *);

enum dispatcher_type
{
    INFO,
    WARNING,
    ERROR,
};

static inline void
MESSAGE(msg_t cbfun, uint8_t type, char *msg)
{
    cbfun(type, msg);
}

EXTERN void __dispatcher_info(char *msg);
EXTERN void __dispatcher_warn(char *msg);
EXTERN void __dispatcher_err(char *msg);

#endif  // !_AOS_MESSAGE_DISPATCHER_H
