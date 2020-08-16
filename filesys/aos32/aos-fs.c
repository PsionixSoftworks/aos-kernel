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

#include "../../include/aos-fs.h"
#include "../../include/aos-defs.h"
#include "../../include/mem-util.h"
#include "../../include/terminal.h"

MODULE("aos-fs", "0.01a");

static inline Directory_t *
aos_set_root(string root) 
{
    Directory_t *directory;
    directory->root_dir = root;
    return (directory);
}

static inline void
aosfs_mount(void)
{

}

void 
aosfs_init(string fs_name)
{
    Directory_t *directory = aos_set_root(AOS_ROOT_DIRNAME);
    directory->fs_name = fs_name;

    aosfs_mount();
}


