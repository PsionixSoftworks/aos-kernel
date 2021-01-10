bits 32

MBOOT_HEADER_MAGIC  equ 0x1BADB002
MBOOT_ALIGN         equ 1 << 0
MBOOT_MEMINFO       equ 1 << 1
MBOOT_ENABLE_GFX    equ 1 << 2
MBOOT_FLAGS         equ (MBOOT_ALIGN | MBOOT_MEMINFO)
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_FLAGS)

section .multiboot
    dd MBOOT_HEADER_MAGIC

    dd MBOOT_FLAGS
    dd MBOOT_CHECKSUM

    dd MBOOT_ENABLE_GFX

section .text
global _start
extern kmain

_start:
    sti
    mov esp, stack_space
    call kmain
    jmp $
section .bss
resb 8192
stack_space:
