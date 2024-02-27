bits 32 
global start
import exit msvcrt.dll
extern exit,scanf,printf
import scanf msvcrt.dll
import printf msvcrt.dll  
segment data use32 class=data
    a db 0
    b db 0
    message1 db "a=",0
    message2 db "b=",0
    format1 db "%d",0
    format2 db "%d",0
    result dd 0
    message3 db "Result: %d",0
segment code use32 class=code
start:
    push dword message1
    call [printf]
    add esp,4
     
    push dword a 
    push dword format1
    call [scanf]
    add esp,4*2
    
    push dword message2
    call [printf]
    add esp,4
     
    push dword b
    push dword format2
    call [scanf]
    add esp,4*2
    
    mov eax,0
    mov al,[a]
    add al,[b]
    mov ebx,0
    mov bl,[a]
    sub bl,[b]
    mul bl
    mov [result],ax
    
    push dword [result]
    push dword message3
    call [printf]
    add esp,4*2
    
    push dword 0 
    call [exit] 