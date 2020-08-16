#ifndef _COMMAND_
#define _COMMAND_

#include "../types.h"
#include "../string.h"

#if defined(__cplusplus)
extern "C" {
#endif

struct command_line 
{
    string *cmd_list;
};
typedef struct command_line command_t;

extern void command_line_init(void);
extern void parse_command(string cmd);

#if defined(__cplusplus)
}
#endif

#endif
