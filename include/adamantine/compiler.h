#ifndef _ADAMANTINE_COMPILER_H
#define _ADAMANTINE_COMPILER_H

#if defined(__GNUC__) && __GNUC__ > 3
#ifndef __STANDARD_ATTRIBUTES__
#define __STANDARD_ATTRIBUTES__
#define NORETURN						__attribute__((noreturn))
#define PACKED				            __attribute__((packed))
#define USED					        __attribute__((used))
#define UNUSED				            __attribute__((unused))
#define HOT                             __attribute__((hot))
#define COLD                            __attribute__((cold))
#define DEPRECATED		                __attribute__((deprecated))
#define SECTION(name)	                __attribute__((section(name)))
#define ALIGN(x)                        __attribute__((aligned(x)))
#define ACCESS(mode)	                __attribute__((access(mode)))
#endif	// !__STANDARD_ATTRIBUTES__
#endif

#endif
