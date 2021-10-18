#ifndef _DEBUG_H
#define _DEBUG_H

#include <adamantine/tty.h>
#include <iso646.h>

#if defined(__DEBUG__) and __DEBUG__ == 1
#define show_debug_info(msg)        tty_printf("[INFO]: %s\n", msg);
#define show_debug_warning(msg)     tty_printf("[WARNING]: %s\n", msg);
#define show_debug_error(msg)       tty_printf("[ERROR]: %s\n", msg);
#endif

#endif
