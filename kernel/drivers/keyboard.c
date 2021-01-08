#include <kernel/drivers/keyboard.h>
#include <kernel/drivers/keys.h>
#include <kernel/system/io.h>
#include <kernel/system/terminal.h>
#include <kernel/isr.h>
#include <kernel/pic.h>

static uint8_t keyboard_read_status(void);

static void
keyboard_send_command(uint8_t cmd)
{
    outb(KEYBOARD_DATA, cmd);
}

static void
keyboard_handler(registers_t regs)
{
    unsigned char scancode = keyboard_read_scancode();
    terminal_printf("Scancode: 0x%x\n", scancode);
}

void
keyboard_init(void)
{
    outb(0x21, 0xFD);
    uint8_t status = keyboard_read_status();

    register_interrupt_handler(IRQ1, keyboard_handler);
    pic_send_eoi(IRQ1);

    terminal_printf("[INFO]: Keyboard is initialized.\n");
}

unsigned char
keyboard_read_scancode(void)
{
    //if (inb(KEYBOARD_DATA))

}

static uint8_t
keyboard_read_status(void)
{
    return (inb(KEYBOARD_STATUS));
}