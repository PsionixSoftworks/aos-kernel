MBALIGN     equ 1 << 0
MEMINFO     equ 1 << 1
GFX_MODE    equ 1 << 2
FLAGS       equ MBALIGN | MEMINFO ;| GFX_MODE
MAGIC       equ 0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd  MAGIC
    dd  FLAGS
    dd  CHECKSUM

    dd 0
    dd 0
    dd 0
    dd 0
    dd 0

    dd 0
    dd 800
    dd 600
    dd 32

section .bss
align   16
stack_bottom:
resb    16384
stack_top:
mboot_ptr:
        resb 4

section .text
extern kmain
global _start:function (_start.end - _start)
_start:
        mov esp, stack_top
        mov ebp, 0
        and esp, 0FFFFFFF0h
        mov [mboot_ptr], ebx

        push ebx
        call kmain
.hang:  hlt
        jmp .hang
.end
