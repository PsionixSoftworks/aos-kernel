#ifndef _ADAMANTINE_MESSAGE_DISPATCHER_H
#define _ADAMANTINE_MESSAGE_DISPATCHER_H

#include <stdint.h>
#include <adamantine/aos-defs.h>

#define KERNEL_ONLY                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

/* Define function macros to dispatch messages to the output */
#define dispatch_inf(msg)       __dispatcher_info(msg);
#define dispatch_wrn(msg)       __dispatcher_warn(msg);
#define dispatch_err(msg)       __dispatcher_err(msg);

typedef void(*msg_t)(uint8_t, char *);      // Type for message callback functions.

/* Dispatcher severity type */
enum dispatcher_type
{
    INFO,                                   // Logs with the '[INFO]:' prefix. Usually green;
    WARNING,                                // Logs with the '[WARNING]:' prefix. Usually yellow;
    ERROR,                                  // Logs with the '[ERROR]:' prefix. Usually red;
};

/* This function takes in a callback to one of the dispatcher messages and processes it */
static inline void
MESSAGE(msg_t cbfun, uint8_t type, char *msg)
{
    cbfun(type, msg);
}

/* Function templates */
EXTERN void __dispatcher_info(char *msg);   // Callback to the info log
EXTERN void __dispatcher_warn(char *msg);   // Callback to the warning log
EXTERN void __dispatcher_err(char *msg);    // Callback to the error log

#endif  // !_AOS_MESSAGE_DISPATCHER_H
