/*
 *  File: aos-fs.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _AOS_FILE_SYSTEM_H
#define _AOS_FILE_SYSTEM_H

#include <stdint.h>

#define AOS_ROOT_DIRNAME            "$0://sysroot/"
#define AOS_FILE_SYSTEM_NAME        "AOS-32"
#define AOS_DIRECTORY_MAX_LENGTH    256
#define AOS_READ                    0x72
#define AOS_WRITE                   0x77

#define DRIVE0                      "$0://"
#define DRIVE1                      "$1://"
#define DRIVE2                      "$2://"
#define DRIVE3                      "$3://"
#define DRIVE4                      "$4://"

#ifndef ROOT_DRIVE
#define ROOT_DRIVE                  DRIVE0
#endif

#ifndef SYSROOT_DIRECTORY
#define SYSROOT_DIRECTORY           ROOT_DRIVE##"sysroot/"
#endif

struct aos_filesystem;
struct aos_directory;

struct aos_filesystem {
    const char *name;
    const char *root;
    struct aos_directory *dir;
} __attribute__((packed));

struct aos_directory {
    char *name;
    struct aos_directory *current;
};

struct aos_filesystem *aosfs_init(const char *name);
int8_t aosfs_create_directory(struct aos_filesystem *aosfs, struct aos_directory *dir, char *dirname);
char *aosfs_directory_get_current(struct aos_filesystem *aosfs);

const char *aosfs_get_sysroot(void);

#endif
