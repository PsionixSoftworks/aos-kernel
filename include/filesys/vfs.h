/*
 *  File: vfs.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _virtual_FILESYS_
#define _virtual_FILESYS_

#include <stdint.h>

#define FS_WRITE    0
#define FS_READ     1
#define FS_APPEND   2

struct fs_container;
struct filesystem;
struct file;

struct fs_container {
    const char *name;
    unsigned long index;
    unsigned long flags;
    struct fs_container *last;
    struct fs_container *next;
} PACKED;

struct filesystem {
    char *root;
    char *name;
    struct filesystem *current;
} PACKED;

struct file {
    char *name;
    unsigned long flags;
};

void vfs_init(const struct filesystem *filesystem);
void vfs_install(void);
int vfs_mount(struct filesystem *filesystem);

void *vfs_directory_create(struct filesystem *fs, char *dirname);
void *vfs_directory_delete(struct filesystem *fs, char *dirname);
void *vfs_directory_rename(struct filesystem *fs, char *dirname, char *newname);

struct filesystem *vfs_file_open(char *filename, uint8_t mode);
void *vfs_file_write(struct filesystem *fs, void *data);
void *vfs_file_read(struct filesystem *fs);
void *vfs_file_append(struct filesystem *fs, void *data);
void *vfs_file_close(struct filesystem *fs);

int8_t vfs_check_permission(struct filesystem *fs, struct file *f, unsigned long flags);

#endif
