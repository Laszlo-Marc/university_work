bits 32
global start
import exit msvcrt.dll
extern exit,printf,scanf
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    n db 0
    message1 db "n= ",0
    message db "numar= ",0
    numere times 100 db 0
    format db "%d",0
    
segment code use32 class=code
start:
    push dword message1
    call [printf]
    add esp,4
    
    push dword n
    push dword format
    call [scanf]
    add esp,4*2
    
    mov ecx,0
    mov ecx,[n]
    bucla:
        
        
        
    
    final:
    push dword 0 
    call [exit]