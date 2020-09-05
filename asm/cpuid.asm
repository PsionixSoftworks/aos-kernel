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
[GLOBAL cpuid_get_property]
cpuid_get_property:
    MOV EAX, [ESP + 4]
    CPUID
