/*
 *  File: vfs.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include <adamantine/adamantine.h>

static struct filesystem *virt_fs;

static void
vfs_set_root_directory(struct filesystem *fs, char *root)
{
    fs->root = root;
}

void
vfs_init(const struct filesystem *fs)
{
    terminal_printf("Initializing Virtual Filesystem...\n");
    virt_fs = fs->current;
    virt_fs->name = "Virtual Filesystem";

    const char *root = "$0:/root/";
    vfs_set_root_directory(virt_fs, root);
}

void
vfs_install(void)
{

}

int
vfs_mount(struct filesystem *fs)
{

}

void *
vfs_directory_create(struct filesystem *fs, char *dirname)
{

}

void *
vfs_directory_delete(struct filesystem *fs, char *dirname)
{

}

void *
vfs_directory_rename(struct filesystem *fs, char *dirname, char *newname)
{

}

struct filesystem *
vfs_file_open(char *filename, uint8_t mode)
{

}

void *
vfs_file_write(struct filesystem *fs, void *data)
{

}

void *
vfs_file_read(struct filesystem *fs)
{

}

void *
vfs_file_append(struct filesystem *fs, void *data)
{

}

void *
vfs_file_close(struct filesystem *fs)
{

}
