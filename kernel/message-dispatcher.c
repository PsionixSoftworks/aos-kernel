#include <adamantine/message-dispatcher.h>
#include <kernel/system/terminal.h>
#include <kernel/system/system.h>

static inline void
dispatch_message(uint8_t type, char *msg)
{
    switch (type)
    {
        case INFO:
            terminal_printf("%s%s", "[INFO]: ", msg);
            handle_dispatched_message(type, msg);
            break;
        case WARNING:
            terminal_printf("%s%s", "[WARNING]: ", msg);
            handle_dispatched_message(type, msg);
            break;
        case ERROR:
            terminal_printf("%s%s", "[ERROR]: ", msg);
            handle_dispatched_message(type, msg);
            break;
        default:
            terminal_printf("%s%s", "[INFO]: ", msg);
            handle_dispatched_message(type, msg);
            break;
    };
}

void
__dispatcher_info(char *msg)
{
    MESSAGE(dispatch_message, INFO, msg);

}

void
__dispatcher_warn(char *msg)
{
    MESSAGE(dispatch_message, WARNING, msg);
}

void
__dispatcher_err(char *msg)
{
    MESSAGE(dispatch_message, ERROR, msg);
}
