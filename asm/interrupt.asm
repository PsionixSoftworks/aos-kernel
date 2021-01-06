%macro ISR_NOERRCODE 1
  global isr%1
  isr%1:
    push byte 0                 ; Push a dummy error code.
    push %1                     ; Push the interrupt number.
    jmp isr_common_stub         ; Go to our common handler code.
%endmacro

; This macro creates a stub for an ISR which passes it's own
; error code.
%macro ISR_ERRCODE 1
  global isr%1
  isr%1:
    push %1                     ; Push the interrupt number
    jmp isr_common_stub
%endmacro

%macro IRQ 2
  global irq_%1
  irq_%1:
    cli
	  push byte 0
	  push byte %2
	  jmp irq_common_stub
%endmacro

ISR_ERRCODE 	  0
ISR_ERRCODE 	  1
ISR_ERRCODE 	  2
ISR_ERRCODE 	  3
ISR_ERRCODE 	  4
ISR_ERRCODE 	  5
ISR_ERRCODE 	  6
ISR_ERRCODE 	  7
ISR_ERRCODE   	8
ISR_ERRCODE 	  9
ISR_ERRCODE   	10
ISR_ERRCODE   	11
ISR_ERRCODE   	12
ISR_ERRCODE   	13
ISR_ERRCODE   	14
ISR_ERRCODE 	  15
ISR_ERRCODE 	  16
ISR_ERRCODE 	  17
ISR_ERRCODE 	  18
ISR_ERRCODE 	  19
ISR_ERRCODE 	  20
ISR_ERRCODE 	  21
ISR_ERRCODE 	  22
ISR_ERRCODE 	  23
ISR_ERRCODE 	  24
ISR_ERRCODE 	  25
ISR_ERRCODE 	  26
ISR_ERRCODE 	  27
ISR_ERRCODE 	  28
ISR_ERRCODE	    29
ISR_ERRCODE 	  30
ISR_ERRCODE 	  31
ISR_NOERRCODE   150

IRQ	0, 32
IRQ	1, 33
IRQ	2, 34
IRQ	3, 35
IRQ	4, 36
IRQ	5, 37
IRQ	6, 38
IRQ	7, 39
IRQ	8, 40
IRQ	9, 41
IRQ	10, 42
IRQ	11, 43
IRQ	12, 44
IRQ	13, 45
IRQ	14, 46
IRQ	15, 47

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
extern isr_handler              ; In isr.c
isr_common_stub:
    pusha                       ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    mov ax, ds                  ; Lower 16-bits of eax = ds.
    push eax                    ; save the data segment descriptor

    mov ax, 0x10                ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop ebx                     ; reload the original data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                        ; Pops edi,esi,ebp...
    add esp, 8                  ; Cleans up the pushed error code and pushed ISR number
    iret

[extern irq_handler]
irq_common_stub:
	  pusha
	
	  mov ax, ds
	  push eax
	
	  mov ax, 0x10
	  mov ds, ax
	  mov es, ax
	  mov fs, ax
	  mov gs, ax
	
	  call irq_handler
	
	  pop ebx
	  mov ds, bx
	  mov es, bx
	  mov fs, bx
	  mov gs, bx
	
	  popa
	  add esp, 8
    sti
	  iret
