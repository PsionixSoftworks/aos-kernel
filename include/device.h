#ifndef _DEVICE_
#define _DEVICE_

#include "driver.h"
#include "aos-defs.h"
#include "types.h"
#include "string.h"

#if defined(__cplusplus)
extern "C" {
#endif

struct aos_fs;

typedef struct aos_device 
{
    uint32_t device_id;
    uint8_t device_status;
    string device_name;
    struct aos_fs *fs;
    uint8_t (*read)(uint8_t *buffer, uint32_t offset, uint32_t len, void * device);
    uint8_t (*write)(uint8_t *buffer, uint32_t offset, uint32_t len, void * device);

} device_t;

enum device_type {
    DEVICE_UNKNOWN,
    DEVICE_CHAR,
    DEVICE_BLOCK,
};

extern void aos_device_init(uint32_t, string);
extern int aos_device_add(struct aos_device *);
extern struct aos_device aos_device_get(uint32_t);
extern void aos_device_free(void);

#if defined(__cplusplus)
}
#endif
#endif
