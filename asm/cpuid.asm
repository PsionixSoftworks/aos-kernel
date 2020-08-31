[GLOBAL cpuid_supported]
cpuid_supported:
    pushfd
    pushfd
    xor dword [esp], 0x00200000
    popfd
    pushfd
    pop eax
    xor eax, [esp]
    popfd
    and eax, 0x00200000
    ret
[GLOBAL cpuid]
cpuid:
    mov eax, 0x0
    cpuid
