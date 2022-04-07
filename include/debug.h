#ifndef _DEBUG_H
#define _DEBUG_H

#include <kernel/version.h>

#if (KERNEL_VERSION_NUMBER <= 40)
#include <adamantine/tty.h>
#else
#include <drivers/tty.h>
#endif

#include <iso646.h>

#define INFO		0
#define WARNING		1
#define ERROR		2

void print_verbose_message(const char *_Msg, const int _Severity);

#endif
