#ifndef _ERRNO_H
#define _ERRNO_H

/* POSIX Error Number Codes */
#define EPERM           1
#define ENOENT          2
#define ESRCH           3
#define EINTR           4
#define EIO             5
#define ENXIO           6
#define E2BIG           7
#define ENOEXEC         8
#define EBADF           9
#define ECHILD          10
#define EDEADLK         11

#define ENOMEM          12
#define EACCESS         13
#define EFAULT          14
#define ENOTBLK         15
#define EBUSY           16
#define EEXIST          17
#define EXDEV           18
#define ENODEV          19
#define ENOTDIR         20
#define EISDIR          21
#define EINVAL          22
#define ENFILE          23
#define EMFILE          24
#define ENOTTY          25
#define ETXTBUSY        26
#define EFBIG           27
#define ENOSPC          28
#define ESPIPE          29
#define EROFS           30
#define EMLINK          31
#define EPIPE           32

#define EDOM            33
#define ERANGE          34

#define EAGAIN          35
#define EWOULDBLOCK     EAGAIN
#define EINPROGRESS     36
#define EALREADY        37

#define ENAMETOOLONG    38
#define ENOLCK          39
#define ENOSYS          40
#define ENOTEMPTY       41
#define EILSEQ          42

/* POSIX Error Codes for networking */
#define ENOTSOCK        48
#define EDESTADDRREQ    49
#define EMSGSIZE        50
#define EPROTOTYPE      51
#define ENOPROTOOPT     52
#define EPROTONOSUPPORT 53
#define ESOCKTNOSUPPORT 54
#define EOPNOTSUPP      55
#define EPFNOSUPPORT    56
#define EAFNOSUPPORT    57
#define EADDRINUSE      58
#define EADDRNOTAVAIL   59
#define ENETDOWN        60
#define ENETUNREACH     61
#define ENETRESET       62
#define ECONNABORTED    63
#define ECONNRESET      64
#define ENOBUFS         65
#define EISCONN         66
#define ENOTCONN        67
#define ESHUTDOWN       68
#define ETOOMANYREFS    69
#define ETIMEDOUT       70
#define ECONNREFUSED    71
#define ELOOP           72
#define EWSNAMETOOLONG  73
#define EHOSTDOWN       74
#define EHOSTUNREACH    75
#define EWSNOTEMPTY     76
#define EPROCLIM        77
#define EUSERS          78
#define EDQUOT          79
#define ESTALE          80
#define EREMOTE         81

#define MAX_ERRNO       4095

#endif
