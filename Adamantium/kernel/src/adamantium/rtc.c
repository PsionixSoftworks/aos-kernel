#include <kernel/rtc.h>
#include <system/portio.h>
#include <kernel/isr.h>

int century_reg = 0x00;

unsigned char second;
unsigned char minute;
unsigned char hour;
unsigned char day;
unsigned char month;
unsigned char year;

static inline void rtc_callback(void);

void
rtc_initialize(void)
{
    register_interrupt_handler(IRQ8, &rtc_callback);
}

extern int
get_update_in_progress_flag(void)
{
    outb(RTC_CMOS_ADDRESS, 0x0A);
    return inb(RTC_CMOS_DATA) & 0x80;
}

extern unsigned char
get_rtc_register(unsigned char _register)
{
    outb(RTC_CMOS_ADDRESS, _register);
    return inb(RTC_CMOS_DATA);
}

extern void 
read_rtc(void)
{
    unsigned char century;
    unsigned char last_second;
    unsigned char last_minute;
    unsigned char last_hour;
    unsigned char last_day;
    unsigned char last_month;
    unsigned char last_year;
    unsigned char last_century;
    unsigned char register_b;

    while (get_update_in_progress_flag());
    second  = get_rtc_register(0x00);
    minute  = get_rtc_register(0x02);
    hour    = get_rtc_register(0x04);
    day     = get_rtc_register(0x07);
    month   = get_rtc_register(0x08);
    year    = get_rtc_register(0x09);
    if (century_reg != 0)
    {
        century = get_rtc_register(century_reg);
    }

    do {
        last_second = second;
        last_minute = minute;
        last_hour   = hour;
        last_day    = day;
        last_month  = month;
        last_year   = year;
        last_century= century;

        while (get_update_in_progress_flag());
        second  = get_rtc_register(0x00);
        minute  = get_rtc_register(0x02);
        hour    = get_rtc_register(0x04);
        day     = get_rtc_register(0x07);
        month   = get_rtc_register(0x08);
        year    = get_rtc_register(0x09);
        if (century_reg != 0)
        {
            century = get_rtc_register(century_reg);
        }
    } while (   (last_second != second) ||
                (last_minute != minute) ||
                (last_hour != hour)     ||
                (last_day != day)       ||
                (last_month != month)   ||
                (last_year != year)     ||
                (last_century != century));
    register_b = get_rtc_register(0x0B);

    if (!(register_b & 0x04))
    {
        second  = (second & 0x0F) + ((second / 16) * 10);
        minute  = (minute & 0x0F) + ((minute / 16) * 10);
        hour    = ((hour & 0x0F) + (((hour & 0x70) /  16) * 10)) | (hour & 0x80);
        day     = (day & 0x0F) + ((day / 16) * 10);
        month   = (month & 0x0F) + ((month / 16) * 10);
        year    = (year & 0x0F) + ((year / 16) * 10);
        if (century_reg != 0)
        {
            century = (century & 0x0F) + ((century / 16) * 10);
        }

        if (!(register_b & 0x02) && (hour & 0x80))
            hour = ((hour & 0x7F) + 12) % 24;
        
        if (century_reg != 0)
            year += century * 100;
        else
        {
            year += (CURRENT_YEAR / 100) * 100;
            if (year < CURRENT_YEAR)
                year += 100;
        }
    }
}

/* The RTC callback is used for RTC initialization and setting certain values. */
static inline void
rtc_callback(void)
{
    // TODO: Figure out what goes here...
}
