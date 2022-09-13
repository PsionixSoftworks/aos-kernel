#ifndef _COMPILER_H
#define _COMPILER_H

/* Make sure we're compiling using GCC. the '__attribute__' function is specific to it */
#if defined(__GNUC__) && __GNUC__ > 3
#ifndef __STANDARD_ATTRIBUTES__							
#define __STANDARD_ATTRIBUTES__
#define __noreturn		__attribute__((noreturn))		// Used on functions that cannot return
#define __packed		__attribute__((packed))			// Pack to the smallest size/alignment 
#define __used			__attribute__((used))			// Force the compiler to use function that does not appear to be used
#define __unused		__attribute__((unused))			// Force the compiler to consider that the function is not used
#define __hot         	__attribute__((hot))			// Hot spot of the compiled program
#define __cold        	__attribute__((cold))			// Optimize for speed, unlikely to be executed
#define __deprecated	__attribute__((deprecated))		// Mark function as deprecated, a function that is to be removed soon
#define __section(name)	__attribute__((section(name)))	// Change the section the code is placed under; Default is .text
#define __align(x)		__attribute__((aligned(x)))		// Specify minimum alignment (in bytes)
#define __access(mode)	__attribute__((access(mode)))	// ??
#define __cdecl__		__attribute__((__cdecl__))		// Code Call Convention
#define __stdcall__		__attribute__((__stdcall__))	// Standard Calling Convention
#define __constructor	__attribute__((constructor))	// For global constructors
#endif	// __STANDARD_ATTRIBUTES__
#endif	// __GNUC__

#if defined(__ADM_COMPILER__)
extern void compile(void *, char *);					// Compile the source code (void *) to the output file (char *)
#endif	// __ADM_COMPILER__

#endif	// _COMPILER_H
