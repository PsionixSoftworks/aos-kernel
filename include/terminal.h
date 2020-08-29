/*
 *  File: terminal.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _AOS_TERMINAL_
#define _AOS_TERMINAL_

#include "aos-defs.h"
#include "types.h"
#include "string.h"
#include "cpu.h"

#define INFO(msg)				TerminalPrintf("[INFO]: %s\n", msg);
#define WARNING(msg)			TerminalPrintf("[WARNING]: %s\n", msg);
#define ERROR(msg)				TerminalPrintf("[ERROR]: %s\n", msg); CPU_Halt();
#define PANIC(msg)				Panic(msg, __FILE__, __LINE__);
#define ASSERT(b) 				((b) ? (void)0 : PanicAssert(__FILE__, __LINE__, #b))

typedef struct AOS_Terminal Terminal_t;

struct AOS_Terminal 
{
	BOOL IsInitialized;
	UDWORD x;
	UDWORD y;
	UBYTE ForeColor;
	UBYTE BackColor;
} PACKED;

EXTERN 	VOID (TerminalInit(UBYTE BackColor, UBYTE ForeColor));
EXTERN 	VOID (TerminalClearScreen(VOID));
EXTERN 	VOID (TerminalPrint(const STRING c));
EXTERN 	VOID (TerminalPrintHex(UDWORD Value));
EXTERN 	VOID (TerminalPrintDec(DWORD Value));
EXTERN 	DWORD (TerminalPrintf(const STRING Format, ...));
EXTERN 	VOID (TerminalPrintln(VOID));
EXTERN 	VOID (TerminalPrintValue(DWORD Value, UBYTE Base));
EXTERN 	CHAR (Terminal_GetChar(CHAR c));
EXTERN 	STRING(TerminalGets(STRING str));
EXTERN 	VOID (TerminalMoveCursor(UDWORD x, UDWORD y));
EXTERN 	UDWORD (TerminalGetCursorX(VOID));
EXTERN 	UDWORD (TerminalGetCursorY(VOID));
EXTERN 	VOID (Panic(const STRING Message, const STRING File, UDWORD Line));
EXTERN 	VOID (PanicAssert(const STRING File, UDWORD Line, const STRING Descrition));

#endif
