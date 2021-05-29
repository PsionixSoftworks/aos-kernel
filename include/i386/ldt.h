#ifndef _ADAMANTINE_LDT_H
#define _ADAMANTINE_LDT_H

#include <compiler.h>
#include <stdint.h>

struct ldt_entry_struct
{
    uint8_t                 table;
    uint8_t                 rpl;
} PACKED;
typedef struct ldt_entry_struct ldt_entry_t;

struct ldt_ptr_struct
{
    uint16_t                limit;
    uint32_t                base;
} PACKED;
typedef struct ldt_ptr_struct ldt_ptr_t;

extern void ldt_init(void);

#endif
