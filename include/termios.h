#ifndef _TERMIOS_H
#define _TERMIOS_H

#include <timers.h>

typedef unsigned short  tcflag_t;
typedef unsigned short  cc_t;
typedef unsigned char   speed_t;

#define NCCS            20  /* Size of cc array; Find out why this needs to be 20. */

struct termios {
    tcflag_t c_iflag;
    tcflag_t c_oflag;
    tcflag_t c_cflag;
    tcflag_t c_lflag;
    speed_t c_ispeed;
    speed_t c_ospeed;
    cc_t c_cc[NCCS];
};

/* c_iflag bitmaps; See if the values are really that important... */
#define IF_BRKINT       0x0001              // 0x0001
#define IF_ICRNL        (IF_BRKINT  << 1)   // 0x0002
#define IF_IGNBRK       (IF_CRNL    << 1)   // 0x0004
#define IF_IGNCR        (IF_IGNBRK  << 1)   // 0x0008
#define IF_IGNPAR       (IF_IGNCR   << 1)   // 0x0010
#define IF_INLCR        (IF_IGNPAR  << 1)   // 0x0020
#define IF_INPCK        (IF_INLCR   << 1)   // 0x0040
#define IF_ISTRIP       (IF_INPCK   << 1)   // 0x0080
#define IF_IXOFF        (IF_ISTRIP  << 1)   // 0x0100
#define IF_IXON         (IF_IXOFF   << 1)   // 0x0200
#define IF_PARMRK       (IF_IXON    << 1)   // 0x0400

/* c_oflags bitmaps; See if the values are really that important... */
#define OF_OPOST        0x0001

/* c_cflag bitmaps; See if the values are really that important... */
#define CF_CLOCAL       0x0001
#define CF_CREAD        (CF_CLOCAL  << 1)
#define CF_CSIZE        0x000C
#define CF_CS5          0x0000
#define CF_CS6          0x0004
#define CF_CS7          0x0008
#define CF_CS8          0x000C
#define CF_CSTOPB       0x0010
#define CF_HUPCL        0x0020
#define CF_PARENB       0x0040
#define CF_PARODD       0x0080

/* c_lflag bitmaps; See if the values are really that important... */
#define LF_ECHO         0x0001
#define LF_ECHOE        0x0002
#define LF_ECHOK        0x0004
#define LF_ECHONL       0x0008
#define LF_ICANON       0x0010
#define LF_IEXTEN       0x0020
#define LF_ISIG         0x0040
#define LF_NOFLSH       0x0080
#define LF_TOSTOP       0x0100

/* c_cc array */
#define CC_VEOF         0x0000
#define CC_VEOL         0x0001
#define CC_VERASE       0x0002
#define CC_VINTR        0x0003
#define CC_VKILL        0x0004
#define CC_VMIN         0x0005
#define CC_VQUIT        0x0006
#define CC_VTIME        0x0007
#define CC_VSUSP        0x0008
#define CC_VSTART       0x0009
#define CC_VSTOP        0x000A

#define _POSIX_VDISABLE (cc_t)0xFF

/* Baud rate settings (POSIX STANDARD) */
#define B0              0x0000
#define B50             0x1000
#define B75             0x2000
#define B110            0x3000
#define B134            0x4000
#define B150            0x5000
#define B200            0x6000
#define B300            0x7000
#define B600            0x8000
#define B1200           0x9000
#define B1800           0xA000
#define B2400           0xB000
#define B4800           0xC000
#define B9600           0xD000
#define B19200          0xE000
#define B38400          0xF000

#ifndef _ANSI_H
#include <ansi.h>
#endif

int tcsendbreak(int _FileDes, int Duration);
int tcdrain(int _FileDes);
int tcflush(int _FileDes, int _QueueSelector);
int tcflow(int _FileDes, int _Action);
speed_t cfgetispeed(const struct termios *_Termios_p);
speed_t cfgetospeed(const struct termios *_Termios_p);
int cfsetispeed(struct termios *_Termios_p, speed_t _speed);
int cfsetospeed(struct termios *_Termios_p, speed_t _speed);
int tcgetattr(int _FileDes, struct termios *_Termios_p);
int tcsetattr(int _FileDes, int _OptActions, const struct termios *_Termios_p);

#if defined(__ADAMANTINE__) || defined(_MINIX)
struct winsize {
    unsigned short ws_row;
    unsigned short ws_col;
    unsigned short ws_xpixel;
    unsigned short ws_ypixel;
};
#endif

#endif
