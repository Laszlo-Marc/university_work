bits 32 
global start
import exit msvcrt.dll
extern exit,scanf,printf
import scanf msvcrt.dll
import printf msvcrt.dll  
segment data use32 class=data
    message1 db "a=",0
    message2 db "b=",0
    format1 db "%d",0
    format2 db "%d",0
    format3 db "Result: %d",0
    a db 0
    b db 0
    result db 0
;Read two numbers a and b (in base 10) from the keyboard and calculate their product. This value will be stored in a variable called "result" (defined in the data segment).
segment code use32 class=code
start:
    push dword message1
    call [printf]
    add esp,4*1
    
    push dword a
    push dword format1
    call [scanf]
    add esp,4*2
    
    push dword message2
    call [printf]
    add esp,4*1
    
    push dword b
    push dword format2
    call [scanf]
    add esp,4*2
    
    mov eax,0
    mov ebx,0
    
    mov al,[a]
    mov bl,[b]
    mul bl
    mov [result],al
    
    push dword [result]
    push dword format3
    call [printf]
    add esp,4*2


    push dword 0 
    call [exit] 

