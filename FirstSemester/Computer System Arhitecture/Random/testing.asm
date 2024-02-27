bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
;A string of doublewords is given. Order in increasing order the string of the high words (most significant) from these doublewords. The low words (least significant) remain unchanged.
segment data use32 class=data
   
    
    
; our code starts here
segment code use32 class=code
    start:
        mov ax,65535
        mov bl,10
        idiv bl 
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program