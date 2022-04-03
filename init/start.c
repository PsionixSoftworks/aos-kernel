#ifndef STARTUP_LOCATION
#define STARTUP_LOCATION 0x00000000
#endif

#define DEFAULT_USER    "aos_user"
#define DEFAULT_PASS    "pass541"

#include <kernel/kernel.h>
#include <drivers/tty.h>
#include <stdbool.h>

static inline void
startup_validate_credentials(char *uname, char *pword)
{
    // First off, get general username & password. The default is aos_user and pass541:
    bool uname_valid = (uname == DEFAULT_USER);
    bool pword_valid = (pword == DEFAULT_PASS);

    if (!uname_valid)
        goto err_uname;
    if (!pword_valid)
        goto err_pword;
    else
        goto parse_user;
    
    err_uname:
        k_tty_set_foreground(SYSTEM_COLOR_RED);
        k_tty_printf("[ERROR]: %s\n", "Invalid username! Please try again.");
        k_tty_set_foreground(SYSTEM_COLOR_LT_GREEN);
        return;
    
    err_pword:
        k_tty_set_foreground(SYSTEM_COLOR_RED);
        k_tty_printf("[ERROR]: %s\n", "Invalid password! Please try again.");
        k_tty_set_foreground(SYSTEM_COLOR_LT_GREEN);
        return;
    
    parse_user:
        k_tty_printf("[USER]: Logged in. Privelage level=3...");
        return;
}

