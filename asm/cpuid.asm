[GLOBAL cpuid_supported]
cpuid_supported:
    PUSHFD
    PUSHFD
    XOR DWORD [ESP], 0x00200000
    POPFD
    PUSHFD
    POP EAX
    XOR EAX, [esp]
    POPFD
    AND EAX, 0x00200000
    RET
[GLOBAL cpuid]
cpuid:
    MOV EAX, 0x0
    CPUID
