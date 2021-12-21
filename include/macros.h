#ifndef _MACROS_H
#define _MACROS_H

/* Define the macro "EXTERN" for cases when C and C++ is used */
#if defined(__cplusplus)
#define EXTERN      extern "C"
#else
#define EXTERN      extern
#endif

/* Define global and local for the OS */
#define __GLOBAL    EXTERN
#define __LOCAL     static
#define __ILOCAL    __LOCAL inline
#define GLOBAL      __GLOBAL
#define LOCAL       __LOCAL

#ifndef _AOS_LENGTH_MACROS
#define MAX_NAME_LENGTH         32
#endif

#if !defined(KERNEL_API)
#if !defined(KERNEL_CDECL)
#define KERNEL_API      
#else
#define KERNEL_API      __cdecl__
#endif
#endif

#endif
