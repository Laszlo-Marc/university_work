;Two byte strings A and B are given. Obtain the string R that contains only the odd positive elements of the two strings

bits 32 
global start
extern exit 
import exit msvcrt.dll  
segment data use32 class=data
    a db 2, 1, 3, -3
    l1 equ $-a
    b db 4, 5, -5, 7
    l2 equ $-b
    r times l1+l2 db 0
segment code use32 class=code
start:
    mov ecx, l1 ;length of a
    mov esi, 0 ; index
    mov edx, 0
    
    jecxz stop 
    repeats:
    
        mov al, [a+esi]
        mov ah, al
        and al, 0000_0001b ;for the parity flag
        
        jpe go
        cmp ah, 0
        jle gonext
        mov [r+edx], ah
        add edx, 1
        go:
        gonext:
        inc esi
        
    loop repeats
    stop:
    
    mov ecx, 0
    mov ecx, l2 ;length of b
    ;keeping the previous index
    mov esi, 0 ; new index
        
    jecxz stopp
    repeatss:
    
        mov al, [b+esi]
        mov ah, al
        and al, 0000_0001b
        
        jpe goo
        cmp ah, 0
        jle gonextt
        mov [r+edx], ah
        add edx, 1
        goo:
        gonextt:
        inc esi 
        
    loop repeatss
    stopp:
    
    push dword 0 
    call [exit] 
