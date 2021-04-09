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

#ifndef _AOS_VFS_H
#define _AOS_VFS_H

#include "file.h"

#define MAX_MOUNTABLE_DEVICES   16

struct virtual_filesystem
{
    char name[10];
    uint8_t max_file_length;
    uint32_t max_file_size;
};

#endif  // !_AOS_VFS_H
