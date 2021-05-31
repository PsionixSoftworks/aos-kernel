#ifndef _ADAMANTINE_COMPILER_H
#define _ADAMANTINE_COMPILER_H

/* Make sure we're compiling using GCC. the '__attribute__' function is specific to it */
#if defined(__GNUC__) && __GNUC__ > 3
#ifndef __STANDARD_ATTRIBUTES__							
#define __STANDARD_ATTRIBUTES__
#define NORETURN		__attribute__((noreturn))		// Used on functions that cannot return
#define PACKED			__attribute__((packed))			// Pack to the smallest size/alignment 
#define USED			__attribute__((used))			// Force the compiler to use function that does not appear to be used
#define UNUSED			__attribute__((unused))			// Force the compiler to consider that the function is not used
#define HOT         	__attribute__((hot))			// Hot spot of the compiled program
#define COLD        	__attribute__((cold))			// Optimize for speed, unlikely to be executed
#define DEPRECATED		__attribute__((deprecated))		// Mark function as deprecated, a function that is to be removed soon
#define SECTION(name)	__attribute__((section(name)))	// Change the section the code is placed under; Default is .text
#define ALIGN(x)		__attribute__((aligned(x)))		// Specify minimum alignment (in bytes)
#define ACCESS(mode)	__attribute__((access(mode)))	// ??
#endif	// !__STANDARD_ATTRIBUTES__
#endif

#endif
