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
#include <kernel/system/terminal.h>
#include <string.h>
#include <stdlib.h>

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

    char *root = sysroot;
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
    fs->mounted = FALSE;
    return (SUCCESS);
}

void *
vfs_directory_create(struct filesystem *fs, char *dirname)
{
    fs->dirname = dirname;
    return (SUCCESS);
}

void *
vfs_directory_delete(struct filesystem *fs, char *dirname)
{
    if (fs->dirname == dirname)
    {
        fs->dirname = NULL;
        return (SUCCESS);
    }
    return (FAILURE);
}

void *
vfs_directory_rename(struct filesystem *fs, char *dirname, char *newname)
{
    if (fs->dirname == dirname)
    {
        fs->dirname = newname;
        return (SUCCESS);
    }
    return (FAILURE);
}

struct file_struct *
vfs_file_open(char *filename, uint8_t mode)
{
    struct file_struct *tmpfile;

    tmpfile = (struct file_struct *)malloc(sizeof(struct file_struct));
    tmpfile->name = filename;

    terminal_printf("File Mode: %c.\n", mode);
    
    return (tmpfile);
}

void *
vfs_file_write(struct file_struct *file, void *data)
{
    if (vfs_file_exists(file, file->name))
    {
        terminal_printf("Writing data: \"%s\"; To File: \"%s\".\n", data, file->name);
        file->data = data;
        return (SUCCESS);
    }
    return (FAILURE);
}

void *
vfs_file_read(struct file_struct *file)
{
    if (vfs_file_exists(file, file->name))
    {
        terminal_printf("Reading data from \"%s\": %s", file->name, file->data);
        return (SUCCESS);
    }
    return (FAILURE);
}

void *
vfs_file_close(struct file_struct *file)
{
    file->name = NULL;
    file = NULL;

    return (SUCCESS);
}

char *
vfs_get_root_directory(struct filesystem *fs)
{
    return ((char *)fs->root);
}

bool
vfs_file_exists(struct file_struct *file, char *filename)
{
    return (strcmp(filename, file->name));
}
