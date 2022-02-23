section .text
    global atou_s ;make it transparent to other modules

atou_s:
    push ebp ; stack maintenance
    push ebx
    mov ebp, esp
    mov ecx, -1
    mov eax, 0

next_char:
    add ecx, 1
    mov ebx, ecx
    add ebx, [ebp+12]
    movzx ebx, byte [ebx] ; get next char

check_zero:
    test bl, bl
    jne .L2
    mov esp, ebp
    pop ebx
    pop ebp
    ret

.L2:
    imul eax, 10
    sub ebx, '0'
    add eax, ebx
    jmp next_char