section .data
    flag1 db '-w'
    flag2 db '-ws'
section .text

    global _start
    extern cmpstr
    extern _print
    extern write
    extern _printw
    extern _printws
    extern _lseek

_start:
    pop ebx
    cmp ebx, 3
    je w
    jg ws
    jmp none

w:
    pop ebx ;popping argv[0]
    pop ebx ; popping argv[1]("-w")
    call _printw
    mov eax,1
    int 0x80

ws:
    pop ebx ;popping argv[0]
    pop ebx ; popping [1]("-ws"), now argv[2] and argv[3] are in the stack
    call _printws
    mov eax,1
    int 0x80



none:
    pop ebx
    call _print
    mov	eax,1
    int 0x80
