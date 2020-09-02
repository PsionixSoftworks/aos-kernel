.section .text
.globl __user_mode
.type __user_mode, @function
_user_mode:
    cli

    mov $0x23, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    mov %esp, %eax
    pushl $0x23
    pushl %eax
    pushf
    pushl $0x1B
    push $1f
1:
    iret
