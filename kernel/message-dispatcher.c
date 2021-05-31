#include <adamantine/message-dispatcher.h>
#include <adamantine/tty.h>
#include <kernel/system/system.h>

/* Message dispatcher */
static inline void
dispatch_message(uint8_t type, char *msg)
{
    switch (type)                                       // The type of message received
    {
        case INFO:
            tty_printf("%s%s", "[INFO]: ", msg);
            handle_dispatched_message(type, msg);
            break;
        case WARNING:
            tty_printf("%s%s", "[WARNING]: ", msg);
            handle_dispatched_message(type, msg);
            break;
        case ERROR:
            tty_printf("%s%s", "[ERROR]: ", msg);
            handle_dispatched_message(type, msg);
            break;
        default:
            tty_printf("%s%s", "[INFO]: ", msg);
            handle_dispatched_message(type, msg);
            break;
    };
}

/* Define the info dispatcher */
void
__dispatcher_info(char *msg)
{
    MESSAGE(dispatch_message, INFO, msg);

}

/* Define the warning dispatcher */
void
__dispatcher_warn(char *msg)
{
    MESSAGE(dispatch_message, WARNING, msg);
}

/* Define the error dispatcher */
void
__dispatcher_err(char *msg)
{
    MESSAGE(dispatch_message, ERROR, msg);
}
