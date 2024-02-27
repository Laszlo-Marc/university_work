bits 32
global start
import exit msvcrt.dll
extern exit,scanf,printf
import scanf msvcrt.dll
import printf msvcrt.dll  
segment data use32 class=data
    a dd 0
    b dd 0
    message1 db "Input doubleword: ",0
    message2 db "Input doubleword: ",0
    format1 db "%x",0
    format2 db "%x",0
    result1 dd 0
    result2 dd 0
    output1 db "sum = %x  ",0
    output2 db "difference= %x",0
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
    mov eax,[a]
    mov ebx,[b]
    sub ax,bx
    mov [result1],ax
    push dword [result1]
    push dword output1
    call [printf]
    add esp,4*2
    
    mov eax,[a]
    mov ebx,[b]
    
    shr eax,16
    shr ebx,16
  
    
    sub eax,ebx
    mov [result2],eax
   
    push dword [result2]
    push dword output2
    call [printf]
    add esp,4*2
    
    push dword 0 
    call [exit] 