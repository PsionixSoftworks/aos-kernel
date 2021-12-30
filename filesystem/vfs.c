#include <filesystem/vfs.h>
#include <filesystem/mount.h>
#include <drivers/device.h>
#include <drivers/tty.h>

struct mount *mounts[MAX_MOUNTS];
struct mount *root = 0;
int mount_num = 0;

struct fs_ops *ops[8];
static int ops_num = 0;
