#define CENTRIX_MODE1
#define KERNEL32    1

#include "../include/centrix-core.h"
#include "../include/centrix.h"
#include "../include/aos-defs.h"
#include "../include/terminal.h"
#include "../include/cpu.h"
#include "../include/vga.h"

MODULE("centrix", "0.01a");

string supported_oses[] =
{
    "CentrixOS",
    "AdamantineOS",
    "SteelOS",
};

struct centrix_core core;
void *KernelInstall(string name) {
    core.os_id = NULL;
    core.os_signature = NULL;

    core.os_name = name;
    return (name);
}

int32_t 
Verify(void)
{
    terminal_init(SYSTEM_COLOR_BLACK, SYSTEM_COLOR_GRAY);
	terminal_clear_screen();

    size_t len = strlen(supported_oses);
    size_t i = 0;
    string os_name = core.os_name;
    while (i < len)
    {
        if (strcmp(os_name, supported_oses[i]) == 0)
        {
            terminal_printf("[CENTRIX]: \"%s\" is a valid Operating System.\n", os_name);
            terminal_printf("[CENTRIX]: Starting \"%s\" OS kernel...\n\n", os_name);
            return (SUCCESS);
        } else {
            i++;
            if (i >= len) 
            {
                terminal_printf("[CENTRIX]: \"%s\" is not a valid Operating System...\n", os_name);
                return (FAILURE);
            }
        }
    }
}
