%macro ISR_NOERRCODE 1
  global ISR_%1
  ISR_%1:
    cli                         ; Disable interrupts firstly.
    push byte 0                 ; Push a dummy error code.
    push byte %1                ; Push the interrupt number.
    jmp ISR_CommonStub         ; Go to our common handler code.
%endmacro

; This macro creates a stub for an ISR which passes it's own
; error code.
%macro ISR_ERRCODE 1
  GLOBAL ISR_%1
  ISR_%1:
    CLI                         ; Disable interrupts.
    PUSH %1                ; Push the interrupt number
    JMP ISR_CommonStub
%endmacro

%macro IRQ 2
GLOBAL IRQ_%1
IRQ_%1:
	CLI
	PUSH BYTE 0
	PUSH BYTE %2
	JMP IRQ_CommonStub
%endmacro

ISR_NOERRCODE 	0
ISR_NOERRCODE 	1
ISR_NOERRCODE 	2
ISR_NOERRCODE 	3
ISR_NOERRCODE 	4
ISR_NOERRCODE 	5
ISR_NOERRCODE 	6
ISR_NOERRCODE 	7
ISR_ERRCODE   	8
ISR_NOERRCODE 	9
ISR_ERRCODE   	10
ISR_ERRCODE   	11
ISR_ERRCODE   	12
ISR_ERRCODE   	13
ISR_ERRCODE   	14
ISR_NOERRCODE 	15
ISR_NOERRCODE 	16
ISR_NOERRCODE 	17
ISR_NOERRCODE 	18
ISR_NOERRCODE 	19
ISR_NOERRCODE 	20
ISR_NOERRCODE 	21
ISR_NOERRCODE 	22
ISR_NOERRCODE 	23
ISR_NOERRCODE 	24
ISR_NOERRCODE 	25
ISR_NOERRCODE 	26
ISR_NOERRCODE 	27
ISR_NOERRCODE 	28
ISR_NOERRCODE	  29
ISR_NOERRCODE 	30
ISR_NOERRCODE 	31
ISR_NOERRCODE   128

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

EXTERN FaultHandler ; No longer used??

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
EXTERN ISR_Handler  ; In isr.c
ISR_CommonStub:
    pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    mov ax, ds               ; Lower 16-bits of eax = ds.
    push eax                 ; save the data segment descriptor

    mov ax, 0x10  ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call ISR_Handler

    pop ebx        ; reload the original data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                     ; Pops edi,esi,ebp...
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    sti
    iret

[EXTERN IRQ_Handler]
IRQ_CommonStub:
	PUSHA
	
	MOV AX, DS
	PUSH EAX
	
	MOV AX, 0x10
	MOV DS, AX
	MOV ES, AX
	MOV FS, AX
	MOV GS, AX
	
	CALL IRQ_Handler
	
	POP EBX
	MOV DS, BX
	MOV ES, BX
	MOV FS, BX
	MOV GS, BX
	
	POPA
	ADD ESP, 8
	STI
	IRET
