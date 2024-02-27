bits 32 
global start
extern exit 
import exit msvcrt.dll  
import printf msvcrt.dll
extern printf
segment data use32 class=data
    format db "%d * %d = %d",0
    a dd 2
    b dd 5
    

segment code use32 class=code
start:
    mov eax,0
    mov eax,[b]
    mul dword[a]
    
    push eax 
    push dword [a]
    push dword [b]
    push dword format
    call [printf]
    add esp,4*4
    
    

    push dword 0 
    call [exit] 