#ifndef _FILE_H
#define _FILE_H

#include <stdint.h>

#define FILENAME_MAX_LENGTH     256
#define FS_READ_ONLY            0
#define FS_WRITE_ONLY           1
#define FS_READ_WRITE           2

struct file;

extern void *fopen(struct file *f, char op);
extern void *fclose(struct file *f);
extern void *fread(struct file *f, void *buffer, size_t size);
extern void fwrite(struct file *f, void *buffer, size_t size);

#endif
