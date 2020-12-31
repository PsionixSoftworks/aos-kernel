.globl gdt_flush
gdt_flush:
    movl 4(%esp), %eax
    lgdt (%eax)

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    jmp $0x08,$flush
flush:
    ret

.globl ldt_flush
ldt_flush:
    movl 4(%esp), %eax
    lldt (%eax)
    ret

.globl idt_flush
idt_flush:
    movl 4(%esp), %eax
    lidt (%eax)
    ret

.globl tss_flush
tss_flush:
    mov $0x2B, %ax

    ltr %ax
    ret
