#ifndef _DEBUG_H
#define _DEBUG_H

#include <kernel/version.h>

#if (KERNEL_VERSION_NUMBER <= 40)
#include <adamantine/tty.h>
#else
#include <drivers/tty.h>
#endif

#include <iso646.h>

#if defined(__DEBUG__) && __DEBUG__ == 1
#define show_debug_info(msg)        k_tty_printf("[INFO]: %s\n", msg);
#define show_debug_warning(msg)     k_tty_printf("[WARNING]: %s\n", msg);
#define show_debug_error(msg)       k_tty_printf("[ERROR]: %s\n", msg);
#else
#define show_debug_info(msg)        
#define show_debug_warning(msg)     
#define show_debug_error(msg)       
#endif

#endif
