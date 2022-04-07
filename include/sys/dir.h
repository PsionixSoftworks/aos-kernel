#ifndef _DIR_H
#define _DIR_H

#include <sys/types.h>

#define DIRBLKSZ        512

#ifndef DIRSZ
#define DIRSZ           60
#endif

struct direct {
    ino_t d_ino;
    char d_name[DIRSZ];
};

#endif
