#ifndef _FS_H
#define _FS_H

#include <stdint.h>

struct filesystem;
struct mount;

struct filesystem
{
    char *name;
    struct filesystem *curr;
    struct filesystem *next;
    struct filesystem *prev;
};

struct mount
{
    char *pt;
    struct filesystem *fs;
};

#endif
