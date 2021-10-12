#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#ifndef _ANSI_H
#include <ansi.h>
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int        size_t;
#endif

#ifndef _SSIZE_T
#define _SSIZE_T
typedef int                 ssize_t;
#endif

#ifndef _TIME_T
#define _TIME_T
typedef long                time_t;
#endif

#ifndef _CLOCK_T
#define _CLOCK_T
typedef long                clock_t;
#endif

#ifndef _SIGSET_H
#define _SIGSET_H
typedef unsigned long       sigset_t;
#endif

typedef long                useconds_t;

typedef short               dev_t;
typedef char                gid_t;
typedef unsigned long       ino_t;
typedef unsigned short      mode_t;
typedef short               nlink_t;
typedef unsigned long       off_t;
typedef int                 pid_t;
typedef short               uid_t;
typedef unsigned long       zone_t;
typedef unsigned long       block_t;
typedef unsigned long       bit_t;
typedef unsigned short      zone1_t;
typedef unsigned short      bitchunk_t;

typedef long unsigned int   vir_bytes;

#ifndef _ADAMANTINE_STDINT_H
#include <stdint.h>
#endif

#endif
