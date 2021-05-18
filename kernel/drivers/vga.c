#include <kernel/drivers/vga.h>
#include <adamantine/aos-defs.h>
#include <string.h>

static uint16_t *video_buffer = NULL;
static uint8_t background_color UNUSED;
static uint8_t foreground_color UNUSED;
static uint32_t x UNUSED;
static uint32_t y UNUSED;

static inline void gfx_mode_begin(void);
static inline void txt_mode_mono_begin(void);
static inline void txt_mode_color_begin(void);

void
vga_init(enum video_mode vmode)
{
    switch (vmode)
    {
    case VGA_GRAPHICS_MODE:
        gfx_mode_begin();
        break;
    case VGA_TEXT_MODE_MONOCHROME:
        txt_mode_mono_begin();
        break;
    case VGA_TEXT_MODE_COLOR:
        txt_mode_color_begin();
        break;
    }
}

void
vga_clear_screen(void)
{

}

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

static inline void
gfx_mode_begin(void)
{
    video_buffer = (uint16_t *)VGA_GRAPHICS_MODE;
}

static inline void
txt_mode_mono_begin(void)
{
    video_buffer = (uint16_t *)VGA_TEXT_MODE_MONOCHROME;
}

static inline void
txt_mode_color_begin(void)
{
    video_buffer = (uint16_t *)VGA_TEXT_MODE_COLOR;

    //console.in.readln = &readln;
    //console.out.putchar = &putchar;
    //console.out.print = &print;
    //console.out.printf = &printf;
}
