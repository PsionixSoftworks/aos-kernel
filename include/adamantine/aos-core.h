#ifndef AOS_CORE_H
#define AOS_CORE_H

/* Include the whole system */
#include <adamantine/adamantine.h>
#include <adamantine/adamantine-x86.h>
#include <adamantine/aos-defs.h>
#include <adamantine/aos-string.h>
#include <adamantine/aos-types.h>
#include <adamantine/limits.h>
#include <adamantine/mutex.h>
#include <backend/back.h>           // ?
#include <centrix/base32.h>         // ?
#include <centrix/centrix-unit.h>   // ?
#include <centrix/centrix.h>
#include <centrix/centrix-core.h>
#include <cmd/cmd.h>                // ?
#include <drivers/bus/bus.h>        // ?
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/keys.h>
#include <drivers/pci/pci.h>
#include <drivers/vga.h>
#include <filesys/aos-fs.h>
#include <filesys/ext2.h>
#include <filesys/vfs.h>
#include <math/math-util.h>         // ?
#include <math/simple-math.h>       // ?
#include <math/vector2f.h>          // ?
#include <x86/descriptor-tables.h>
#include <memory/balloon.h>
#include <memory/block.h>                  // ?
#include <memory/chunk.h>                  // ?
#include <memory/mm.h>
#include <kernel/cpu.h>
#include <kernel/cpuid.h>
#include <kernel/irq.h>
#include <kernel/isr.h>
#include <kernel/kernel.h>
#include <kernel/pic.h>
#include <kernel/pit.h>
#include <system/io.h>
#include <system/syscall.h>
#include <system/system.h>
#include <system/terminal.h>
#include <init.h>
#include <input.h>
#include <main.h>
#include <map.h>
#include <output.h>
#include <paging.h>
#include <task.h>
#include <tss.h>

#endif
