#ifndef _ADAMANTINE_INITRD_H
#define _ADAMANTINE_INITRD_H

#include "vfs.h"

typedef struct
{
	uint32_t nfiles;		// Number of files in the ramdisk.
} initrd_header_t;

typedef struct
{
	uint8_t magic;
	int8_t name[64];
	uint32_t offset;
	uint32_t length;
} initrd_file_header_t;

#endif
