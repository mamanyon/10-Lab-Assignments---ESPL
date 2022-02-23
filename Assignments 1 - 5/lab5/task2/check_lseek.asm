section .data
    fd: dd 0
section .bss
    buffer: resb 64

section .text:
    global _lseek
    extern openw

_lseek:
    push ebp
    push ebx
    mov ebp, esp
    mov ebx, [ebp+12] ;filename
    push 0
    push ebx
    call	openw
    pop edx
    pop edx
    mov [fd], eax
    xor ecx, ecx ; reseting our counter


_seek:
    mov ebx, [fd]
    mov ecx,24
    mov edx, 0
    mov eax, 19
    int 0x80
    push 4
    push buffer
    call readw
    pop edx
    pop edx
    xor edx, edx
    cmp eax, 0
    je exit_
    movzx edx , byte [buffer]
    cmp edx, 10
    je exit_
    jmp _seek


readw:
  push ebp ; stack maintenance
  push ebx
  push ecx
  mov ebp, esp

  mov eax, 3
  mov ebx, [fd]
  mov ecx, [ebp+16] ; buffer
  mov edx, [ebp+20] ;how much we r reading
  jmp finishw

finishw:
  int 0x80
  mov esp, ebp
  pop ecx
  pop ebx
  pop ebp
  ret

exit_:
    mov eax, 1
    int 0x80