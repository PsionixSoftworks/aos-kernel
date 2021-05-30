#ifndef _ADAMANTINE_ASSERT_H
#define _ADAMANTINE_ASSERT_H

#define KERNEL_ONLY

extern void __assert(char *msg, char *filename, unsigned int lineno);

#ifndef assert
#define assert(msg)     __assert(msg, __FILE__, __LINE__);
#endif

#endif  // !_ADAMANTINE_ASSERT_H
