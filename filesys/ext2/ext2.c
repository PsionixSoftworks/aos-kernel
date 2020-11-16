/*
 *  File: ext2.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include <filesys/ext2.h>
#include <filesys/vfs.h>
#include <kernel/system/terminal.h>
#include <kernel/memory/mm.h>
#include <adamantine/aos-string.h>

/*
#define SIZE_OF_SINGLY (priv->blocksize * priv->blocksize / 4)

static inode_t *inode = 0;
static uint8_t *root_buf = 0;
static uint8_t *block_buf = 0;
static inode_t *minode = 0;

void 
ext2_read_block(uint8_t *buf, uint32_t block, device_t *device, ext2_priv_data *priv),
ext2_write_block(uint8_t *buf, uint32_t block, device_t *device, ext2_priv_data *priv),
ext2_read_inode(inode_t *inode_buf, uint32_t inode, device_t *device, ext2_priv_data *priv),
ext2_write_inode(inode_t *inode_buf, uint32_t ii, device_t *device, ext2_priv_data *priv),
ext2_list_directory(char *dd, char *buffer, device_t *device, ext2_priv_data *priv),
ext2_find_new_inode(uint32_t *id, device_t *device, ext2_priv_data *priv),
ext2_alloc_block(uint32_t *out, device_t *device, ext2_priv_data *priv);

uint8_t ext2_read_root_directory(char *filename, device_t *device, ext2_priv_data *priv),
ext2_find_file_inode(char *ff, inode_t *inode_buf, device_t *device, ext2_priv_data *priv),
ext2_read_singly_linked(uint32_t block_id, uint8_t *buf, device_t *device, ext2_priv_data *priv),
ext2_read_doubly_linked(uint32_t block_id, uint8_t *buf, device_t *device, ext2_priv_data *priv),
ext2_read_file(char *fn, uint8_t buffer, device_t *device, ext2_priv_data *priv),
ext2_touch(char *file, device_t *device __attribute__((unused)), ext2_priv_data *priv __attribute__((unused))),
ext2_writefile(char *fn, char *buf, uint32_t len, device_t *device, ext2_priv_data *priv),
ext2_exist(char *file, device_t *device, ext2_priv_data *priv);

uint32_t 
ext2_get_inode_block(uint32_t inode, uint32_t *b, uint32_t *ioff, device_t *device, ext2_priv_data *priv),
ext2_read_directory(char *filename, ext2_dir *dir, device_t *device, ext2_priv_data *priv);

uint8_t 
ext2_probe(device_t *device) 
{
    terminal_printf("Probing device %d\n", device->device_id);
    if (!device->read) 
    {
        terminal_print("device has no read, skipping.\n");
        return (0);
    }
    uint8_t *buf = (uint8_t *)malloc(1024);
    device->read(buf, 2, 2, device);
    superblock_t *sb = (superblock_t *)buf;
    if (sb->ext2_sig != EXT2_SIGNATURE) 
    {
        terminal_printf("Invalid EXT2 signature, have %x\n", sb->ext2_sig);
        return (0);
    }
    terminal_print("valid EXT2 signature!\n");
    filesystem_t *fs = (filesystem_t *)malloc(sizeof(filesystem_t));
    ext2_priv_data *priv = (ext2_priv_data *)malloc(sizeof(ext2_priv_data));
    memcpy(&priv->sb, sb, sizeof(superblock_t));
    uint32_t blocksize = 1024 << sb->blocksize_hint;
    terminal_printf("size of a block: %d bytes.\n", blocksize);
    priv->blocksize = blocksize;
    priv->inodes_per_block = blocksize / sizeof(inode_t);
    priv->sectors_per_block = blocksize / 512;
    terminal_printf("size of volume: %d bytes.\n", blocksize * (sb->blocks));
    uint32_t number_of_bgs0 = sb->blocks / sb->blocks_in_blockgroup;
    if (!number_of_bgs0) number_of_bgs0 = 1;
    terminal_printf("There are %d block groups.\n", number_of_bgs0);
    priv->number_of_bgs = number_of_bgs0;

    uint32_t block_bgdt = sb->superblock_id + (sizeof(superblock_t) / blocksize);
    priv->first_bgd = block_bgdt;
    fs->name = "EXT2";
    fs->probe = (uint8_t(*)(device_t *))ext2_probe;
    fs->mount = (uint8_t(*)(device_t *, void *))ext2_mount;
    fs->read = (uint8_t(*)(char *, char *, device_t *, void *))ext2_read_file;
    fs->exists = (uint8_t(*)(char *, device_t *, void *))ext2_exist;
    fs->read_dir = (uint8_t(*)(char *, char *, device_t *, void *))ext2_list_directory;
    fs->touch = (uint8_t(*)(char *, device_t *, void *))ext2_touch;
    fs->write_file = (uint8_t(*)(char *, char *m, uint32_t, device_t *, void *))ext2_writefile;
    fs->priv_data = (void *)priv;
    device->fs = fs;
    terminal_printf("device %s (%d) is with EXT2 filesystem. Probe successful.\n", device->device_name, device->device_id);
    free(buf);

    return (1);
}

uint8_t 
ext2_mount(device_t *device, void *privd) 
{
    terminal_printf("Mounting ext2 on device %s (%d).\n", device->device_name, device->device_id);
    ext2_priv_data *priv = privd;
    if (ext2_read_root_directory((char *)1, device, priv))
        return (1);
    return (0);
}

void 
ext2_read_block(uint8_t *buf, uint32_t block, device_t *device, ext2_priv_data *priv) 
{
    uint32_t sectors_per_block = priv->sectors_per_block;
    if (!sectors_per_block) sectors_per_block = 1;

    device->read(buf, block * sectors_per_block, sectors_per_block, device);
}

void 
ext2_write_block(uint8_t *buf, uint32_t block, device_t *device, ext2_priv_data *priv) 
{
    uint32_t sectors_per_block = priv->sectors_per_block;
    if (!sectors_per_block) sectors_per_block = 1;

    device->write(buf, block * sectors_per_block, sectors_per_block, device);
}

void 
ext2_read_inode(inode_t *inode_buf, uint32_t inode, device_t *device, ext2_priv_data *priv) 
{
    uint32_t bg = (inode - 1) / priv->sb.inodes_in_blockgroup;
    uint32_t i = 0;

    if (!block_buf) 
        block_buf = (uint8_t *)malloc(priv->blocksize);
    ext2_read_block(block_buf, priv->first_bgd, device, priv);
    block_group_desc_t *bgd = (block_group_desc_t *)block_buf;
    terminal_printf("We seek BG %d.\n", bg);

    for (i = 0; i < bg; i++)
        bgd++;
    uint32_t index = (inode - 1) % priv->sb.inodes_in_blockgroup;
    terminal_printf("Index of inode is %d.\n", index);
    uint32_t block = (index * sizeof(inode_t)) / priv->blocksize;
    terminal_printf("Relative: %d, Absolute: %d.\n", block, bgd->block_of_inode_table + block);
    ext2_read_block(block_buf, bgd->block_of_inode_table + block, device, priv);
    inode_t *_inode = (inode_t *)block_buf;
    index = index % priv->inodes_per_block;
    for (i = 0; i < index; i++)
        _inode++;
    memcpy(inode_buf, _inode, sizeof(inode_t));
}

void 
ext2_write_inode(inode_t *inode_buf, uint32_t ii, device_t *device, ext2_priv_data *priv) 
{
    uint32_t bg = (ii - 1) / priv->sb.inodes_in_blockgroup;
    uint32_t i = 0;

    if (!block_buf) block_buf = (uint8_t *)malloc(priv->blocksize);
    ext2_read_block(block_buf, priv->first_bgd, device, priv);
    block_group_desc_t *bgd = (block_group_desc_t *)block_buf;
    terminal_printf("We seek BG %d.\n", bg);
    for (i = 0; i < bg; i++)
        bgd++;
    uint32_t index = (ii - 1) % priv->sb.inodes_in_blockgroup;
    terminal_printf("Index of inode is %d.\n", index);
    uint32_t block = (index * sizeof(inode_t)) / priv->blocksize;
    terminal_printf("Relative: %d, Absolute: %d.\n", block, bgd->block_of_inode_table + block);
    uint32_t final = bgd->block_of_inode_table + block;
    ext2_read_block(block_buf, final, device, priv);
    inode_t *_inode = (inode_t *)block_buf;
    index = index % priv->inodes_per_block;
    for (i = 0; i < index; i++) {
        _inode++;
    }
    memcpy(_inode, inode_buf, sizeof(inode_t));
    ext2_write_block(block_buf, final, device, priv);
}

uint32_t 
ext2_get_inode_block(uint32_t inode, uint32_t *b, uint32_t *ioff, device_t *device, ext2_priv_data * priv) 
{
    uint32_t bg = (inode - 1) / priv->sb.inodes_in_blockgroup;
    uint32_t i = 0;

    if (!block_buf) 
        block_buf = (uint8_t *)malloc(priv->blocksize);
    ext2_read_block(block_buf, priv->first_bgd, device, priv);
    block_group_desc_t *bgd = (block_group_desc_t *)block_buf;
    terminal_printf("We seek BG %d.\n", bg);

    for (i = 0; i < bg; i++)
        bgd++;
    uint32_t index = (inode - 1) % priv->sb.inodes_in_blockgroup;
    uint32_t block = (index * sizeof(inode_t)) / priv->blocksize;
    index = index % priv->inodes_per_block;
    *b = block + bgd->block_of_inode_table;
    *ioff = index;

    return (1);
}

uint32_t 
ext2_read_directory(char *filename, ext2_dir *dir, device_t *device, ext2_priv_data *priv) 
{
    while (dir->inode != 0) 
    {
        char *name = (char *)malloc(dir->namelength + 1);
        memcpy(name, &dir->reserved + 1, dir->namelength);
        name[dir->namelength] = 0;

        if ((filename) && (strcmp(filename, name) == 0)) 
        {
            ext2_read_inode(inode, dir->inode, device, priv);
            terminal_printf("Found inode %s! %d\n", filename, dir->inode);
            free(name);
            return (dir->inode);
        }
        if ((!filename) && ((uint32_t)filename != 1)) 
        {
            terminal_printf("%s\n", name);
        }
        dir = (ext2_dir *)((uint32_t)dir + dir->size);
        free(name);
    }
    return (0);
}

uint8_t 
ext2_read_root_directory(char *filename, device_t *device, ext2_priv_data *priv) 
{
    if (!inode) 
        inode = (inode_t *)malloc(sizeof(inode_t));
    if (!root_buf) 
        root_buf = (uint8_t *)malloc(priv->blocksize);
    ext2_read_inode(inode, 2, device, priv);
    if ((inode->type & 0xF000) != INODE_TYPE_DIRECTORY) 
    {
        ERROR("Fatal: Root directory is not a directory...\n");
        return (0);
    }

    for (uint32_t i = 0; i < 12; i++) 
    {
        uint32_t b = inode->dbp[i];
        if (b == 0) break;
        ext2_read_block(root_buf, b, device, priv);

        if (ext2_read_directory(filename, (ext2_dir *)root_buf, device, priv)) 
            return (1);
    }
    if (filename && (uint32_t)filename != 1) 
        return (0);
    return (1);
}

uint8_t 
ext2_find_file_inode(char *ff, inode_t *inode_buf, device_t *device, ext2_priv_data *priv) 
{
    char *filename = malloc(strlen(ff) + 1);
    memcpy(filename, ff, strlen(ff) + 1);
    size_t n = strsplit(filename, '/');
    filename++;
    uint32_t retnode = 0;
    if (n > 1) 
    {
        ext2_read_inode(inode, 2, device, priv);
        n--;
        while (n--) 
        {
            terminal_printf("Looking for %s.\n", filename);
            for (uint32_t i = 0; i < 12; i++) {
                uint32_t b = inode->dbp[i];
                if (!b) break;
                ext2_read_block(root_buf, b, device, priv);
                uint32_t rc = ext2_read_directory(filename, (ext2_dir *)root_buf, device, priv);
                if (!rc) 
                {
                    if (strcmp(filename, "") == 0) 
                    {
                        free(filename);
                        return (strcmp(ff, "/") ? retnode : 1);
                    }
                    terminal_printf("File (%s (%x)) not found!\n", filename, filename);
                    free(filename);
                    return (0);
                } 
                else 
                {
                    retnode = rc;
                    goto fix;
                }
            }
            fix:;
            uint32_t s = strlen(filename);
            filename += s + 1;
        }
        memcpy(inode_buf, inode, sizeof(inode_t));
    }
    free(filename);
    return (retnode);
}

void 
ext2_list_directory(char *dd, char *buffer, device_t *device, ext2_priv_data *priv) 
{
    char *dir = dd;
    uint32_t rc = ext2_find_file_inode(dir, (inode_t *)buffer, device, priv);
    if (!rc) return;
    for (uint32_t i = 0; i < 12; i++) 
    {
        uint32_t b = inode->dbp[i];
        if (!b) break;
        ext2_read_block(root_buf, b, device, priv);
        ext2_read_directory(0, (ext2_dir *)root_buf, device, priv);
    }
}

uint8_t 
ext2_read_singly_linked(uint32_t blockid, uint8_t *buf, device_t *device, ext2_priv_data *priv) 
{
    //uint32_t blockadded = 0;
    uint32_t maxblocks = ((priv->blocksize) / (sizeof(uint32_t)));

    ext2_read_block(root_buf, blockid, device, priv);
    uint32_t *block = (uint32_t *)root_buf;
    for (uint32_t i = 0; i < maxblocks; i++) 
    {
        if (block[i] == 0) break;
        ext2_read_block(buf + i * priv->blocksize, block[i], device, priv);
    }
    return (1);
}

uint8_t 
ext2_read_doubly_linked(uint32_t blockid, uint8_t *buf, device_t *device, ext2_priv_data *priv) 
{
    //uint32_t blockadded = 0;
    uint32_t maxblocks = ((priv->blocksize) / (sizeof(uint32_t)));

    ext2_read_block(block_buf, blockid, device, priv);

    uint32_t *block = (uint32_t *)block_buf;
    uint32_t s = SIZE_OF_SINGLY;
    for (uint32_t i = 0; i < maxblocks; i++) 
    {
        if (block[i] == 0) break;
        ext2_read_singly_linked(block[i], buf + 1 * s, device, priv);
    }
    return (1);
}

uint8_t 
ext2_read_file(char *fn, uint8_t buffer, device_t *device, ext2_priv_data *priv) 
{
    if (!minode) minode = (inode_t *)malloc(sizeof(inode_t));
    char *filename = fn;
    if (!ext2_find_file_inode(filename, minode, device, priv)) 
    {
        terminal_print("File inode not found.\n");
        return (0);
    }

    for (uint32_t i = 0; i < 12; i++) 
    {
        uint32_t b = minode->dbp[i];
        if (b == 0) {
            terminal_print("End of file!\n"); 
            return (1);
        }
        if (b > priv->sb.blocks) 
            PANIC("%s: block %d outside range (max: %d)!\n", b, priv->sb.blocks);
        terminal_printf("Reading block: %d.\n", b);

        ext2_read_block(root_buf, b, device, priv);
        memcpy(buffer + 1 * (priv->blocksize), root_buf, priv->blocksize);
    }
    if (minode->singly_block) 
    {
        ext2_read_singly_linked(minode->singly_block, buffer + 12 * (priv->blocksize), device, priv);
    }
    if (minode->doubly_block) 
    {
        uint32_t s = SIZE_OF_SINGLY + 12 * priv->blocksize;
        ext2_read_doubly_linked(minode->doubly_block, buffer + s, device, priv);
    }
    return (1);
}

void 
ext2_find_new_inode_id(uint32_t *id, device_t *device, ext2_priv_data *priv) 
{
    ext2_read_block(root_buf, priv->first_bgd, device, priv);
    block_group_desc_t *bg = (block_group_desc_t *)root_buf;
    for (uint32_t i = 0; i < priv->number_of_bgs; i++) 
    {
        if (bg->num_of_unallocated_inode) 
        {
            *id = ((i + 1) * priv->sb.blocks_in_blockgroup) - bg->num_of_unallocated_inode + 1;
            bg->num_of_unallocated_inode--;
            ext2_write_block(root_buf, priv->first_bgd + i, device, priv);
            ext2_read_block(root_buf, priv->sb.superblock_id, device, priv);
            superblock_t *sb = (superblock_t *)root_buf;
            sb->unallocatedinodes--;
            return;
        }
        bg++;
    }
}

void 
ext2_alloc_block(uint32_t *out, device_t *device, ext2_priv_data *priv) 
{
    ext2_read_block(root_buf, priv->first_bgd, device, priv);
    block_group_desc_t *bg = (block_group_desc_t *)root_buf;
    for (uint32_t i = 0; i < priv->number_of_bgs; i++) 
    {
        if (bg->num_of_unallocated_block) 
        {
            *out = priv->sb.blocks - bg->num_of_unallocated_block + 1;
            bg->num_of_unallocated_block--;
            ext2_write_block(root_buf, priv->sb.superblock_id, device, priv);
            superblock_t *sb = (superblock_t *)root_buf;
            sb->unallocatedblocks--;
            ext2_write_block(root_buf, priv->sb.superblock_id, device, priv);
            return;
        }
        bg++;
    }
}

uint8_t 
ext2_touch(char *file, device_t *device __attribute__((unused)), ext2_priv_data *priv __attribute__((unused))) 
{
    if (!device->write)
        return (0);
    
    char *fil = (char *)malloc(strlen(file) + 1);
    memcpy(fil, file, strlen(file) + 1);
    inode_t *fi = (inode_t *)malloc(sizeof(inode_t));
    fi->hardlinks = 1;
    fi->size = 0;
    fi->type = INODE_TYPE_FILE;
    fi->disk_sectors = 2;

    size_t n = strsplit(fil, '/');
    n--;
    while (n) 
    {
        fil += strlen(fil) + 1;
        n--;
    }

    ext2_dir *entry = (ext2_dir *)malloc(sizeof(ext2_dir) + strlen(fil) + 1);
    entry->size = sizeof(ext2_dir) + strlen(fil) + 1;
    entry->namelength = strlen(fil) + 1;
    entry->reserved = 0;
    memcpy(&entry->reserved + 1, fil, strlen(fil) + 1);

    uint32_t id = 0;
    entry->inode = id;

    uint32_t block = 0;
    uint32_t ioff = 0;ext2_get_inode_block(id, &block, &ioff, device, priv);
    inode_t *winode = (inode_t *)root_buf;
    for (uint32_t i = 0; i < ioff; i++)
        winode++;
    memcpy(winode, fi, sizeof(inode_t));
    ext2_write_block(root_buf, block, device, priv);

    char *f = (char *)malloc(strlen(file) + 1);
    memcpy(f, file, strlen(file) + 1);
    str_backspace(f, '/');

    if (!inode) 
        inode = (inode_t *)malloc(sizeof(inode_t));
    if (!block_buf) 
        block_buf = (uint8_t *)malloc(priv->blocksize);
    uint32_t t = ext2_find_file_inode(f, inode, device, priv);
    t++;

    uint8_t found = 0;
    for (uint32_t i = 0; i < 12; i++) 
    {
        if (inode->dbp[i] == 0) 
        {
            uint32_t theblock = 0;
            ext2_alloc_block(&theblock, device, priv);
            inode->dbp[i] = theblock;
            ext2_write_inode(inode, t, device, priv);
        }
        ext2_read_block(block_buf, inode->dbp[i], device, priv);

        ext2_dir *d = (ext2_dir *)block_buf;
        uint32_t passed = 0;
        while (d->inode != 0) 
        {
            if (d->size == 0) 
                break;
            uint32_t truesize = d->namelength + 8;
            truesize += 4 - truesize % 4;
            uint32_t origsize = d->size;

            if (truesize != d->size) 
            {
                d->size = truesize;
                passed += d->size;
                d = (ext2_dir *)((uint32_t)d + d->size);
                entry->size = priv->blocksize - passed;
                break;
            }
            passed += d->size;
            d = (ext2_dir *)((uint32_t)d + d->size);
        }
        if (passed >= priv->blocksize) {
            continue;
        }
        dir_write:
            memcpy(d, entry, entry->size);
            ext2_write_block(block_buf, inode->dbp[i], device, priv);
            return (1);
    }
    return (0);
}

uint8_t 
ext2_writefile(char *fn, char *buf, uint32_t len, device_t *device, ext2_priv_data * priv) 
{
    uint32_t inode_id = ext2_find_file_inode(fn, inode, device, priv);
    inode_id++;
    if (inode_id == 1) return 0;
    terminal_printf("%s's inode is %d.\n", fn, inode_id);
    if (!inode) inode = (inode_t *)malloc(sizeof(inode_t));
    ext2_read_inode(inode, inode_id, device, priv);

    if (inode->size == 0) 
    {
        uint32_t blocks_to_alloc = len / priv->blocksize;
        blocks_to_alloc++;
        if (blocks_to_alloc > 12) 
        {
            terminal_print("Unable to write to files larger than 12KB???\n");
            return (0);
        }

        for (uint32_t i = 0; i < blocks_to_alloc; i++) 
        {
            uint32_t bid = 0;
            ext2_alloc_block(&bid, device, priv);
            inode->dbp[i] = bid;
        }
        terminal_printf("Allocated %d blocks!\n", blocks_to_alloc);
        inode->size += len;

        ext2_write_inode(inode, inode_id - 1, device, priv);

        for (uint32_t i = 0; i < blocks_to_alloc; i++) 
        {
            ext2_read_block(root_buf, inode->dbp[i], device, priv);
            if (i + 1 < blocks_to_alloc) 
            {
                memcpy(root_buf, buf + i *priv->blocksize, priv->blocksize);
            } 
            else 
            {
                terminal_printf("Last block write %d => %d!\n", i, inode->dbp[i]);
                memcpy(root_buf, buf + i * priv->blocksize, len);
            }
            ext2_write_block(root_buf, inode->dbp[i], device, priv);
        }
        terminal_print("Wrote data to fresh blocks!\n");
        return (1);
    }
    uint32_t last_data_block = inode->size / priv->blocksize;
    uint32_t last_data_offset = (inode->size) % priv->blocksize;

    ext2_read_block(root_buf, last_data_block, device, priv);

    if (len < priv->blocksize - last_data_offset) 
    {
        memcpy(root_buf + last_data_offset, buf, priv);
        ext2_write_block(root_buf, last_data_block, device, priv);
        return (1);
    }
    return (0);
}

uint8_t ext2_exist(char *file, device_t *device, ext2_priv_data *priv) 
{
    return (ext2_read_file(file, 0, device, priv));
}
*/
