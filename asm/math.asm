section .text

global _cos
global __cos
global _sin
global __sin
global _tan
global __tan

_cos:
__cos:
    push ebp
    mov ebp, esp
    fld qword [ebp + 8]
    fcos

    pop ebp
    ret

_sin:
__sin:
    push ebp
    mov ebp, esp
    fld qword [ebp + 8]
    fsin

    pop ebp
    ret

_tan:
__tan:
    push ebp
    mov ebp, esp
    sub esp, 4
    fld qword [ebp + 8]
    fptan
    fstp dword [ebp - 4]
    mov esp, ebp

    pop ebp
    ret
