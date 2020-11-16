#ifndef AOS_CORE_H
#define AOS_CORE_H

/* Include the necessary kernel core components */
#include <kernel/system/terminal.h>
#include <kernel/drivers/vga.h>
#include <kernel/x86/descriptor-tables.h>
#include <kernel/pit.h>
#include <kernel/memory/paging.h>
#include <kernel/memory/mm.h>

#define USING_CENTRIX_CORE
#include <adamantine/adamantine.h>

#endif
