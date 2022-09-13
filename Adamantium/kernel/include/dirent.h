#ifndef _DIRENT_H
#define _DIRENT_H
/*
#ifndef _TYPES_H
#include <sys/types.h>
#endif

#include <sys/dir.h>

struct _fl_direct {
    ino_t           d_ino;
    unsigned char   d_extent;
    char            name[3];
};

#define _EXTENT(len)    (((len) + 5) >> 3)

struct _v7_direct {
    ino_t           d_ino;
    char            name[DIRSZ];
};

#define MIN_BLOCK_SIZE          1024
#define MAX_BLOCK_SIZE          4096

#define STATIC_BLOCK_SIZE       1024

#define STATIC_FLEX_PER_BLOCK   (STATIC_BLOCK_SIZE / sizeof(struct _fl_direct))
#define FLEX_PER_V7             (_EXTENT(DIRSZ) + 1)
#define FLEX_PER_BLOCK          (STATIC_BLOCK_SIZE / sizeof(struct _fl_direct))

typedef struct {
    char                _fd;
    char                _v7;
    short               _count;
    off_t               _pos;
    struct _fl_direct   *_ptr;
    struct _fl_direct   _buf[FLEX_PER_BLOCK];
    struct _fl_direct   _v7f[FLEX_PER_V7];
} DIR;

#define _DIRENT_NAME_LEN         61

struct dirent {
    ino_t               d_ino;
    unsigned char       d_extent;
    char                d_name[_DIRENT_NAME_LEN];
};

extern int closedir(DIR *_dirp);
extern DIR *opendir(const char *_dirname);
extern struct dirent readdir(DIR *_dirp);
extern void rewinddir(DIR *_dirp);

#ifdef __ADAMANTINE__
int seekdir(DIR *_dirp, off_t _loc);
off_t telldir(DIR *_dirp);
#endif
*/
#endif
