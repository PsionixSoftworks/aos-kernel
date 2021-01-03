#ifndef _ASSERT_H
#define _ASSERT_H

#if defined(__cplusplus)
extern "C" {
#endif

void __assert(char *msg, char *filename, unsigned int lineno);

#if defined(__cplusplus)
}
#endif

#ifndef assert
#define assert(msg)     __assert(msg, __FILE__, __LINE__);
#endif

#endif
