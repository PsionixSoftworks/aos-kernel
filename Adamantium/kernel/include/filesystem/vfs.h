#ifndef _VFS_H
#define _VFS_H

#include <system/types.h>
#include <stdint.h>

#define USE_COMMON_HEADERS
#include <adamantium/adamantium.h>

#include "mount_list.h"
#include "path.h"

#define FS_FILE         0x01
#define FS_DIRECTORY    0x02
#define FS_CHARDEVICE   0x03
#define FS_BLOCKDEVICE  0x04
#define FS_PIPE         0x05
#define FS_SYMLINK      0x06
#define FS_MOUNTPOINT   0x08

struct mount_point
{
    uint8_t flags;
    struct mount_point* next;
};

typedef struct fs
{
    /* File operations (to be added to...) */
    void*(*fopen)(char*, uint8_t, struct mount_point*);
    void*(*fread)(char*, struct mount_point*);
    void*(*fwrite)(char*, void*, struct mount_point*);
    void*(*fclose)(char*, struct mount_point*);

    /* Directory Operations (to be added to...) */
    void*(*d_create)(char*, struct mount_point*);
    void*(*d_delete)(char*, struct mount_point*);
    void*(*d_rename)(char*, char*, struct mount_point*);
    void*(*d_open)(char*, struct mount_point*);
    void*(*d_readdir)(char*, struct mount_point*);
    void*(*d_close)(char*, struct mount_point*);
} vfs_t;

void* fs_create(char* name, uint32_t where, struct device* dev, vfs_t* fsptr);
void* fs_mount(coid* id, int addr, struct mount_point* mp);

void* fs_file_open(char* filename, uint8_t mode, struct mount_point* mp);

#endif
