bits 32 
global start
import exit msvcrt.dll
extern exit,scanf,printf
import scanf msvcrt.dll
import printf msvcrt.dll  
segment data use32 class=data
    a db 0
    b dw 0
    message1 db "Input byte: ",0
    message2 db "Input word: ",0
    format1 db "%d",0
    format2 db "%d",0
    result dd 0
    message3 db "YES",0
    message4 db "NO",0
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
    
    mov eax,[b]
   
    
    mov cl, 8 ; Number of bits in a byte
    and eax, 0xff ; Mask the first 8 bits of the word
    cmp eax, [a] ; Compare the byte to the first 8 bits of the word
    je found_consecutive

; Iterate through the remaining bits of the word
    mov ecx, 24 ; Number of bits remaining in the word
check_next:
    shr eax, 8 ; Shift the word 8 bits to the right
    and eax, 0xff ; Mask the next 8 bits of the word
    cmp eax, [a] ; Compare the byte to the next 8 bits of the word
    je found_consecutive
    sub ecx, 8 ; Decrement the number of remaining bits
    jnz check_next

; If the loop completes, the byte is found consecutively in the word
found_consecutive:
    push dword message3
    call [printf]
    add esp,4
    
    jmp final

not_consecutive:
    push dword message4
    call [printf]
    add esp,4
    
   final:
    push dword 0 
    call [exit] 