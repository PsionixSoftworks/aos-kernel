#ifndef _DEBUG_H
#define _DEBUG_H

#include <kernel/version.h>

#if (KERNEL_VERSION_NUMBER <= 40)
#include <adamantine/tty.h>
#else
#include <drivers/tty.h>
#endif

#include <iso646.h>

#if defined(__DEBUG__) and (__DEBUG__ == 1)
#define show_debug_info(...)        k_tty_set_foreground(SYSTEM_COLOR_LT_GREEN);    \
                                    k_tty_printf("[INFO]: ");                       \
                                    k_tty_printf( __VA_ARGS__ );                    \
                                    k_tty_println();                                \
                                    k_tty_set_foreground(SYSTEM_COLOR_GRAY);
#define show_debug_warning(...)     k_tty_set_foreground(SYSTEM_COLOR_YELLOW);      \
                                    k_tty_printf("[WARNING]: ");                    \
                                    k_tty_printf( __VA_ARGS__ );                    \
                                    k_tty_println();                                \
                                    k_tty_set_foreground(SYSTEM_COLOR_GRAY);
#define show_debug_error(...)       k_tty_set_foreground(SYSTEM_COLOR_RED);         \
                                    k_tty_printf("[ERROR]: ");                      \
                                    k_tty_printf( __VA_ARGS__ );                    \
                                    k_tty_println();                                \
                                    k_tty_set_foreground(SYSTEM_COLOR_GRAY);
#else
#define show_debug_info(...)        
#define show_debug_warning(...)     
#define show_debug_error(...)       
#endif

#endif
