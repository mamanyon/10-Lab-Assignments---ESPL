section .text
	global cmpstr ;make cmpstr transparent to other modules

cmpstr:
	push ebp ;stack maintenance
	push ebx
	mov ebp, esp ;stack maintenance
    mov ecx, -1

incr:
    add ecx, 1
    mov ebx, ecx
    mov eax, ecx
    add eax, [ebp+12]
    add ebx, [ebp+16]
    movzx	ebx, BYTE [ebx] ;get next char in s2
    movzx	eax, BYTE [eax] ; get next char in s1

check_zero:
    mov edx, ecx
    add edx, [ebp+12]
    movzx	edx, BYTE [edx]
    test dl, dl
    je not_equal //we reached zero bit in s1, so we can end now by substracting
    mov edx, ecx
    add edx, [ebp+16]
    movzx	edx, BYTE [edx]
    test dl, dl
    je not_equal //we reached zero bit in s2, so we can end now by substracting

compare:
	cmp eax, ebx ;comparing the two chars
	jne not_equal ;bits are not equal, we can end now by substracting
	jmp incr ;bits are equal, we need to iterate to the next char

not_equal:
	sub eax, ebx ;stores the difference in eax
	jmp FINISH
	
FINISH:
	mov esp, ebp ;stack maintenance
	pop ebx
	pop ebp ;stack maintenance
	ret ;stack maintenance