#ifndef _AOS_KERNEL_
#define _AOS_KERNEL_

// Handle other includes here:
#include "types.h"
#include "init.h"

#if KERNEL32

#define KERNEL_MODE_NORMAL		0x10
#define KERNEL_MODE_SAFE		0x20
#define KERNEL_MODE_NO_GUI		0x30

#if defined(__cplusplus)
extern "C" {
#endif

typedef void(*kfunc_t)(uint8_t);

// Declare the global functions used by the kernel:
extern void kernel_init(uint8_t mode);					// The kernel's init function for startup.
extern void kernel_update(void);				// The kernel's update function to run the os in a constant loop.
extern void kernel_quit(uint8_t status);					// Shuts down the kernel when execution stops.
extern bool kernel_is_running(void);			// Checks to see if the kernel is running.
extern void free_system_resources(uint8_t);
extern void kernel_begin_mode(kfunc_t init_func, uint8_t mode);

static __initcall void kernel_current_run_mode_start(uint8_t mode)
{
	switch (mode)
	{
		case KERNEL_MODE_NORMAL:
			kernel_begin_mode(kernel_init, KERNEL_MODE_NORMAL);
			break;
		case KERNEL_MODE_SAFE:
			kernel_begin_mode(kernel_init, KERNEL_MODE_SAFE);
			break;
		case KERNEL_MODE_NO_GUI:
			kernel_begin_mode(kernel_init, KERNEL_MODE_NO_GUI);
			break;
		default:
			kernel_begin_mode(kernel_init, KERNEL_MODE_NORMAL);
			break;
	}
}

// Define the kernel struct, it will control every aspect of the kernel:
typedef struct 
{
	bool running;										// This needs to be set to true in order to keep the kernel_update function running.
	uint8_t exit_status;
} kernel_t;			// Define the kernel type.

#if defined(__cplusplus)
}
#endif

#endif	// !KERNEL32
#endif	// !ADAMANTINE_KERNEL
