.set ALIGN,     1 << 0
.set MEMINFO,   1 << 1
.set FLAGS,     ALIGN | MEMINFO
.set MAGIC,     0x1BADB002
.set CHECKSUM,  -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.globl _start
.type _start, @function
_start:
    mov $stack_top, %esp
    call k_main
1:  hlt
    jmp 1b
.size _start, . - _start

// Handle the TSS in here for now until a better way is defined:
.globl tss_flush
tss_flush:
    mov $0x2B, %ax

    ltr %ax
    ret
// Reset the computer. This seems to be the best way to do it. Perhaps I'll put time into research, but for now...
.globl system_restart_safe
system_restart_safe:
    in $0x64, %al
    test $0b00000010, %al
    jne system_restart_safe

    mov $0xFE, %al
    out %al, $0x64
