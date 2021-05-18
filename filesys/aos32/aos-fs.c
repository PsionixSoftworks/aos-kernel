/*
 *  File: aos-fs.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include <filesys/aos-fs.h>
#include <kernel/system/terminal.h>
#include <stdlib.h>
#include <string.h>

static aosfs_t *fs;
static struct aos_directory *main_dir;

aosfs_t *
aosfs_init(const char *name)
{
    terminal_printf("[INFO]: %s Filesystem Initializing...\n", name);

    char *root;
    root = "$0://";

    fs->root = (char *)malloc(strlen(root) + 1);
    fs->root = (char *)strcpy(fs->root, root);

    fs->dir = main_dir;
    fs->dir->name = malloc(strlen(root) + 1);
    fs->dir->name = strcpy(fs->dir->name, fs->root);

    terminal_printf("[INFO]: %s initialized!\n", name);

    return (fs);
}

int8_t
aosfs_create_directory(struct aos_filesystem *aosfs, char *dirname)
{
    terminal_printf("Creating directory \"%s\" in \"%s\"...", dirname, aosfs->dir->name);
    aosfs->dir->name = strcat(aosfs->dir->name, dirname);

    terminal_printf("Entering directory \"%s\"\n", aosfs->dir->name);

    return (1);
}

char *
aosfs_directory_get_current(struct aos_filesystem *aosfs)
{
    return (aosfs->dir->name);
}

const char *
aosfs_get_sysroot(void)
{
    return (fs->root);
}
