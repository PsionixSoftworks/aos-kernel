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
static inline void keyboard_set_leds(bool num_lock, bool caps_lock, bool scroll_lock);

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
    uint8_t key;
    
    keyboard_set_leds(true, true, true);

    key = keyboard_read();
    if (!(key & 0x80) == 1)
        terminal_printf("%s", keys_normal[key]);
}        

static inline uint8_t
keyboard_read(void)
{
    if (initialized) {
        uint8_t status = (uint8_t)inb(KEYBOARD_COMMAND);
        if ((status & 0x01) == 1)
        return (inb(KEYBOARD_DATA));
    }
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
    if (initialized) {
        keyboard_read();
        if (key_last > KEYBOARD_KEY_DOWN_NONE)
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

    keyboard_write_command(0xED);
    keyboard_write_command(data);
}
