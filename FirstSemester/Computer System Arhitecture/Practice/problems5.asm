bits 32 
global start
extern exit 
import exit msvcrt.dll  
import printf msvcrt.dll
import scanf msvcrt.dll
extern printf,scanf
segment data use32 class=data
    a dd 20
    b dd 0
    message db "b=",0
    format1 db "%d",0
    message2 db "Result: %d ",0
    result dd 0
;A natural number a (a: dword, defined in the data segment) is given. Read a natural number b from the keyboard and calculate: a + a/b. Display the result of this operation. The values will be displayed in decimal format (base 10) with sign.
segment code use32 class=code
start:
    push dword message
    call [printf]
    add esp,4
    
    push dword b
    push dword format1
    call [scanf]
    add esp,4*2
    
    mov eax,0
    mov al,[a]
    mov ah,0
    mov dx,0
    div word [b]
    add ax,[a]
    
    mov [result],ax
    
    push dword [result]
    push dword message2
    call [printf]
    add esp, 4*2
    
    push dword 0 
    call [exit] 