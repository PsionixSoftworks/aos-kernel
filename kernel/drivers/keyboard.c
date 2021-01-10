#include <kernel/drivers/keyboard.h>
#include <kernel/drivers/keys.h>
#include <kernel/system/io.h>
#include <kernel/system/terminal.h>
#include <kernel/isr.h>
#include <kernel/pic.h>

static inline void keyboard_handler(void);
static inline uint8_t keyboard_read(void);
static inline void keyboard_write_command(uint8_t cmd);
static inline char *keyboard_get_key(void);

static bool initialized = false;
static bool shift_press = false;
static uint8_t key_last = NULL;

void
keyboard_init(void)
{
    register_interrupt_handler(IRQ1, &keyboard_handler);

    terminal_printf("[INFO]: Keyboard is initialized!\n");
    initialized = true;
}

static inline void
keyboard_handler(void)
{
    uint8_t key = keyboard_read();

    if (!(key & 0x80) == 1)
        terminal_printf("%s", keys_normal[key]);
}        

static inline uint8_t
keyboard_read(void)
{
    uint8_t status = (uint8_t)inb(KEYBOARD_COMMAND);
    if ((status & 0x01) == 1)
       return (inb(KEYBOARD_DATA));
}

static inline void
keyboard_write_command(uint8_t cmd)
{
    if (initialized)
        outb(KEYBOARD_COMMAND, cmd);
    else
        terminal_printf("[ERROR]: Keyboard has not been initialized...\n");
}

static inline char *
keyboard_get_key(void)
{
    keyboard_read();
    if (key_last > KEYBOARD_KEY_DOWN_NONE)
        return (key_last);
    return (KEYBOARD_KEY_DOWN_NONE);
}
