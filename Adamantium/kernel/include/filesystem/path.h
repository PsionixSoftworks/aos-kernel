#ifndef _FILESYSTEM_PATH_H
#define _FILESYSTEM_PATH_H

#include <memory/memory-util.h>

struct path_node
{
	char* name;
	struct path_node* next;
};

#endif
