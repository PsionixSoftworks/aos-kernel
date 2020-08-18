; Load up the Global Descriptor Table:
[GLOBAL GDT_Flush]
GDT_Flush:
	MOV EAX, [ESP + 4]
	LGDT [EAX]

	MOV AX, 0x10
	MOV DS, AX
	MOV ES, AX
	MOV FS, AX
	MOV GS, AX
	MOV SS, AX
	jmp 0x08:.Flush
.Flush:
	RET

; Load up the Interrupt Descriptor Table:
[GLOBAL IDT_Load]
IDT_Load:
	MOV EAX, [ESP + 4]
	LIDT [EAX]
	RET

[GLOBAL TSS_Flush]
TSS_Flush:
	MOV AX, 0x2B


	
	LTR AX
	RET
