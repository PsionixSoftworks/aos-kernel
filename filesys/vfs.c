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

#include <filesys/vfs.h>

static struct filesystem *virt_fs;

static void
vfs_set_root_directory(struct filesystem *fs, char *root)
{
    fs->root = root;
}

void
vfs_init(struct filesystem *fs, char *name, char *sysroot)
{
    terminal_printf("Initializing Virtual Filesystem...\n");
    virt_fs->current = fs;
    virt_fs->current->name = name;

    const char *root = sysroot;
    vfs_set_root_directory(virt_fs, root);
}

void
vfs_install(void)
{
    if (!virt_fs->current->installed)
    {
        virt_fs->current->installed = true;
    }
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

static int32_t file_id = 0;

struct file_struct *
vfs_file_open(char *filename, uint8_t mode)
{

    
    
}

void *
vfs_file_write(struct file_struct *file, void *data)
{
    
}

void *
vfs_file_read(struct file_struct *file)
{

}

void *
vfs_file_append(struct file_struct *file, void *data)
{

}

void *
vfs_file_close(struct file_struct *file)
{

}

char *
vfs_get_root_directory(struct filesystem *fs)
{
    return ((char *)fs->root);
}
