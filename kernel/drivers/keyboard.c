#include <kernel/drivers/keyboard.h>
#include <kernel/drivers/keys.h>
#include <kernel/system/ioctrl.h>
#include <adamantine/tty.h>
#include <kernel/drivers/vga.h>
#include <kernel/isr.h>
#include <kernel/pic.h>
#include <compiler.h>

#include <string.h>
#include <stdlib.h>
#include <stddef.h>

/* Define for normal keys */
const char keys_normal[256] = 
{
	0x00, 0x00,				                                            // <None>, <Escape>,
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',					// 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,
	'-', '=', '\b', '\t',												// -, =, <Backspace>, <Tab>,
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	// Q, W, E, R, T, Y, U, I, O, P, [, ], <Enter>,
	0x00,  										                        // <Control>,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',				// A, S, D, F, G, H, J, K, L, ;, ',
	'`', 0x00, '\\',    						                        // `, <Left Shift>, \,
	'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0x00,				// Z, X, C, V, B, N, m, ',', ., /, <Right Shift>, <Alt>
	'*', 0x00, ' ', 0x00,											    // *, <Alt>, <Space Bar>, <Caps Lock>,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,			// F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,
	0x00, 																// <Numlock (On?)>,
	0x00,																// <Scroll Lock>,
	'7', '8', '9',	    												// Numpad 7, Numpad 8, Numpad 9
	'-', 																// Numpad -,
    '4', '5', '6',  													// Numpad 4, Numpad 5, Numpad 6,
	'+',																// Numpad +,
	'1', '2', '3',  													// Numpad 1, Numpad 2, Numpad 3,
	'0', 0x00, 															// Numpad 0, Numpad Del,
	0x00, 0x00,	0x00,													// <NONE>, <NONE>, "<NONE>"
	0x00, 0x00,															// <Windows key>, <Windows key>,
};

// Define for keys when shift is held:
const char keys_caps[256] = 
{
	0x00, 0x00, 														// <None>, <Escape>,
	'!', '@', '#', '$', '%', '^', '&', '*', '(', ')',					// 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,
	'_', '+', '\b', '\t',												// -, =, <Backspace>, <Tab>,
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	// Q, W, E, R, T, Y, U, I, O, P, [, ], <Enter>,
	0x00,																// <Control>,
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"',				// A, S, D, F, G, H, J, K, L, ;, ',
	'~', 0x00, '|',														// `, <Left Shift>, \,
	'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0x00,				// Z, X, C, V, B, N, m, ',', ., /, <Right Shift>, <Alt>
	'*', 0x00, ' ', 0x00,												// *, <Alt>, <Space Bar>, <Caps Lock>,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,			// F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,
	0x00, 																// <Numlock (On?)>,
	0x00,																// <Scroll Lock>,
	'7', '8', '9',														// Numpad 7, Numpad 8, Numpad 9
	'-', 																// Numpad -,
	'4', '5', '6',														// Numpad 4, Numpad 5, Numpad 6,
	'+',																// Numpad +,
	'1', '2', '3',														// Numpad 1, Numpad 2, Numpad 3,
	'0', '.',															// Numpad 0, Numpad Del,
	0x00, 0x00, 0x00,															// <NONE>, <NONE>, "<NONE>"
	0x00, 0x00,													// <Windows key>, <Windows key>,
};

static inline void keyboard_handler(void);              // The keyboard callback (tied to IRQ1)
static inline uint8_t keyboard_read(void);              // Read keyboard command
static inline void keyboard_write_command(uint8_t);     // Write keyboard command
static inline char *keyboard_get_key(void);             // Get the keyboard key
static inline void keyboard_set_leds(bool, bool, bool); // Set the keyboard LED's (numlock, caps lock, and scroll lock)
static inline char *keyboard_get_keylast(void);         // Get the last key pressed

static bool init = false;                               // Whether the keyboard is initialized
static bool shift_press = false;                        // True if the shift key is being held
static bool ctrl_press = false;                         // True if the control key is being held
static bool system_press = false;                       // True if the "windows"/"command" key is being held
static bool alt_press = false;                          // True if the alt key is being held
static bool numlock;                                    // True if numlock is enabled
static bool capslock;                                   // True if caps lock is enabled
static bool scrllock;                                   // True if scroll lock is enabled
static char *key_last = NULL;                           // The last key pressed
static char key_buffer[256];                            // The key buffer (for command line functionality)

