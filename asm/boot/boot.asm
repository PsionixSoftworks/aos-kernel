bits 32

section .multiboot
    dd 0x1BADB002

    dd 0x0
    dd - (0x1BADB002 + 0x0)

section .text
global _start
extern kmain

_start:
    cli
    mov esp, stack_space
    call kmain
    jmp $

section .bss
resb 8192
stack_space:
