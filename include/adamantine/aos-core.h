#ifndef AOS_CORE_H
#define AOS_CORE_H

/* Include the necessary kernel core components */
#include <kernel/system/terminal.h>
#include <kernel/drivers/vga.h>
#include <kernel/x86/descriptor-tables.h>
#include <kernel/pit.h>
#include <kernel/memory/paging.h>
#include <kernel/memory/mm.h>
#include <kernel/cpu.h>
#include <kernel/cpuid.h>

#define USING_CENTRIX_CORE
#include <adamantine/adamantine.h>
#include <adamantine/adamantine-x86.h>

#endif
