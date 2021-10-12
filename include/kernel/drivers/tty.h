#ifndef _KERNEL_DRIVER_TTY_H
#define _KERNEL_DRIVER_TTY_H

#include <timers.h>

#define CONSOLE_MINOR       0
#define LOG_MINOR           15
#define RS232_MINOR         16
#define TTYPX_MINOR         128
#define PTYPX_MINOR         192

#define LINEWRAP            1

#define TTY_IN_BYTES        256
#define TAB_SIZE            8
#define TAB_MASK            7

#define ESC                 '\33'

#define O_NOCTTY            00400
#define O_NONBLOCK          04000

struct tty;
typedef _PROTO(int (*devfun_t), (struct tty *tty_ptr, int try_only));
typedef _PROTO(void (*devfunarg_t), (struct tty *tty_ptr, int c));

typedef struct tty
{
    int tty_events;
    int tty_index;
    int tty_minor;

    uint16_t *tty_inhead;
    uint16_t *tty_intail;
    int tty_incount;
    int tty_eotct;
    devfun_t tty_devread;
    devfun_t tty_icancel;
    int tty_min;
    timer_t tty_timer;

    devfun_t tty_devwrite;
    devfunarg_t tty_echo;
    devfun_t tty_ocancel;
    devfun_t tty_break;

    int tty_position;
    char tty_reprint;
    char tty_escaped;
    char tty_inhibited;
    char tty_pgrp;
    char tty_openct;

    char tty_inrepcode;
    char tty_inrevived;
    char tty_incaller;
    char tty_inproc;
    vir_bytes tty_in_vir;
    int tty_inleft;
    int tty_incum;
    char tty_outrepcode;
    char tty_outrevived;
    char tty_outcaller;
    char tty_outproc;
    vir_bytes tty_out_vir;
    int tty_outleft;
    int tty_outcum;
    char tty_iocaller;
    char tty_ioproc;
    int tty_ioreq;
    vir_bytes tty_iovir;

    int tty_select_ops;
    int tty_select_proc;

    devfun_t tty_ioctl;
    devfun_t tty_close;
    void *tty_priv;
    struct termios tty_termios;
    struct winsize tty_winsize;

    uint16_t tty_inbuf[TTY_IN_BYTES];
} tty_t;

//extern tty_t tty_table[NR_CONS + NR_RS_LINES + NR_PTYS];

#endif