/* Initialize the keyboard */
void
keyboard_init(void)
{
    if (!init)                                          // Check if the keyboard is initialized
    {
        memset(key_buffer, 0, sizeof(char) * 40);
        register_interrupt_handler(                     // Register the keyboard callback  with IRQ1
            IRQ1, 
            (isr_t)&keyboard_handler
        );

        tty_puts("[INFO]: Keyboard is initialized!\n"); // Print the status
        tty_puts("[ADAMANTINE]: ");                     // Print the command line "thing"
        
        init = true;                                    // Report that the keyboard is initialized
    }
}

/* Define the function that reads scancodes */
unsigned char
keyboard_read_scancode(void)
{
    uint8_t status = keyboard_read();                   // Read the command bit
    if ((status & 0x01) == 1)                           // If status is 1,
        return (inb(KEYBOARD_DATA));                    // return the scancode,
    return 0;                                           // otherwise, return 0 (failure)
}

/* Temporary storage for commands */
const char *cmd_list[] =
{
    "adm",                                              // Main command for interacting with the terminal and files
    "push",                                             // Push data onto the command line stack
    "pop",                                              // Pop data off the command line stack
    "ccmd",                                             // Create command
    "decl",                                             // Declare varible=value
    "pout",                                             // Print Out, DEBUG ONLY!
    "clear",                                            // Clear the terminal
    "fg1",                                              // Set the foreground color to 1 (blue)
    "fg2",                                              // Set the foreground color to 2 (green)
    "fg3",                                              // Set the foreground color to 3 (cyan)
    "fg4",                                              // Set the foreground color to 4 (red)
    "fg5",                                              // Set the foreground color to 5 (magenta)
    "fg6",                                              // Set the foreground color to 6 (brown (or orange, unless I'm color blind!))
    "fg7",                                              // Set the foreground color to 7 (gray)
    "fg8",                                              // Set the foreground color to 8 (dark gray)
    "fg9",                                              // Set the foreground color to 9 (light blue)
};

/* Process the commands as tokens */
static inline bool
process_commands(char *cmd)
{
    for (size_t i = 0; i < 16; i++)                     // Cycle through all of the commands in the array
    {
        if (strcmp(cmd, cmd_list[i]) == 0)              // Check if the command(s) match
        {
            return true;
        }
    }
    return false;
}

static uint8_t save_color = SYSTEM_COLOR_LT_GREEN;

/* Print out a debug message (for testing purposes only) */
static inline void
pout(void)
{
    tty_set_foreground(SYSTEM_COLOR_LT_CYAN);           // Change the text color to light cyan
    tty_printf("Print Out!\n");                         // Print the text
    tty_set_foreground(save_color);                     // Revert the text color back
}

/* Commit the changes to the text color */ 
static inline bool
change_fg(char *tok)
{
    for (size_t i = 7; i < 16; i++)                     // Cycle through the foreground colors
    {
        if (!strcmp(tok, cmd_list[i]))                  // Check if we have a match
        {
            return true;
        }
    }
    return (false);
}

/* Process user input */
static inline void
user_input(char *buffer)
{
    char *token = strtok(buffer, " ");                  // Break the input string into seperate tokens
    while (token != NULL)                               // Loop until we run out of tokens
    {
        /* Perform test functions here */
        if (strcmp(token, "test") == 0)
        {
            tty_printf("Recognized token: %s\n", token);
        }
        else
        {
            tty_printf("Output: %s\n", token);
        }
        /* Set the next tojen to 'NULL' */
        token = strtok(NULL, " ");
    }
}

/* Handle backspace (temporarily here) */
static inline void
backspace(char s[])
{
    int len = strlen(s);                                // Get the length of the string?
    s[len - 1] = '\0';                                  // Set the position -1 to null terminator (empty char)
}

