#ifndef _AOS_KEYBOARD_H
#define _AOS_KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#define KYBRD_ENC_CMD_SET_LED           0xED
#define KYBRD_CTRL_CMD_SELF_TEST        0xAA
#define KYBRD_CTRL_CMD_DISABLE          0xAD
#define KYBRD_CTRL_CMD_WRITE_OUT_PORT   0xFE

uint8_t kkybrd_enc_read_buf(void);
void kkybrd_ctrl_send_cmd(uint8_t cmd);
void kkybrd_set_leds(bool num, bool caps, bool scroll);
bool kkybrd_self_test(void);
void kkybrd_disable(void);
void kkybrd_reset_system(void);

#endif
