#ifndef _INIT_
#define _INIT_

#include "../include/kernel.h"
#include "../include/aos-defs.h"
#include "../include/x86/gdt.h"
#include "../include/x86/ldt.h"     /* WIP * */
#include "../include/x86/idt.h"

#if defined(__cplusplus)
extern "C" {
#endif

static void 
init_all(void) 
{
    gdt_init();
    ldt_init();
    idt_init();
}

#if defined(__cplusplus)
}
#endif

#define __initcall      _TEXT

#endif
