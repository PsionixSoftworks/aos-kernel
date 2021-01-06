#include <kernel/drivers/keyboard.h>
#include <kernel/drivers/keys.h>
#include <kernel/system/io.h>

static bool _kybrd_disabled = false;

enum KYBRD_ENCODER_IO {
    KYBRD_ENC_INPUT_BUF     = 0x60,
    KYBRD_ENC_CMD_REG       = 0x60
};

enum KYBRD_CTRL_IO {
    KYBRD_CTRL_STATS_REG    = 0x64,
    KYBRD_CTRL_CMD_REG      = 0x64
};

enum KYBRD_CTRL_STATUS_MASK {
    KYBRD_CTRL_STATS_MASK_OUT_BUF = 1,
    KYBRD_CTRL_STATS_MASK_IN_BUF = 2,
    KYBRD_CTRL_STATS_MASK_SYSTEM = 4,
    KYBRD_CTRL_STATS_MASK_CMD_DATA = 8,
    KYBRD_CTRL_STATS_MASK_LOCKED = 0x10,
    KYBRD_CTRL_STATS_MASK_AUX_BUF = 0x20,
    KYBRD_CTRL_STATS_MASK_TIMEOUT = 0x40,
    KYBRD_CTRL_STATS_MASK_PARITY = 0x80
};

uint8_t
kkybrd_enc_read_buf(void)
{
    return (inb(KYBRD_CTRL_STATS_REG));
}

void
kkybrd_ctrl_send_cmd(uint8_t cmd)
{
    while (1)
        if ((kkybrd_enc_read_buf() & KYBRD_CTRL_STATS_MASK_IN_BUF) == 0)
            break;
    outb(KYBRD_CTRL_CMD_REG, cmd);
}

void
kkybrd_set_leds(bool num, bool caps, bool scroll)
{
    uint8_t data = 0;

    data = (scroll) ? (data | 1) : (data & 1);
    data = (num) ? (num | 2) : (num & 2);
    data = (caps) ? (caps | 4) : (caps & 4);

    kkybrd_ctrl_send_cmd(KYBRD_ENC_CMD_SET_LED);
    kkybrd_ctrl_send_cmd(data);
}

bool
kkybrd_self_test(void)
{
    kkybrd_ctrl_send_cmd(KYBRD_CTRL_CMD_SELF_TEST);
    while (1)
        if ((kkybrd_enc_read_buf() & KYBRD_CTRL_STATS_MASK_IN_BUF) == 0)
            break;
    return (kkybrd_enc_read_buf() == 0x55) ? true : false;
}

void
kkybrd_disable(void)
{
    kkybrd_ctrl_send_cmd(KYBRD_CTRL_CMD_DISABLE);
    _kybrd_disabled = true;
}

void
kkybrd_reset_system(void)
{
    kkybrd_ctrl_send_cmd(KYBRD_CTRL_CMD_WRITE_OUT_PORT);
    kkybrd_ctrl_send_cmd(0xFE);
}
