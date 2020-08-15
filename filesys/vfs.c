#define KERNEL32    1

#include "../include/vfs.h"
#include "../include/terminal.h"
#include "../include/mem_util.h"
#include "../include/ext2.h"
#include "../include/aos-defs.h"

MODULE("virtual-filesystem", "0.01a");

#define MAX_MOUNTS      16

uint8_t __init_vfs = 0;

mount_info_t **mp = 0;
int last_mount_id = 0;

device_t *
check_mount(char *loc) 
{
    for (int i = 0; i < last_mount_id; i++) 
    {
        if (strcmp(loc, mp[i]->loc) == 0) 
        {
            return (mp[i]->device);
        }
    }
    return (0);
}

uint8_t 
list_mount(void) 
{
    for (int i = 0; i < MAX_MOUNTS; i++) 
    {
        if (!mp[i]) 
            break;
        terminal_printf("%s on %s type: %s\n", mp[i]->device->device_name, mp[i]->loc, mp[i]->device->fs->name);
    }
    return (1);
}

uint8_t 
device_try_to_mount(device_t *device, char *loc) 
{
    if ((!device) || !(device->device_id)) 
        return (0);
    if (check_mount(loc)) 
        return (0);
    #ifdef EXT2_FILESYSTEM
    if (ext2_probe(device)) 
    {
        if (ext2_mount(device, device->fs->priv_data)) 
        {
            mount_info_t *m = (mount_info_t *)malloc(sizeof(mount_info_t));
            m->loc = loc;
            m->device = device;
            last_mount_id++;
            mp[last_mount_id - 1] = m;
            return (1);
        }
        return (0);
    }
    #endif

    #ifdef AOS32_FILESYSTEM
    if (aos_fs_probe(device)) 
    {
        if (aos_fs_mount(device, device->fs->priv_data)) 
        {
            mount_info_t *m = (mount_info_t * )malloc(sizeof(mount_info_t));
            m->loc = loc;
            m->device = device;
            last_mount_id++;
            mp[last_mount_id - 1] = m;
            return (1);
        }
        return (0);
    }
    #endif

    return (0);
}

uint8_t 
__find_mount(char *filename, int *adjust) 
{
    char *orig = (char *)malloc(strlen(filename) + 1);
    memset(orig, 0, strlen(filename) + 1);
    memcpy(orig, filename, strlen(filename) + 1);
    if (orig[strlen(orig)] == '/') 
        str_backspace(orig, '/');
    while (1) 
    {
        for (int i = 0; i < MAX_MOUNTS; i++) 
        {
            if (!mp[i]) 
                break;
            if (strcmp(mp[i]->loc, orig) == 0) 
            {
                *adjust = (strlen(orig) - 1);
                free(orig);
                return (1);
            }
        }
        if (strcmp(orig, "/") == 0)
            break;
        str_backspace(orig, '/');
    }
    return (0);
}

uint8_t 
vfs_read(char *filename, char *buffer) 
{
    int adjust = 0;
    int i = __find_mount(filename, &adjust);
    filename += adjust;

    int rc = mp[i]->device->fs->read(filename, buffer, mp[i]->device, mp[i]->device->fs->priv_data);
    return (rc);
}

uint32_t 
vfs_ls(char *dir, char *buffer) 
{
    char *orig = (char *)malloc(strlen(dir) + 1);
    memset(orig, 0, strlen(dir) + 1);
    memcpy(orig, dir, strlen(dir) + 1);
    while (1) 
    {
        for (int i = 0; i < MAX_MOUNTS; i++) 
        {
            if (!mp[i]) break;
            if (strcmp(mp[i]->loc, orig) == 0) 
            {
                mp[i]->device->fs->read_dir(dir + strlen(mp[i]->device->fs->priv_data) - 1, buffer, mp[i]->device, mp[i]->device->fs->priv_data);
                for (int k = 0; k < MAX_MOUNTS; k++) 
                {
                    if (!mp[k]) 
                        break;
                    char *mount = (char *)malloc(strlen(mp[k]->loc) + 1);
                    str_backspace(mount, '/');
                    if (strcmp(mount, dir) == 0) 
                    {
                        char *p = mp[k]->loc + strlen(dir);
                        if ((strlen(p) == 0) || (strlen(p) == 1)) 
                            continue;
                        terminal_printf("%s\n", p);
                    }
                    free(mount);
                }
                break;
            }
        }
        if (strcmp(orig, "/") == 0) 
            break;
        str_backspace(orig, '/');
    }
    free(orig);
    return (1);
}

uint8_t 
vfs_exists_in_dir(char *wd, char *fn) 
{
    char *filename = (char *)malloc(strlen(wd) + 2 + strlen(fn));
    memset(filename, 0, strlen(wd) + 2 + strlen(fn));
    memcpy(filename, wd, strlen(wd));
    memcpy(filename + strlen(wd), fn, strlen(fn));
    memset(filename + strlen(wd) + strlen(fn) + 1, '\0', 1);

    if (filename[strlen(filename)] != '/') 
    {
        uint32_t index = strlen(filename);
        filename[index] = '/';
        filename[index + 1] = 0;
    }
    int rc = 0;
    char *o = (char *)malloc(strlen(filename) + 2);
    memset(o, 0, strlen(filename) + 2);
    memcpy(o, filename, strlen(filename) + 1);

    while (1) 
    {
        for (int i = 0; i < MAX_MOUNTS; i++) 
        {
            if (!mp[i]) 
                break;

            if (strcmp(o, mp[i]->loc) == 0) 
            {
                filename += strlen(mp[i]->loc) - 1;
                rc = mp[i]->device->fs->exists(filename, mp[i]->device, mp[i]->device->fs->priv_data);
                free(o);
                free(filename);
                return (rc);
            }
        }
        if (strcmp(o, "/" == 0))
            break;
        str_backspace(o, '/');
    }
    free(o);
    free(filename);
    return (rc);
}

void vfs_init(void) 
{
    INFO("Loading up Virtual Filesystem...\n");
    mp = (mount_info_t **)malloc(sizeof(uint32_t) * MAX_MOUNTS);
    __init_vfs = 1;
}
