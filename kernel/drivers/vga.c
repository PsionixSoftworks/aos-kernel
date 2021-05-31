#include <kernel/drivers/vga.h>
#include <adamantine/aos-defs.h>
#include <string.h>

/* Find the current "mode"? */
/*
uint16_t
find_mode(int x, int y, int d)
{
    struct vbe_info_structure *ctrl = (struct vbe_info_structure *)0x2000;
    struct vbe_mode_info_structure *inf = (struct vbe_mode_info_structure *)0x3000;
    uint16_t *modes;
    int i;
    uint16_t best = 0x13;
    int pixdiff, bestpixdiff = ((320 * 200) - (x * y));
    int depthdiff, bestdepthdiff = 8 >= d ? 8 - d : (d - 8) * 2;

    strcpy(ctrl->signature, "VBE2");
}
*/