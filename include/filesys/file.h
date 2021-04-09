#ifndef _FILE_H
#define _FILE_H

#include <stdint.h>
#include <adamantine/aos-defs.h>

#define FILENAME_MAX_LENGTH     256
#define FS_READ_ONLY            0x1000
#define FS_WRITE_ONLY           0x2000
#define FS_READ_WRITE           0x4000

struct file
{
    uint16_t owner;
    void *data;
    char path[FILENAME_MAX_LENGTH];
};

extern void *fopen(struct file *f, char op);
extern void *fclose(struct file *f);
extern void *fread(struct file *f, void *buffer, size_t size);
extern void fwrite(struct file *f, void *buffer, size_t size);

#endif
