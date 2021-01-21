/*
 *  File: ext2.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _EXT2_H
#define _EXT2_H

#include <stdint.h>

#ifndef _EXT2_H
#define _EXT2_H
#endif

#define EXT2_SIGNATURE      0xEF53

#define INODE_TYPE_FIFO         0x1000
#define INODE_TYPE_CHAR_DEV     0x2000
#define INODE_TYPE_DIRECTORY    0x4000
#define INODE_TYPE_BLOCK_DEV    0x6000
#define INODE_TYPE_FILE         0x8000
#define INODE_TYPE_SYMLINK      0xA000
#define INODE_TYPE_SOCKET       0xC000

#if defined(__cplusplus)
extern "C" {
#endif



#if defined(__cplusplus)
}
#endif

#endif  // !_EXT2_H