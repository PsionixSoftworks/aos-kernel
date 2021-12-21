#ifndef _DEBUG_H
#define _DEBUG_H

#include <kernel/version.h>

#if (KERNEL_VERSION_NUMBER <= 40)
#include <adamantine/tty.h>
#else
#include <drivers/tty.h>
#endif

#include <iso646.h>

#if defined(__DEBUG__) and __DEBUG__ == 1
#define show_debug_info(msg)        tty_printf("[INFO]: %s\n", msg);
#define show_debug_warning(msg)     tty_printf("[WARNING]: %s\n", msg);
#define show_debug_error(msg)       tty_printf("[ERROR]: %s\n", msg);
#else
#define show_debug_info(msg)        msg
#define show_debug_warning(msg)     msg
#define show_debug_error(msg)       msg
#endif

#endif
