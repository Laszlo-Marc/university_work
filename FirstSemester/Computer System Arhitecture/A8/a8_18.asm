bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               
import exit msvcrt.dll    
extern scanf
extern printf
import scanf msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 0
    b dd 0
    one db "%d",0
    two db "%x",0
    message db "The number of 1's in the sum is %d", 10, 0  
    message1 db "a=",0
    message2 db "b=",0
;Read a decimal number and a hexadecimal number from the keyboard. Display the number of 1's of the sum of the two numbers in decimal format. Example:
;a = 32 = 0010 0000b
;b = 1Ah = 0001 1010b
;32 + 1Ah = 0011 1010b
;The value printed on the screen will be 4
segment code use32 class=code
start:
    
    push dword message1
    call [printf]
    add esp, 4*1

    push dword a
    push one
    call [scanf]
    add esp, 8

    push dword message2
    call [printf]
    add esp, 4*1

    push dword b
    push two
    call [scanf]
    add esp, 8

    mov eax, [a]
    add eax, [b]
    mov ecx, 0

   count_ones:
    cmp eax, 0
    je final
    shr eax, 1
    jc addc
    jmp count_ones
   addc:
    add ecx,1
    jmp count_ones

   final:
    push ecx
    push message
    call [printf]
    add esp, 8

    
    push dword 0
    call [exit]
