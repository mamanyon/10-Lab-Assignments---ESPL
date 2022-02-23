section .text
    global Open ;make it transparent to other modules

Open:
    push ebp ; stack maintenance
    push ebx
    mov ebp, esp

get_args:
    mov eax, 5
    mov ebx, 0
    add ebx, [ebp+12]
    mov ecx, 0
    mov edx, 0777
    int 0x80
    mov esp, ebp
    pop ebx
    pop ebp
    ret