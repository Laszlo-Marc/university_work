bits 32 
global start
extern exit 
import exit msvcrt.dll  
segment data use32 class=data
    a db 2
    b db 5
    d db 4
    c dd 3
    x dq 10


segment code use32 class=code
start: ;(8-a*b*100+c)/d+x; a,b,d-byte; c-doubleword; x-qword
    mov eax,0
    mov al,8
    cbw
    cwde
    mov ebx,0
    mov cl,[b]
    mov bl,[a]
    imul cl
    sub eax,ebx
    
    
    push dword 0 
    call [exit] 