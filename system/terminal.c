/*
 *  File: terminal.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

/* Include anything the terminal requires here */
#include <stdarg.h>

#include "../include/terminal.h"
#include "../include/vga.h"
#include "../include/io.h"
#include "../include/keyboard.h"
#include "../include/mutex.h"

MODULE("terminal", "0.01a");

#define EOF		(-1)

/* Define mutexes here. */
DEFINE_MUTEX(m_mprintf);

static Terminal_t Terminal;
static UWORD *VideoMemory;
static DWORD TerminalPutchar(CHAR c);
static VOID MoveCursor(VOID);
static VOID Scroll(VOID);

VOID 
TerminalInit(UBYTE BackColor, UBYTE ForeColor) 
{
	VideoMemory = (UWORD *)VGA_TEXT_MODE_COLOR;
	Terminal.BackColor = BackColor;
	Terminal.ForeColor = ForeColor;
	Terminal.IsInitialized = TRUE;

	TerminalClearScreen();
}

VOID
TerminalClearScreen(VOID)
{
	UBYTE AttributeByte = ((Terminal.BackColor << 0x4) | (Terminal.ForeColor & 0x0F));
	UWORD Blank = 0x20 | (AttributeByte << 0x8);

	for (DWORD i = 0; i < (VGA_WIDTH * VGA_HEIGHT); i++) 
	{
		VideoMemory[i] = Blank;
	}
	Terminal.x = 0;
	Terminal.y = 0;
	MoveCursor();
}

VOID 
TerminalPrint(const STRING Str) 
{
	DWORD i = 0;
	while (Str[i]) 
	{
		TerminalPutchar(Str[i++]);
	}
}

VOID
TerminalPrintHex(UDWORD Value)
{
	TerminalPrintValue(Value, 0x10);
}

VOID
TerminalPrintDec(DWORD Value)
{
	TerminalPrintValue(Value, 0x0A);
}

static BOOL 
Print(const STRING Data, SIZE Length) 
{
	const UBYTE *Bytes = (const UBYTE *)Data;
	for (SIZE i = 0; i < Length; i++) 
	{
		if (TerminalPutchar(Bytes[i]) == EOF)
			return (FALSE);
		return (TRUE);
	}
}

static VOID 
Printf(const STRING Str, va_list ap) 
{
	MutexLock(&m_mprintf);
	STRING s = 0;
	CHAR Buffer[32768];
	for (SIZE i = 0; i < strlen((STRING)Str); i++) 
	{
		if (Str[i] == '%') 
		{
			switch (Str[i + 1]) 
			{
				case 's':
					s = va_arg(ap, const STRING);
					TerminalPrint(s);
					i++;
					continue;
				case 'b': {
					DWORD b = va_arg(ap, DWORD);
					TerminalPrint(itoa(b, Buffer, 0x2));
					i++;
					continue;
				}
				case 'o': {
					DWORD o = va_arg(ap, DWORD);
					TerminalPrint(itoa(o, Buffer, 0x8));
					i++;
					continue;
				}
				case 'd': {
					DWORD c = va_arg(ap, DWORD);
					TerminalPrintDec(c);
					i++;
					continue;
				}
				case 'x': {
					DWORD c = va_arg(ap, DWORD);
					DWORD FinalValue = itoa(c, Buffer, 0x10);
					to_lower(FinalValue);
					TerminalPrintHex(FinalValue);
					i++;
					continue;
				}
				case 'X': {
					DWORD c = va_arg(ap, DWORD);
					DWORD FinalValue = itoa(c, Buffer, 0x10);
					to_upper(FinalValue);
					TerminalPrintHex(FinalValue);
					i++;
					continue;
				}
			};
		} 
		else 
		{
			TerminalPutchar(Str[i]);
		}
	}
	MutexUnlock(&m_mprintf);
	va_end(ap);
}

DWORD 
TerminalPrintf(const STRING restrict Format, ...) 
{
	// TODO: Implement the printf function...
	if (!Format)
		return 0;
	va_list ap;
	va_start(ap, Format);
	Printf((const STRING)Format, ap);

	return (1);
}

