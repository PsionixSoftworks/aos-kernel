#ifndef CENTRIX_CORE
#define CENTRIX_CORE

#if defined(__cplusplus)
extern "C" {
#endif

#include "types.h"
#include "string.h"
#include "aos-defs.h"

#if !defined(CENTRIX_MODE1) || !defined(CENTRIX_ALPHA)
/* We'll just ignore it for now. */
#else
#include "centrix/centrix_unit.h"
#include "centrix/base32.h"

struct _BASE32;



#endif

#if defined(DEBUG_MODE)
#include "centrix/debug.h"
#pragma pack(2)
#endif

#define KERNEL_INSTALL(name)        KernelInstall(name);

struct centrix_core 
{
    uint32_t os_id;
    uint32_t os_signature;
    string os_name;
};

void *KernelInstall(string name);
int32_t Verify(void);

#if defined(__cplusplus)
}
#endif

#endif	// !CENTRIX_CORE
