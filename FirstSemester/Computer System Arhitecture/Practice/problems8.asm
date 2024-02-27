bits 32 
global start
import exit msvcrt.dll
extern exit,scanf,printf
import scanf msvcrt.dll
import printf msvcrt.dll  
segment data use32 class=data
    a db 0
    message db "a = %d(base 10), a = %x(base 16)",0
    message2 db "Enter a negative number: ",0
    format db "%d",0
;Read a number in base 10 from the keyboard and display the value of that number in base 16 Example: Read: 28; display: 1C    
segment code use32 class=code
start:
    push dword message2
    call [printf]
    add esp,4
    
    push dword a
    push dword format
    call [scanf]
    add esp, 4*2
    
    push dword[a]
    push dword message
    call [printf]
    add esp,4*3
    
    
    push dword 0 
    call [exit] 

