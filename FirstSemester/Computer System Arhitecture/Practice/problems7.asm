bits 32 
global start
import exit msvcrt.dll
extern exit,scanf,printf
import scanf msvcrt.dll
import printf msvcrt.dll  
segment data use32 class=data
    message1 db "Enter your number: ",0
    format1 db "%d",0
    message2 db "Converted in hexadecimal: %x",0
    
    num db 0
;Read a number in base 10 from the keyboard and display the value of that number in base 16 Example: Read: 28; display: 1C    
segment code use32 class=code
start:
    push dword message1
    call [printf]
    add esp,4
    
    push dword num
    push dword format1
    call [scanf]
    add esp,4*2
    
    push dword [num]
    push dword message2
    call [printf]
    add esp,4*3
    
    push dword 0 
    call [exit] 

