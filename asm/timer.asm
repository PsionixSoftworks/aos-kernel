[GLOBAL read_PIT_count]
read_PIT_count:
    pushfd
    cli
    mov al, 00000000b
    out 0x43, al

    in al, 0x40
    mov ah, al
    in al, 0x40
    rol ax, 8
    popfd
    ret
