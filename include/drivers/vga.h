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

#ifndef _ADAMANTINE_VGA_H
#define _ADAMANTINE_VGA_H

#define KERNEL_ONLY                                     // CAN ONLY BE ACCESSED IN KERNEL MODE!

#include <compiler.h>
#include <stdint.h>

/* VGA Teletype Screen Macros */
#define VGA_WIDTH                               80      // Width is 80px
#define VGA_HEIGHT                              25      // Height is 25px

/* The modes we can use to display information */
enum vga_mode
{
    VGA_GRAPHICS_MODE           =0x000A0000,            // Graphic mode
    VGA_TEXT_MODE_MONOCHROME    =0x000B0000,            // Monochrome Text
    VGA_TEXT_MODE_COLOR         =0x000B8000,            // Colored Text (See below)
};

/* Define the available VGA colors */
enum vga_color 
{
    SYSTEM_COLOR_BLACK,         // 0x00 | 0
    SYSTEM_COLOR_BLUE,          // 0x01 | 1
    SYSTEM_COLOR_GREEN,         // 0x02 | 2
    SYSTEM_COLOR_CYAN,          // 0x03 | 3
    SYSTEM_COLOR_RED,           // 0x04 | 4
    SYSTEM_COLOR_MAGENTA,       // 0x05 | 5
    SYSTEM_COLOR_BROWN,         // 0x06 | 6
    SYSTEM_COLOR_GRAY,          // 0x07 | 7
    SYSTEM_COLOR_DK_GRAY,       // 0x08 | 8
    SYSTEM_COLOR_LT_BLUE,       // 0x09 | 9
    SYSTEM_COLOR_LT_GREEN,      // 0x0A | 10
    SYSTEM_COLOR_LT_CYAN,       // 0x0B | 11
    SYSTEM_COLOR_LT_RED,        // 0x0C | 12
    SYSTEM_COLOR_LT_MAGENTA,    // 0x0D | 13
    SYSTEM_COLOR_YELLOW,        // 0x0E | 14
    SYSTEM_COLOR_WHITE,         // 0x0F | 15
};

typedef struct {
    uint16_t *buffer;
} VGA, *VGA_PTR;

/* Define the VESA VBE info struct for GFX mode */
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
} __packed;

/* Define the VESA VBE mode info struct for GFX mode */
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
} __packed;

/* Template Functions */
//extern void vga_init(enum video_mode vmode);          // Unused?
//extern void vga_clear_screen(void);                   // Unused?
//extern uint16_t find_mode(int x, int y, int d);         // Find the available display mode

#endif  // !_ADAMANTINE_VGA_H
