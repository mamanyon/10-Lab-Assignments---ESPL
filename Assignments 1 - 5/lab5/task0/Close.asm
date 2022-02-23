section .text
    global Close ;make it transparent to other modules

Close:
    push ebp ; stack maintenance
    push ebx
    mov ebp, esp

get_args:
    mov eax, 6
    mov ebx, 0
    add ebx, [ebp+12]
    int 0x80
    mov esp, ebp
    pop ebx
    pop ebp
    ret