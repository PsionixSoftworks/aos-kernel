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

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>
#include <adamantine/aos-string.h>
#include <kernel/drivers/driver.h>

struct aos_device;

typedef struct aos_fs 
{
    char *name;
    uint8_t (*probe)(struct aos_device *);
    uint8_t (*read)(char *, char *, struct aos_device *, void *);
    uint8_t (*read_dir)(char *, char *, struct aos_device *, void *);
    uint8_t (*touch)(char *fn, struct aos_device *, void *);
    uint8_t (*write_file)(char *fn, char *buf, uint32_t len, struct aos_device *, void *);
    uint8_t (*exists)(char *filename, struct aos_device *, void *);
    uint8_t (*mount)(struct aos_device *, void *);
    int8_t *priv_data;
} filesystem_t;

typedef struct mount_info 
{
    char *loc;
    struct aos_device *device;
} mount_info_t;

extern uint8_t vfs_read(char *f, char *buffer);
extern uint32_t vfs_ls(char *d, char *buffer);
extern uint8_t vfs_exists_in_dir(char *wd, char *fn);
extern void vfs_init(void);
extern uint8_t list_mount(void);
extern uint8_t device_try_to_mount(struct aos_device *device, char *fn);

#endif
