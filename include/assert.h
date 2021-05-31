#ifndef _ADAMANTINE_ASSERT_H
#define _ADAMANTINE_ASSERT_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

/* Define the assert function */
#ifndef assert
#define assert(msg)     __assert(msg, __FILE__, __LINE__);
#endif

/* Function Templates */
extern void __assert(char *msg, char *filename, unsigned int lineno);

#endif  // !_ADAMANTINE_ASSERT_H
