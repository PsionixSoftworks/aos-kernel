/* Define the entrypoint of the kernel */
OUTPUT_FORMAT("elf32-i386")
ENTRY(_start)
SECTIONS
{
	. = 1M;					/* Kernel start address */
	kernel_base = .;
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
	.data BLOCK(4K) : ALIGN(4K)
	{ 
		*(.data) 
	}
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.special)
		*(.rodata)
	}
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)  
	}
	kernel_end = .;
}
