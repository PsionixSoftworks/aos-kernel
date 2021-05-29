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

// Nested conditional statement= var = (expr1 == val ? expr2 : expr3);

// Define for normal keys:
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

static inline void keyboard_handler(void);
static inline uint8_t keyboard_read(void);
static inline void keyboard_write_command(uint8_t cmd);
static inline char *keyboard_get_key(void);
static inline void keyboard_set_leds(bool num_lock, bool caps_lock, bool scroll_lock);
static inline char *keyboard_get_keylast(void);

static bool init = false;
static bool shift_press = false;
static bool ctrl_press = false;
static bool system_press = false;
static bool alt_press = false;
static bool numlock UNUSED;
static bool capslock UNUSED;
static bool scrllock UNUSED;
static char *key_last = NULL;
static char key_buffer[256];

void
keyboard_init(void)
{
    if (!init)
    {
        //key_buffer = (char *)malloc(sizeof(char *));
        //memset(key_buffer, 0, sizeof(char) * 40);

        register_interrupt_handler(IRQ1, (isr_t)&keyboard_handler);
        //key_buffer = keyboard_get_keylast();

        tty_puts("[INFO]: Keyboard is initialized!\n");

        tty_puts("[ADAMANTINE]: ");
        
        init = true;
    }
}

unsigned char
keyboard_read_scancode(void)
{
    uint8_t status = keyboard_read();
    if ((status & 0x01) == 1)
        return (inb(KEYBOARD_DATA));
    return 0;
}

static void UNUSED
keyboard_set_typematic_byte(void)
{
    outb(KEYBOARD_DATA, 0xF3);
    outb(KEYBOARD_DATA, 0);
}

static inline void
user_input(char *buffer)
{
    tty_printf("\nResult: '%s'", buffer);
}

static inline void
backspace(char s[])
{
    int len = strlen(s);
    s[len - 1] = '\0';
}

static inline void
keyboard_handler(void)
{
    static unsigned char scancode;
    scancode = keyboard_read_scancode();

    if (scancode)
    {
        // Check for Escape:
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

        // Check for Caps lock:
        if (scancode == KEYBOARD_KEY_DOWN_CAPS_LOCK)
            shift_press = !shift_press;
        
        if ((ctrl_press) && (scancode == KEYBOARD_KEY_DOWN_S))
        {
            tty_puts("Nothing to save!\n");
            tty_puts("[ADAMANTINE]: ");
        }
        else if ((system_press) && (scancode == KEYBOARD_KEY_DOWN_W))
            tty_puts("System test...\n");
        else if (scancode == KEYBOARD_KEY_DOWN_ENTER)
        {
            if (key_buffer[0] != 0)
            {
                user_input(key_buffer);
                key_buffer[0] = '\0';
            }
            tty_puts("\n[ADAMANTINE]: ");
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

static inline char *
keyboard_get_keylast(void)
{
    return (key_last);
}

static inline uint8_t
keyboard_read(void)
{
    if (init) {
        uint8_t status = inb(KEYBOARD_CMD);
        return (status);
    }
    return 0;
}

static inline void
keyboard_write_command(uint8_t cmd)
{
    if (init) {
        while (1)
            if (!(keyboard_read() & 0x2))
                break;
        outb(KEYBOARD_DATA, cmd);
    }
    else
    {
        tty_printf("[ERROR]: Keyboard has not been init...\n");
    }
}

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

static inline void
keyboard_set_leds(bool num_lock, bool caps_lock, bool scroll_lock)
{
    uint8_t data = 0;

    data = (scroll_lock) ? (data | 1) : (data & 1);
    data = (num_lock) ? (num_lock | 2) : (num_lock & 2);
    data = (caps_lock) ? (caps_lock | 4) : (caps_lock & 4);

    outb(KEYBOARD_DATA, 0xED);
    outb(KEYBOARD_DATA, data);
}
