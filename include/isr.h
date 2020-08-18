/*
 *  File: isr.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef ADAMANTINE_ISR
#define ADAMANTINE_ISR

#include "aos-defs.h"
#include "types.h"
#include "string.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define IRQ0		32
#define IRQ1		33
#define IRQ2		34
#define IRQ3		35
#define IRQ4		36
#define IRQ5		37
#define IRQ6		38
#define IRQ7		39
#define IRQ8		40
#define IRQ9		41
#define IRQ10		42
#define IRQ11		43
#define IRQ12		44
#define IRQ13		45
#define IRQ14		46
#define IRQ15		47

typedef struct AOS_Registers 
{
	UDWORD GS, FS, ES, DS;
	UDWORD EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
	UDWORD INT_No, ERR_Code;
	UDWORD EIP, CS, EFLAGS, USERESP, SS;
} Registers_t;

typedef VOID(*ISR_t)(Registers_t);
EXTERN	SET_VOID(RegisterInterruptHandler(UBYTE N, ISR_t Handler));

#if defined(__cplusplus)
}
#endif
#endif	// !ADAMANTINE_ISR
