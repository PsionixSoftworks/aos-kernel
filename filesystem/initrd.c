#include <filesystem/initrd.h>
#include <kernel/memory/memory-util.h>
#include <stdlib.h>
#include <string.h>

initrd_header_t *initrd_header;
initrd_file_header_t *file_headers;
fs_node_t *initrd_root;
fs_node_t *initrd_dev;
fs_node_t *root_nodes;
int nroot_nodes;

struct dirent dirent;

static uint32_t
initrd_read(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer)
{
	initrd_file_header_t header = file_headers[node->inode];
	if (offset > header.length)
		return 0;
	if (offset + size > header.length)
		size = header.length - offset;
	memcpy(buffer, (uint8_t *)(header.offset + offset), size);
	return size;
}

static struct dirent *
initrd_readdir(fs_node_t *node, uint32_t index)
{
	if (node == initrd_root && index == 0)
	{
		strcpy(dirent.name, "dev");
		dirent.name[3] = 0;
		dirent.ino = 0;
		return &dirent;
	}

	if (index - 1 >= nroot_nodes)
		return 0;
	strcpy(dirent.name, root_nodes[index - 1].name);
	dirent.name[strlen(root_nodes[index - 1].name)] = 0;
	dirent.ino = root_nodes[index - 1].inode;
	return &dirent;
}

static fs_node_t *
initrd_finddir(fs_node_t *node, char *name)
{
	if (node == initrd_root && !strcmp(name, "dev"))
		return initrd_dev;
	int i;
	for (i = 0; i < nroot_nodes; i++)
		if (!strcmp(name, root_nodes[i].name))
			return &root_nodes[i];
	return 0;
}

fs_node_t *
initialize_initrd(uint32_t location)
{
	initrd_header = (initrd_header_t *)location;
	file_headers = (initrd_file_header_t *)(location + sizeof(initrd_header_t));

	//initrd_root = (fs_node_t *)kmalloc()
}