VOID 
TerminalPrintln(VOID) 
{
	TerminalPrint("\n");
}

VOID 
TerminalPrintValue(DWORD Value, UBYTE Base) 
{
	CHAR Buffer[16];
	STRING NumberToString = itoa(Value, Buffer, Base);
	if (Base == 0x10)
		TerminalPrint("0x");
	if (Base == 0x2)
		TerminalPrint("0b");
	TerminalPrint(NumberToString);
}

static DWORD 
TerminalPutchar(CHAR c) 
{
	//terminal.fore_color = SYSTEM_COLOR_WHITE;

	UBYTE AttributeByte = ((Terminal.BackColor << 0x4) | (Terminal.ForeColor & 0x0F));
	UWORD Attribute = AttributeByte << 0x8;
	UWORD *Location;

	if ((c == 0x08) && (Terminal.x > 0x10)) 
	{
		TerminalMoveCursor(-1, 0);
		Location = VideoMemory + (Terminal.y * VGA_WIDTH + Terminal.x);
		*Location = ' ' | Attribute;
	} 
	else
	if (c == 0x09) 
	{
		Terminal.x = (Terminal.x + 0x4) & ~(0x4-0x1);
	} 
	else
	if (c == '\r') 
	{
		Terminal.x = 0;
	} 
	else
	if (c == '\n') 
	{
		Terminal.x = 0;
		Terminal.y++;
	} 
	else
	if (c >= ' ') 
	{
		Location = VideoMemory + (Terminal.y * VGA_WIDTH + Terminal.x);
		*Location = c | Attribute;
		Terminal.x++;
	}

	if (Terminal.x >= VGA_WIDTH) {
		Terminal.x = 0;
		Terminal.y++;
	}
	Scroll();
	MoveCursor();
}

static VOID 
MoveCursor(VOID) 
{
	UWORD CursorLocation = Terminal.y * VGA_WIDTH + Terminal.x;
	WritePortB(0x3D4, 14);
	WritePortB(0x3D5, CursorLocation >> 8);
	WritePortB(0x3D4, 15);
	WritePortB(0x3D5, CursorLocation);
}

static VOID 
Scroll(VOID) 
{
	UBYTE AtributeByte = ((Terminal.BackColor << 0x4) | (Terminal.ForeColor & 0x0F));
	UWORD Blank = 0x20 | (AtributeByte << 0x8);

	if (Terminal.y >= VGA_HEIGHT) 
	{
		DWORD i;
		for (i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++) 
		{
			VideoMemory[i] = VideoMemory[i + VGA_WIDTH];
		}

		for (i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < (VGA_WIDTH * VGA_HEIGHT); i++) 
		{
			VideoMemory[i] = Blank;
		}
		Terminal.y = VGA_HEIGHT - 1;
	}
}

CHAR 
terminal_getchar(CHAR c) 
{
	return (c);
}

STRING TerminalBuffer;
STRING
TerminalGets(STRING Str) 
{
	TerminalBuffer = strcpy(Str, TerminalBuffer);
	return (TerminalBuffer);
}

VOID 
TerminalMoveCursor(UDWORD x, UDWORD y)
{
	Terminal.x += x;
	Terminal.y += y;
	MoveCursor();
}

UDWORD TerminalGetCursorX(VOID)
{
	return (Terminal.x);
}

UDWORD TerminalGetCursorY(VOID)
{
	return (Terminal.y);
}

VOID 
Panic(const STRING Message, const STRING File, UDWORD Line) 
{
	__asm__ __volatile__("CLI");
	TerminalPrintf("!!! PANIC(%s) at %s : %d\n", Message, File, Line);
	CPU_Halt();
}

VOID
PanicAssert(const STRING File, UDWORD Line, const STRING Description) 
{
	__asm__ __volatile__("CLI");
	TerminalPrintf("!!! ASSERTION-FAILED(%s) at %s : %d.\n", Description, File, Line);
	CPU_Halt();
}
