section .text
    global utoa_s ;make it transparent to other modules
utoa_s:
    push ebp ; stack maintenance
    push ebx
    mov ebp, esp

Getting_args:
    mov eax, [ebp+12] ;getting the int
    mov esi, [ebp+16] ; getting the buffer to the string
int_to_string:
   add esi,9
   mov byte [esi],0
   mov ebx,10
.next_digit:
    xor edx,edx         ; Clear edx prior to dividing edx:eax by ebx
    div ebx             ; eax /= 10
    add dl,'0'          ; Convert the remainder to ASCII
    dec esi             ; store characters in reverse order
    mov [esi],dl
    test eax,eax
    jnz .next_digit     ; Repeat until eax==0
    mov eax,esi

    mov esp, ebp
    pop ebx
    pop ebp
    ret