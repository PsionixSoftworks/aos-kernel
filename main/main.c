#include "../include/main.h"
#include "../include/kernel.h"
#include "../include/aos-defs.h"
#include "../include/terminal.h"

MODULE("main", "0.01a");

void _TEXT 
kmain(void) 
{
	KernelInstall(OS_NAME);
	uint32_t status = Verify();
	if (status == SUCCESS)
	{
		kernel_init(0);
		while (kernel_is_running())
		{
			kernel_update();
		}
		kernel_quit(0x0);
	} else {
		ERROR("Unable to start. Invalid OS...");
		kernel_quit(0x1);
	}
}
