[global cpuid_supported]
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
[global cpuid_get_property]
cpuid_get_property:
    mov eax, [esp + 4]
    cpuid
