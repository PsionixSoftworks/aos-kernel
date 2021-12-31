#ifndef _ADAMANTINE_VIRTUAL_FILESYSTEM_H
#define _ADAMANTINE_VIRTUAL_FILESYSTEM_H

#include <drivers/device.h>
#include <system/types.h>
#include <errno.h>
#include <macros.h>

#define MAX_MOUNTS          256
#define BLOCK_SIZE          512
#define BLOCKS_PER_SECTOR   8

struct filesystem;
struct file;
struct fs_ops;

struct filesystem {
    char name[MAX_NAME_LENGTH];
    struct fs_ops *ops;
    struct filesystem *next;
};

struct file {
    int flags;
    int mode;
    uid_t owner;
    gid_t group;
    off_t pos;
    void *data;
    char *path;
    char chbuffer;
};

struct fs_ops {
    unsigned long reentrant;
    char *fsname;

    int (*open)(struct file *_fd, char *_name);
    int (*close)(struct file *_fd);
    int (*read)(struct file *_fd, void *_data, size_t _size, off_t _pos);
    int (*write)(struct file *_fd, void *_data, size_t _size, off_t _pos);

    struct filesystem *(*mount)(struct device *);
};

extern int fs_initialize(void);
extern void file_seek(struct file *_file, int _pos);
extern struct filesystem *filesystem_register(char *name, struct fs_ops *ops);
extern struct file *open(const char *_path, int _flags);
extern int close(struct file *_fd);
extern ssize_t read(struct file *_fd, void *_buffer, size_t _buffer_size);
extern ssize_t write(struct file *_fd, const void *_data, size_t _data_size);
extern int fs_mount(char *_path, struct device *_device);

#endif
