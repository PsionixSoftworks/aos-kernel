#ifndef _CONST_H
#define _CONST_H

#define V1_NR_DZONES            7
#define V1_NR_TZONES            9
#define V2_NR_DZONES            7
#define V2_NR_TZONES            10

#define NR_FLIPS                128
#define NR_INODES               64
#define NR_SUPERS               8
#define NR_LOCKS                8

#define usizeof(t)              ((unsigned)sizeof(t))

#define SUPER_MAGIC             0x137F
#define SUPER_REV               0x7F13
#define SUPER_V2                0x2468
#define SUPER_V2_REV            0x6824
#define SUPER_V3                0x4D5A

#define V1                      1
#define V2                      2
#define V3                      3

#define SU_UID                  ((uid_t)0)
#define SYS_UID                 ((uid_t)0)
#define SYS_GID                 ((gid_t)0)
#define NORMAL                  0
#define NO_READ                 1
#define PREFETCH                2

#define XPIPE                   (-NR_TASKS - 1)

#define DIR_ENTRY_SIZE          usizeof(struct dirent)
#define NR_DIR_ENTRIES(b)       ((b) / DIR_ENTRY_SIZE)

#define V1_ZONE_NUM_SIZE        usizeof(zone1_t)

#define V1_INDIRECTS            (STATIC_BLOCK_SIZE / V1_ZONE_NUM_SIZE)

#endif
