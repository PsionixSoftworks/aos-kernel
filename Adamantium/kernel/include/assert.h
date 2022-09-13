#ifndef _ADAMANTINE_ASSERT_H
#define _ADAMANTINE_ASSERT_H

#include <stdint.h>

#define panic(msg) 		__panic(msg, __FILE__, __LINE__);
#define assert(b) 		((b) ? (void)0 : __panic_assert(__FILE__, __LINE__, #b));

extern void __panic(const char *message, const char *file, uint32_t line);
extern void __panic_assert(const char *file, uint32_t line, const char *desc);

#endif  // !_ADAMANTINE_ASSERT_H
