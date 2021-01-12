#include <kernel/drivers/keyboard.h>
#include <kernel/drivers/keys.h>
#include <kernel/system/io.h>
#include <kernel/system/terminal.h>
#include <kernel/isr.h>
#include <kernel/pic.h>

// Nested conditional statement= var = (expr1 == val ? expr2 : expr3);

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

unsigned char
keyboard_read_scancode(void)
{
    uint8_t status = keyboard_read();
    if ((status & 0x01) == 1)
        return (inb(KEYBOARD_DATA));
}

static inline void
keyboard_handler(void)
{
    static unsigned char scancode = NULL;
    scancode = keyboard_read_scancode();
    if ((scancode >= KEYBOARD_KEY_DOWN_NONE) && (!(scancode & 0x80)))
        keyboard_set_leds(0, 1, 0);
    /*if (!(scancode & 0x80) == 1) {
        terminal_printf("%s", keys_normal[scancode]);
    }*/
}        

static inline uint8_t
keyboard_read(void)
{
    if (initialized) {
        uint8_t status = inb(KEYBOARD_COMMAND);
        return (status);
    }
}

static inline void
keyboard_write_command(uint8_t cmd)
{
    if (initialized) {
        while (1)
            if (!(keyboard_read() & 0x2))
                break;
        outb(0x60, cmd);
    }
    else
    {
        terminal_printf("[ERROR]: Keyboard has not been initialized...\n");
    }
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

    outb(0x60, 0xED);
    outb(0x60, data);
}
