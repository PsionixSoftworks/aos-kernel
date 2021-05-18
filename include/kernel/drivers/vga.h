/*
 *  File: vga.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _AOS_VGA_H
#define _AOS_VGA_H

#include <adamantine/compiler.h>
#include <stdint.h>

#define VGA_WIDTH                   80
#define VGA_HEIGHT                  25

enum video_mode
{
    VGA_GRAPHICS_MODE           =0xA0000,
    VGA_TEXT_MODE_MONOCHROME    =0xB0000,
    VGA_TEXT_MODE_COLOR         =0xB8000,
};

enum vga_color 
{
    SYSTEM_COLOR_BLACK,
    SYSTEM_COLOR_BLUE,
    SYSTEM_COLOR_GREEN,
    SYSTEM_COLOR_CYAN,
    SYSTEM_COLOR_RED,
    SYSTEM_COLOR_MAGENTA,
    SYSTEM_COLOR_BROWN,
    SYSTEM_COLOR_GRAY,
    SYSTEM_COLOR_DK_GRAY,
    SYSTEM_COLOR_LT_BLUE,
    SYSTEM_COLOR_LT_GREEN,
    SYSTEM_COLOR_LT_CYAN,
    SYSTEM_COLOR_LT_RED,
    SYSTEM_COLOR_LT_MAGENTA,
    SYSTEM_COLOR_YELLOW,
    SYSTEM_COLOR_WHITE
};

struct vbe_info_structure {
    char                    signature[4];
    uint16_t                version;
    uint32_t                oem;
    uint32_t                capabilities;
    uint32_t                video_modes;
    uint16_t                video_memory;
    uint16_t                software_rev;
    uint32_t                vendor;
    uint32_t                product_name;
    uint32_t                product_rev;
    char                    reserved[222];
    char                    *oem_data[256];
} PACKED;

struct vbe_mode_info_structure {
    uint16_t                attributes;
    uint8_t                 window_a;
    uint8_t                 window_b;
    uint16_t                granularity;
    uint16_t                window_size;
    uint16_t                segment_a;
    uint16_t                segment_b;
    uint32_t                win_func_ptr;
    uint16_t                pitch;
    uint16_t                xres;
    uint16_t                yres;
    uint8_t                 w_char;
    uint8_t                 y_char;
    uint8_t                 planes;
    uint8_t                 bpp;
    uint8_t                 banks;
    uint8_t                 memory_model;
    uint8_t                 bank_size;
    uint8_t                 image_pages;
    uint8_t                 reserved0;

    uint8_t                 red_mask;
    uint8_t                 red_position;
    uint8_t                 green_mask;
    uint8_t                 green_position;
    uint8_t                 blue_mask;
    uint8_t                 blue_position;
    uint8_t                 reserved_mask;
    uint8_t                 reserved_position;
    uint8_t                 direct_color_attributes;

    uint32_t                framebuffer;
    uint32_t                off_screen_mem_off;
    uint16_t                off_screen_mem_size;
    uint8_t                 reserved1[206];
} PACKED;

void vga_init(enum video_mode vmode);
void vga_clear_screen(void);
uint16_t find_mode(int x, int y, int d);

#endif  // !_AOS_VGA_H
