#include <drivers/i8042.h>
#include <drivers/driver.h>
#include <system/portio.h>

static inline unsigned char
i8042_startup_intern(unsigned char _status)
{
    unsigned char result;
    
    result = inb(_status);
    return result;
}

unsigned char
i8042_kb_initialize(void)
{
    unsigned char result;

    result = (i8042_startup_intern(I8042_STATUS) == 0 ? 1 : 0);
    return result;
}

uint8_t
i8042_read_status_register(void)
{
    uint8_t status;
    status = inb(I8042_STATUS);

    return status;
}

unsigned char
i8042_read_data(void)
{
    unsigned char data;
    data = inb(I8042_DATA);

    return data;
}
