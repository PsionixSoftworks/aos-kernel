[GLOBAL read_PIT_count]
read_PIT_count:
    PUSHFD
    CLI
    MOV AL, 00000000b
    OUT 0x43, AL

    IN AL, 0x40
    MOV AH, AL
    IN AL, 0x40
    ROL AX, 8
    POPFD
    RET
