#include <filesystem/fs.h>

fs_node_t *fs_root = 0;

uint32_t
read_fs(fs_node_t *_node, uint32_t _offset, uint32_t _size, uint8_t *_buffer)
{
	if (_node->read != 0)
		return _node->read(_node, _offset, _size, _buffer);
	else
		return 0;
}

uint32_t
write_fs(fs_node_t *_node, uint32_t _offset, uint32_t _size, uint8_t *_buffer)
{
	if (_node->write != 0)
		return _node->write(_node, _offset, _size, _buffer);
	else
		return 0;
}

void
open_fs(fs_node_t *_node, uint8_t _read, uint8_t _write)
{
	// ^^ Unused parameters? Perhaps later on?
	if (_node->open != 0)
		return _node->open(_node);
}

void
close_fs(fs_node_t *_node)
{
	if (_node->close != 0)
		return _node->close(_node);
}

struct dirent *
readdir_fs(fs_node_t *_node, uint32_t _index)
{
	if ((_node->flags & 0x7) == FS_DIRECTORY && _node->readdir != 0)
		return _node->readdir(_node, _index);
	else
		return 0;
}

fs_node_t *
finddir_fs(fs_node_t *_node, char *_name)
{
	if ((_node->flags & 0x7) == FS_DIRECTORY && _node->finddir != 0)
		return _node->finddir(_node, _name);
	else
		return 0;
}
