#include <filesystem/vfs.h>
#include <filesystem/mount.h>
#include <drivers/device.h>
#include <drivers/tty.h>
#include <memory/memory-util.h>
#include <kernel/kernel.h>
#include <string.h>

struct mount *mounts[MAX_MOUNTS];
struct mount *root = 0;
int mount_num = 0;

struct fs_ops *ops[8];
static int ops_num = 0;

static inline struct mount *__vfs_check_mounts_intern(char *);
static inline int           __vfs_set_mount_intern(char *, struct device *, struct filesystem *);

int
fs_initialize(void)
{
    k_tty_printf("Initializing filesystems...\n");
    
    memset(mounts, 0, sizeof(mounts));
    memset(root, 0, sizeof(struct mount *));
    mount_num = 0;

    memset(ops, 0, sizeof(ops));
    ops_num = 0;

    // Initialize any filesystem here:
    
    k_tty_printf("Done!\n");

    return 0;
}

/* For now, we'll just set the pointer to the position, but later we'll make it more complex */
void
file_seek(struct file *_file, int _pos)
{
    _file->pos = _pos;
}

static inline struct mount *
__vfs_check_mounts_intern(char *_str)
{
    int i = 0;
    for (i = 0; i < mount_num; ++i)
    {
        if (!(strcmp(mounts[i]->point, _str)))
        {
            k_tty_printf("Mount Name: %s\n", _str);
            return mounts[i];
        }
    }
    return 0;
}

static inline int
__vfs_set_mount_intern(char *_path, struct device *_device, struct filesystem *_fs)
{
    struct mount *mount = (struct mount *)kmalloc(sizeof(*mount));
    if (!mount)
        return -ENOMEM;
    
    mount->point        = _path;
    mount->fs           = _fs;
    mount->device       = _device;
    mounts[mount_num++] = mount;

    if (strcmp(_path, "/") == 0)
        root = mount;
    return 0;
}

struct mount *
find_mount(char *_path)
{
    struct mount *ret = root;
    char *str;

    str = kmalloc(strlen(_path) + 1);
    strcpy(str, _path);
    if (strcmp(str, "/") == 0)
        goto out;
    
    while (strlen(str) > 1)
    {
        ret = __vfs_check_mounts_intern(str);
        if (ret)
            goto out;
        str[strlen(str) - 1] = 0;
    }

    ret = root;
out:
    kfree(str);
    return ret;
}

struct filesystem *
vfs_mount_fs(struct device *_device)
{
    struct filesystem *fs = 0;
    for (int i = 0; i < ops_num; ++i)
    {
        if (ops[i]->mount)
        {
            fs = ops[i]->mount(_device);
            if ((fs) && (!IS_ERR(fs)))
                return fs;
        }
    }
    return 0;
}

int 
fs_mount(char *_path, struct device *_device)
{
    if ((!root) && (strcmp("/", _path) != 0))
        return -EAGAIN;
    
    if (root)
    {
        // TODO: Figure out what goes here...
    }

    struct filesystem *fs = vfs_mount_fs(_device);
    if (!fs)
        return -ENXIO;
    
    k_tty_printf("%s: fs->name: %s\n", __func__, fs->ops->fsname);
    return __vfs_set_mount_intern(_path, _device, fs);
}
