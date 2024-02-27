bits 32
global start
import exit msvcrt.dll
extern exit,scanf,printf
import scanf msvcrt.dll
import printf msvcrt.dll  
segment data use32 class=data
    a dw 0
    b dw 0
    message1 db "a= ",0
    message2 db "b= ",0
    format1 db "%d",0
    format2 db "%d",0
    c dd 0
    output db "c = %x",0
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
    mov ax,[a]
    sub ax,[b]
    shl eax,16
    mov ax,[a]
    add ax,[b]
    mov [c],eax
    
    push dword [c]
    push dword output
    call [printf]
    add esp,4*2
    
    push dword 0 
    call [exit] 