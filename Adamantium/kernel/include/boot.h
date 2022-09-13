#ifndef _BOOT_H
#define _BOOT_H

/* Set the macro below to 1 to enable Graphic Mode */
#define USE_GFX_MODE	0			// This is only to be set to 0 when we're developing the kernel. Graphic mode will have glyphs
									// which will serve as the charset for ASCII fonts. But we will get to that...

/* For consistency sake, take off the 'MULTIBOOT_' prefix so 'AOUT_KLUDGE' isn't alone. */
#define HEADER_MAGIC	MULTIBOOT_HEADER_MAGIC
#define PAGE_ALIGN		MULTIBOOT_PAGE_ALIGN
#define MEMORY_INFO		MULTIBOOT_MEMORY_INFO

/* We want to be able to just toggle Graphic Mode on and off, so we'll de this */
#if defined(USE_GFX_MODE) && USE_GFX_MODE == 1
#define VIDEO_MODE		MULTIBOOT_VIDEO_MODE
#else
#define VIDEO_MODE		0
#endif

/* Check if the '__ELF__' macro is defined or not. If not, it will expand to the AOUT Kludge. */
#ifdef __ELF__
#define AOUT_KLUDGE		0
#else
#define AOUT_KLUDGE		MULTIBOOT_AOUT_KLUDGE
#endif

#define HEADER_FLAGS	(PAGE_ALIGN | MEMORY_INFO |  VIDEO_MODE | AOUT_KLUDGE)
#define STACK_SIZE		(1 << 16)

#endif
