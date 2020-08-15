#ifndef ADAMANTINE_STANDARD_DEFINITIONS
#define ADAMANTINE_STANDARD_DEFINITIONS

#include "terminal.h"

#define OS_NAME                             "AdamantineOS"
#define OS_VERSION                          "0.04a"
#define OS_SIGNATURE                        "{0:0:0:0~0}"

// Define the boolean operators true and false:
#ifndef BOOLEAN_OPS

#ifndef FALSE
#define FALSE								0
#endif

#ifndef TRUE
#define TRUE								1
#endif

#endif

// Define Adamantine API macros:
#ifndef ADAMANTINE_MACROS
#define FAILSAFE
#define NULL								(void *)0
#define FAILURE								(void *)FALSE
#define SUCCESS								(void *)TRUE
#endif

// Define the module naming system for later use:
#ifndef ADAMANTINE_MODULE
#define ADAMANTINE_MODULE
#define MODULE(name, version) 	static char *_name       = "MODULE("#name").name";    \
                                static char *_version    = "MODULE("#version").version";
#define MODULE_GET_NAME(void)   _name;
#define MODULE_GET_VERS(void)   _version;
#endif	// !MODULE_DESCRIPTOR

#ifndef __STANDARD_ATTRIBUTES__
#define __STANDARD_ATTRIBUTES__
#define PACKED				            __attribute__((__packed__))
#define USED					        __attribute__((__used__))
#define UNUSED				            __attribute__((__unused__))
#define HOT                             __attribute__((__hot__))
#define COLD                            __attribute__((__cold__))
#define DEPRECATED		                __attribute__((deprecated))
#define SECTION(name)	                __attribute__((section(name)))
#define _TEXT                           SECTION(".text")
#define _MULTIBOOT                      SECTION(".multiboot")
#define _RODATA                         SECTION(".rodata")
#define _DATA                           SECTION(".data")
#define _BSS                            SECTION(".bss")
#define ACCESS(mode)	                __attribute__((access(mode)))
#endif	// !__STANDARD_ATTRIBUTES__

#endif	// !ADAMANTINE_STANDARD_DEFINITIONS
