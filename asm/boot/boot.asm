[BITS 32]

MBALIGN         equ 1 << 0
MEMINFO         equ 1 << 1
VIDINFO         equ 1 << 2
FLAGS           equ MBALIGN | MEMINFO ;| VIDINFO
MAGIC           equ 0x1BADB002
CHECKSUM        equ -(MAGIC + FLAGS)

section .multiboot
align 4
        dd MAGIC
        dd FLAGS
        dd CHECKSUM
        dd 0, 0, 0, 0, 0
        dd 0
        dd 1024, 768, 32

section .bss
;align 16
stack_bottom:
resb 32768
stack_top:

section .text
extern k_main

global _start:function (_start.end - _start)
_start:
        mov esp, stack_top
        push esp
        
        call k_main
.hang:  hlt
        jmp .hang
.end:

global system_restart_safe
system_restart_safe:
    in al, 0x64
    test al, 0b00000010
    jne system_restart_safe

    mov al, 0xFE
    out 0x64, al

global tss_install
tss_install: 
    mov ax, 0x2B

    ltr ax
    ret
