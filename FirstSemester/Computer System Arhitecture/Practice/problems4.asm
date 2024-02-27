bits 32 
global start
extern exit 
import exit msvcrt.dll  
import printf msvcrt.dll
extern printf
segment data use32 class=data
    a dd 25
    b dd 10
    format db "Quotient=%d, remainder=%d",0
    quotient dd 0
    remainder dd 0

segment code use32 class=code
start:
    mov eax,0
    mov eax,[a]
    mov edx,0
    idiv dword [b]
    
    mov [quotient],eax
    mov [remainder],edx
    
    push dword [remainder]
    push dword [quotient]
    push dword format
    call [printf]
    add esp,4*3
    

    push dword 0 
    call [exit] 