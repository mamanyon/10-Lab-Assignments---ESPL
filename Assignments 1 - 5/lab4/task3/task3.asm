%define X 'A'
%define STR string1

section .rodata
    print_format db '"%c" appears in "%s" %d times', 10, 0
    string1 db 'ABBA', 0
    string2 db 'BBA', 0
    string3 db 'BB', 0
    string4 db '', 0

section .text
    global _start
    extern printf

_start:
    mov ecx, -1
    mov eax, 0
    jmp count

count:
    inc ecx
    mov ebx, ecx
    add ebx, STR
    movzx	ebx, BYTE [ebx] ; get next char
    test bl,bl
    jne compare

zero:
    jmp print

compare:
    cmp ebx, X
    jne count
    inc eax
    jmp count

print:
    sub  esp, 4
    push eax
    push STR
    push X
    push print_format
    call printf
    add esp, 16

exit:
    mov ebx, 0
    mov eax, 1
    int 80h
