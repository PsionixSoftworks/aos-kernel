#include <system/portio.h>

static inline void
__port_write(uint16_t _port, uint32_t _value, uint8_t _type)
{
    switch (_type)
    {
    case 'b':
        __asm__ volatile (
            "outb %0, %1" : : 
            "a"((uint8_t)_value), 
            "Nd"(_port)
        );
        break;
    case 'w':
        __asm__ volatile (
            "outw %0, %1" : : 
            "a"((uint16_t)_value), 
            "Nd"(_port)
        );
        break;
    case 'l':
        __asm__ volatile (
            "outl %0, %1" : : 
            "a"((uint32_t)_value), 
            "Nd"(_port)
        );
        break;
    };
}

static inline uint32_t
__port_read(uint16_t _port, uint8_t _type)
{
    uint32_t value = 0;
    switch (_type)
    {
    case 'b':
        __asm__ volatile (
            "inb %1, %0" : 
            "=a"(value) : 
            "dN"(_port)
        );
        return (value);
        break;
    case 'w':
        __asm__ volatile (
            "inw %1, %0" : 
            "=a" (value) : 
            "dN" (_port)
        );
        return (value);
        break;
    case 'l':
        __asm__ volatile (
            "inl %1, %0" : 
            "=a"(value) : 
            "dN"(_port)
        );
        return (value);
        break;
    };
    return 0x0;
}

void
outb(uint16_t _port, uint8_t _value)
{
    __port_write(_port, _value, 'b');
}

void
outw(uint16_t _port, uint16_t _value)
{
    __port_write(_port, _value, 'w');
}

void
outl(uint16_t _port, uint32_t _value)
{
    __port_write(_port, _value, 'l');
}

uint8_t
inb(uint16_t _port)
{
    uint8_t value = (uint8_t)__port_read(_port, 'b');
    return value;
}

uint16_t
inw(uint16_t _port)
{
    uint16_t value = (uint16_t)__port_read(_port, 'w');
    return value;
}

uint32_t
inl(uint16_t _port)
{
    uint32_t value = (uint32_t)__port_read(_port, 'l');
    return value;
}

/* Check if IRQ's are enabled (defined in "idt.h") */
#ifndef IRQS_ENABLED
/* Wait on an IO port */
void 
__io_wait(void) 
{
	__asm__ volatile ( 	
        "JMP 1f\n\t" 
		"1:JMP 2f\n\t" 
		"2:"
    );
}
#else
void
__io_wait(void)
{
	__asm__ volatile (
        "outb %%al, $0x80" : : 
        "a"(0)
    );
}
#endif	// !IRQS_ENABLED
