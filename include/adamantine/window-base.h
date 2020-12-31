#ifndef _AOS_WINDOW_BASE_H
#define _AOS_WINDOW_BASE_H

#include <adamantine/adamantine.h>

struct window;

#define WTK_T       struct window *wnd_t;
#define WND_ENTRY   WTK_T;

WND_ENTRY window_init(void (*wndfunc)(char *name, uint32_t width, uint32_t height, uint32_t depth));

#endif