/* Keyboard callback; where the magic happens (to be heavily modified...) */
static inline void
keyboard_handler(void)
{
    static unsigned char scancode;                      // Key scancode
    scancode = keyboard_read_scancode();                // Assign the scancode

    if (scancode)                                       // If it does not equal zero,
    {
        /* Check for Escape */
        if (scancode == KEYBOARD_KEY_DOWN_ESCAPE)
            tty_puts("Cannot exit from current mode!\n[ADAMANTINE]: ");
        if ((scancode == KEYBOARD_KEY_DOWN_WINDOWS_KEY_LEFT) || (scancode == KEYBOARD_KEY_DOWN_WINDOWS_KEY_RIGHT))
            tty_puts("[WindowsKey]: ");

        // Check for Left Shift:
        if ((scancode == KEYBOARD_KEY_DOWN_LEFT_SHIFT) || (scancode == KEYBOARD_KEY_DOWN_RIGHT_SHIFT))
            shift_press = true;
        else if ((scancode == KEYBOARD_KEY_UP_LEFT_SHIFT) || (scancode == KEYBOARD_KEY_UP_RIGHT_SHIFT))
            shift_press = false;

        // Check for Control Key:
        if ((scancode == KEYBOARD_KEY_DOWN_CONTROL))
            ctrl_press = true;
        else if (scancode == KEYBOARD_KEY_UP_CONTROL)
            ctrl_press = false;

        // Check for Alt Key:
        if (scancode == KEYBOARD_KEY_DOWN_ALT)
            alt_press = true;
        else if (scancode == KEYBOARD_KEY_UP_ALT)
            alt_press = false;

        // Check for System Key:
        if ((scancode == KEYBOARD_KEY_DOWN_WINDOWS_KEY_LEFT) || (scancode == KEYBOARD_KEY_DOWN_WINDOWS_KEY_RIGHT))
            system_press = true;
        else if ((scancode == KEYBOARD_KEY_UP_WINDOWS_KEY_LEFT) || (scancode == KEYBOARD_KEY_UP_WINDOWS_KEY_RIGHT))
            system_press = false;

        /* Check for numlock */
        if (scancode == KEYBOARD_KEY_DOWN_NUM_LOCK)
        {
            numlock = !numlock;
            keyboard_set_leds(numlock, capslock, scrllock);
        }

        /* Check for Caps lock */
        if (scancode == KEYBOARD_KEY_DOWN_CAPS_LOCK)
        {
            capslock = !capslock;
            keyboard_set_leds(numlock, capslock, scrllock);
        }
        
        /* Check for scroll lock */
        if (scancode == KEYBOARD_KEY_DOWN_SCROLL_LOCK)
        {
            scrllock = !scrllock;
            keyboard_set_leds(numlock, capslock, scrllock);
        }

        if ((ctrl_press) && (scancode == KEYBOARD_KEY_DOWN_S))
        {
            tty_puts("Nothing to save!\n");
            tty_puts("[ADAMANTINE]: ");
        }
        else if ((system_press) && (scancode == KEYBOARD_KEY_DOWN_W))
            tty_puts("System test...\n");
        else if (scancode == KEYBOARD_KEY_DOWN_ENTER)
        {
            tty_println();
            if (key_buffer[0] != 0)
            {
                user_input(key_buffer);
                key_buffer[0] = '\0';
            }
            tty_puts("[ADAMANTINE]: ");
        }
        else if (shift_press)
        {
            char c = keys_caps[(int)scancode];
            char str[2] = {c, '\0'};
            append(key_buffer, c);
            tty_puts(str);
        }
        else
        {
            if (scancode == KEYBOARD_KEY_DOWN_BACKSPACE)
            {
                backspace(key_buffer);
                tty_putchar('\b');
            } else
            {
                char c = keys_normal[(int)scancode];
                char str[2] = {c, '\0'};
                append(key_buffer, c);
                tty_puts(str);
            }
        }
    }
}

/* Get the last key pressed */
static inline char *
keyboard_get_keylast(void)
{
    return (key_last);
}

/* Read the keyboard command port */
static inline uint8_t
keyboard_read(void)
{
    if (init) {
        uint8_t status = inb(KEYBOARD_CMD);
        return (status);
    }
    return 0;
}

/* Write to the keyboard data port */
static inline void
keyboard_write_command(uint8_t cmd)
{
    if (init) {                                         // Make sure it's initialized first
        while (1)
            if (!(keyboard_read() & 0x2))
                break;
        outb(KEYBOARD_DATA, cmd);
    }
    else
    {
        tty_printf("[ERROR]: Keyboard has not been initialized...\n");
    }
}

/* Get the keyboard key */
static inline char *
keyboard_get_key(void)
{
    if (init) {
        keyboard_read();
        if (key_last != KEYBOARD_KEY_DOWN_NONE)
            return (key_last);
        return (KEYBOARD_KEY_DOWN_NONE);
    }
}

/* Set the keyboard LED's */
static inline void
keyboard_set_leds(bool num_lock, bool caps_lock, bool scroll_lock)
{
    uint8_t data = 0;

    data = (scroll_lock) ? (data | 0) : (data & 0);
    data = (num_lock) ? (num_lock | 1) : (num_lock & 1);
    data = (caps_lock) ? (caps_lock | 2) : (caps_lock & 2);

    outb(KEYBOARD_DATA, 0xED);
    outb(KEYBOARD_DATA, data);
}
