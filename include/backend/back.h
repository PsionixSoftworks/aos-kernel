#ifndef _AOS_BACKEND_MODULE_
#define _AOS_BACKEND_MODULE_

/* Test Macros (WARNING: DO NOT USE THESE IN THE ACTUAL KERNEL!!!) */
#define __AOS_BASEMENT__(x, z)
#define __SYSTEM_IPAR               __AOS_BASEMENT__(0x0A, 0xFF)
#define __SYSTEM_OPAR               __AOS_BASEMENT__(0x0B, 0xFF)

/* Official Macros */
#define __kernel_only               /* Used to determine if a function is a kernel only member. */

#endif
