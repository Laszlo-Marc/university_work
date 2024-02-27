bits 32 
global start
extern exit 
import exit msvcrt.dll  
import printf msvcrt.dll
import scanf msvcrt.dll
extern printf,scanf
segment data use32 class=data
    a db 0
    b db 0
    format1 db "%d",0
    message1 db "a=",0
    format2 db "%d",0
    message2 db "b=",0
    result dd 0
    format3 db "Result: %d",0
;Read two numbers a and b (base 10) from the keyboard and calculate: (a+b)/(a-b). The quotient will be stored in a variable called "result" (defined in the data segment). The values are considered in signed representation.
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
    mov ebx,0
    mov al, [a]
    add al,[b]
    mov ah,0
    mov dx,0
    mov bl,[a]
    sub bl,[b]
    mov bh,0
    div bx
    
    mov [result],ax
    
    push dword [result]
    push dword format3
    call [printf]
    add esp,2*4
    
    push dword 0 
    call [exit] 