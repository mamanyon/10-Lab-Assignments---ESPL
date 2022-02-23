section .data
    fd: dd 0
    msg: db " is the number of time the substring appears in the file", 10
    msg1: db "Hello"
section .bss
    buffer: resb 64
    len: resb 4
section .text
global _printws
extern utoa_s
extern openw
extern cmpstr
extern strlen
extern writew

_printws:
    push ebp
    push ebx
    mov ebp, esp
    xor esi, esi; clean
    mov esi, [ebp+12] ;now the desired substring is saved in esi
    mov ebx, [ebp+16] ; filename in ebx
    push 0
    push ebx
    call openw; for open
    pop edx
    pop edx
    mov [fd], eax; save the fd
    xor ecx, ecx ; resetting our counter
    mov edx, -1

.findlen:
    push esi
    call strlen
    mov [len], eax
    pop esi

reading_loop:
    inc edx ;incrementing file index
    push edx ;for lseek
    call _seek ;set file index
    pop edx
.read: ; continue of the loop
    push buffer ;len chars will be inserted to buffer
    call readws
    cmp eax, 0 ;if we reached eof
    je exit
    push esi ;pushing our sub for strcmp
    call cmpstr ;comparing what we read with our sub
    pop esi
    pop edi
    cmp eax, 0 ;if they are equal we have 0 in eax
    je .inc
    jmp reading_loop


.inc:
    inc ecx
    jmp reading_loop

readws:
    push ebp ; stack maintenance
    push ebx
    push ecx
    push edx
    mov ebp, esp

    mov eax, 3
    mov ebx, [fd]
    mov ecx, [ebp+20] ;buffer to which we want to insert char
    mov edx, [len] ;how much we r reading
    jmp finishws

_seek:
    push ebp ; stack maintenance
    push ebx
    push ecx
    push edx
    mov ebp, esp
    mov ebx, [fd]
    mov ecx,[ebp+20] ;how much we are indexing
    mov edx, 0 ;start from beginning
    mov eax, 19 ;opcode for lseek

finishws:
    int 0x80
    mov esp, ebp
    pop edx
    pop ecx
    pop ebx
    pop ebp
    ret

exit:
    call close ;closing file
    push buffer ;for utoa_S
    push ecx ;counter
    call utoa_s ;translating counter to string and storing it in buffer
    pop edx ;pop counter
    pop edx ; pop buffer
    push eax ;utoa STR
    call strlen ;putting strlen in eax
    pop edx ; we have utoa STR in edx
    push eax ;pushing strlen
    push edx ;pushing utoa STR
    call writew ;printing UTOA STR
    pop eax
    pop edx
    push 57
    push msg
    call writew
    mov esp, ebp
    pop ebx
    pop ebp
    ret



test_print:
    push ebp ; stack maintenance
    push ebx
    push ecx
    push edx
    mov ebp, esp

    mov eax, 4 ; opcode for write
    mov ebx, 1 ; write to stdout
    mov ecx, msg1 ; buffer
    mov edx, 6 ; how many chars
    int 0x80
    mov esp, ebp
    pop edx
    pop ecx
    pop ebx
    pop ebp
    ret

close:
    push ebp ; stack maintenance
    push ebx
    push ecx
    push edx
    mov ebp, esp
    mov eax, 6 ; opcode for close
    mov ebx, [fd] ; fs we want to close
    jmp finishws