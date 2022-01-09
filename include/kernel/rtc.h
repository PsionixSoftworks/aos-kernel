#ifndef _RTC_H
#define _RTC_H

#define CURRENT_YEAR        2022
#define RTC_CMOS_ADDRESS    0x70
#define RTC_CMOS_DATA       0x71

extern void rtc_initialize(void);
extern int get_update_in_progress_flag(void);
extern unsigned char get_rtc_register(unsigned char _register);
extern void read_rtc(void);

#endif
