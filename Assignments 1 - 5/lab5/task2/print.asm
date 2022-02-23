section .data
    fd: dd 0
section .bss
    buffer: resb 64
section .text

global _print
global read
global write
global open
global close

_print:
    push ebp ; stack maintenance
    push ebx ; stack maintenance
    mov ebp, esp ; set pointer
    mov ebx, [ebp + 12] ; pointer to filename in ebx
    push 0 ; read only
    push ebx ; filename for open
	call open ; in eax we have fd
	pop edx ; popping filename
	pop edx ; popping read only '0'
	mov [fd], eax ; inset fd to fd
.L2:
    push 1 ;reading 1 char
    push buffer ; buffer
    call read ; reading 1 char
    pop edx ; popping buffer
    pop edx ; popping 1
    cmp eax, 0 ; EOF?
    je _exit ; if we finished, exit
    push buffer ;buffer we want to write from
    call write
    pop edx
    jmp .L2

read:
    push ebp ; stack maintenance
    push ebx
    mov ebp, esp

    mov eax, 3 ; opcode read
    mov ebx, [fd] ; fd
    mov ecx, [ebp+12] ;buffer to which we want to insert char
    mov edx, [ebp+16] ;how much we r reading
    jmp finish

write:
    push ebp ; stack maintenance
    push ebx
    mov ebp, esp

    mov eax, 4 ; opcode for write
    mov ebx, 1 ; write to stdout
    mov ecx, [ebp+12] ; buffer
    mov edx, 1 ; how many chars
    jmp finish
open:
    push ebp ; stack maintenance
    push ebx
    mov ebp, esp
    mov eax, 5
    mov ebx, [ebp+12] ; filename
    mov ecx, [ebp+16] ; readonly(0)
    mov edx, 0777 ; file permissions
    jmp finish
close:
    push ebp ; stack maintenance
    push ebx
    mov ebp, esp

    mov eax, 6 ; opcode for close
    mov ebx, [fd] ; fs we want to close
    jmp finish

finish:
    int 0x80
    mov esp, ebp
    pop ebx
    pop ebp
    ret

_exit:
    call close
    mov esp, ebp
    pop ebx
    pop ebp
    ret
