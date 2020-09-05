; Load up the Global Descriptor Table:
[GLOBAL gdt_flush]
gdt_flush:
	MOV EAX, [ESP + 4]
	LGDT [EAX]

	MOV AX, 0x10
	MOV DS, AX
	MOV ES, AX
	MOV FS, AX
	MOV GS, AX
	MOV SS, AX
	jmp 0x08:.flush
.flush:
	RET

; Load up the Interrupt Descriptor Table:
[GLOBAL idt_flush]
idt_flush:
	MOV EAX, [ESP + 4]
	LIDT [EAX]
	RET

; Load up the Task State Segment:
[GLOBAL tss_flush]
tss_flush:
    MOV AX, 0x2B

    LTR AX
    RET