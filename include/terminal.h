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

#if defined(__cplusplus)
extern "C" {
#endif

#define INFO(msg)				TerminalPrintf("[INFO]: %s\n", msg);
#define WARNING(msg)			TerminalPrintf("[WARNING]: %s\n", msg);
#define ERROR(msg)				TerminalPrintf("[ERROR]: %s\n", msg); CPU_Halt();
#define PANIC(msg, i1, i2)		Panic(msg, __FILE__, __LINE__);
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

EXTERN 	SET_VOID(TerminalInit(UBYTE BackColor, UBYTE ForeColor));
EXTERN 	SET_VOID(TerminalClearScreen(VOID));
EXTERN 	SET_VOID(TerminalPrint(const STRING c));
EXTERN 	SET_VOID(TerminalPrintHex(UDWORD Value));
EXTERN 	SET_VOID(TerminalPrintDec(DWORD Value));
EXTERN 	SET_DWORD(TerminalPrintf(const STRING Format, ...));
EXTERN 	SET_VOID(TerminalPrintln(VOID));
EXTERN 	SET_VOID(TerminalPrintValue(DWORD Value, UBYTE Base));
EXTERN 	SET_CHAR(Terminal_GetChar(CHAR c));
EXTERN 	SET_STRING(TerminalGets(STRING str));
EXTERN 	SET_VOID(TerminalMoveCursor(UDWORD x, UDWORD y));
EXTERN 	SET_UDWORD(TerminalGetCursorX(VOID));
EXTERN 	SET_UDWORD(TerminalGetCursorY(VOID));
EXTERN 	SET_VOID(Panic(const STRING Message, const STRING File, UDWORD Line));
EXTERN 	SET_VOID(PanicAssert(const STRING File, UDWORD Line, const STRING Descrition));

#if defined(__cplusplus)
}
#endif

#endif
