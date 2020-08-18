/*
 *  File: system.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/system.h"
#include "../include/io.h"
#include "../include/adamantine.h"
#include "../include/vga.h"

MODULE("System", "0.01a");

VOID 
SystemEnableCursor(UBYTE CursorStart, UBYTE CursorEnd) 
{
	WritePortB(0x3D4, 0x0A);
	WritePortB(0x3D5, (ReadPortB(0x3D5) & 0xC0) | CursorStart);
	
	WritePortB(0x3D4, 0x0B);
	WritePortB(0x3D5, (ReadPortB(0x3D5) & 0xE0) | CursorEnd);
}

VOID 
SystemDisableCursor(VOID) 
{
	WritePortB(0x3D4, 0x0A);
	WritePortB(0x3D5, 0x20);
}

VOID 
SystemUpdateCursor(UDWORD x, UDWORD y) 
{
	UWORD Pos = y * VGA_WIDTH + x;
	
	WritePortB(0x3D4, 0x0F);
	WritePortB(0x3D5, (UBYTE)(Pos & 0xFF));
	WritePortB(0x3D4, 0x0E);
	WritePortB(0x3D5, (UBYTE)((Pos >> 8) & 0xFF));
}

UWORD 
SystemGetCursorPosition(void)
{
	UWORD Pos = 0;
	WritePortB(0x3D4, 0x0F);
	Pos |= ReadPortB(0x3D5);
	WritePortB(0x3D4, 0x0E);
	Pos |= ((UWORD)ReadPortB(0x3D5)) << 8;
	return (Pos);
}
