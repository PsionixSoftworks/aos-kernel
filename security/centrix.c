/*
 *  File: centrix.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#define CENTRIX_MODE1

#include <centrix/centrix-core.h>
#include <centrix/centrix.h>
#include <kernel/system/terminal.h>
#include <kernel/cpu.h>
#include <kernel/drivers/vga.h>

MODULE("Centrix", "0.01a");

string supported_os[] =
{
    "CentrixOS",
    "AdamantineOS",
    "SteelOS",
};

struct centrix_core core;
void *
kernel_install(string name) {
    core.os_id = NULL;
    core.os_signature = NULL;

    core.os_name = name;
    return (name);
}

dword 
kernel_verify(void)
{
    /*
    terminal_init();
	terminal_clear();

    size_t length = strlen(supported_os);
    size_t i = 0;
    string os_name = core.os_name;
    while (i < length)
    {
        if (strcmp(os_name, supported_os[i]) == 0)
        {
            terminal_printf("[CENTRIX]: \"%s\" is a valid Operating System.\n", os_name);
            terminal_printf("[CENTRIX]: Starting \"%s\" OS kernel...\n\n", os_name);
            return (SUCCESS);
        } else {
            i++;
            if (i >= length) 
            {
                terminal_printf("[CENTRIX]: \"%s\" is not a valid Operating System...\n", os_name);
                return (FAILURE);
            }
        }
    }
    */

   return (0);
}
