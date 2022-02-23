section .text
	
global _start
global read
global write
global open
global close
global strlen

extern main
_start:

	;TODO: handles command line input parameters
    mov eax,[esp]
    mov ebx, esp
    add ebx,4
    push ebx
    push eax
	call	main
    mov     ebx,eax
	mov	eax,1
	int 0x80

read:
    push ebp ; stack maintenance
    push ebx
    mov ebp, esp

    mov eax, 3
    mov ebx, [ebp+12]
    mov ecx, [ebp+16]
    mov edx, [ebp+20]
    jmp finish

write:
    push ebp ; stack maintenance
    push ebx
    mov ebp, esp

    mov eax, 4
    mov ebx, [ebp+12]
    mov ecx, [ebp+16]
    mov edx, [ebp+20]
    jmp finish
open:
    push ebp ; stack maintenance
    push ebx
    mov ebp, esp

    mov eax, 5
    mov ebx, [ebp+12]
    mov ecx, [ebp+16]
    mov edx, 0777
    jmp finish
close:
    push ebp ; stack maintenance
    push ebx
    mov ebp, esp

    mov eax, 6
    mov ebx, [ebp+12]
    jmp finish

strlen:
    push	ebp
    push	ebx
    mov	ebp, esp
    mov	eax,-1

.L2:
    add eax, 1
    mov ebx, eax
    add ebx, [ebp+12]
    movzx	ebx, BYTE [ebx]
    test bl,bl
    jne .L2
    mov esp, ebp
    pop ebx
    pop ebp
    ret

finish:
    int 0x80
    mov esp, ebp
    pop ebx
    pop ebp
    ret
