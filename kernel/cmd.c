#define KERNEL32	1

#include "../include/cmd/cmd.h"
#include "../include/terminal.h"
#include "../include/aos-defs.h"

MODULE("command", "0.01a");

command_t command;

void 
command_line_init(void) 
{
    command.cmd_list[0] = "test";
}

uint8_t 
__parse_command(string cmd) 
{
    for (int i = 0; i < sizeof(uint8_t); i++) 
    {
        if (cmd == command.cmd_list[i]) 
        {
            return (1);
        }
    }
    return (0);
}

void parse_command(string cmd) 
{
    if (!__parse_command(cmd)) 
    {
        terminal_printf("Unrecognized command: \"%s\"\n", cmd);
    } 
    else 
    {
        terminal_printf("Command \"%s\" exists!\n", cmd);
    }
}
