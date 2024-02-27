bits 32 
global start
extern exit 
import exit msvcrt.dll  
import scanf msvcrt.dll
import printf msvcrt.dll
extern printf,scanf

segment data use32 class=data
    message1 db "a=",0
    message2 db "b=",0
    format1 db  "%i",0
    format2 db "%i",0
    format3 db "Result: %d",0
    a db 0
    b db 0
    result db 0


;Read two numbers a and b (in base 10) from the keyboard and calculate a/b. This value will be stored in a variable called "result" (defined in the data segment). The values are considered in signed representation.
segment code use32 class=code
start:
    push dword message1
    call [printf]
    add esp,4
    
    push dword a
    push dword format1
    call [scanf]
    add esp, 4*2
    
    push dword message2
    call [printf]
    add esp,4
    
    push dword b
    push dword format2
    call [scanf]
    add esp,4*2
    
    mov eax,0
    mov eax,[a]
    idiv dword [b]
    mov [result],eax  
    
    push dword [result]
    push dword format3
    call [printf]
    add esp,4*2
    
    push dword 0 
    call [exit] 

