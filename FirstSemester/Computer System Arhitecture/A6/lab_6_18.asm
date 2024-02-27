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
    sir dd 12ab5678h, 1256abcdh, 12344344h
    len_sir equ ($ - sir) / 4
    
; our code starts here
segment code use32 class=code
    start:
        first_loop:
            mov bx, 0
            cld
            mov esi, sir
            mov ecx, len_sir - 1
            
            second_loop:
            lodsd
            rol eax, 16
            mov edx, eax
            
            lodsd
            rol eax, 16
            
            cmp dx, ax
            
            jbe no_swap
            
            xchg dx, ax
            mov bx, 1
            
            no_swap:
            rol edx, 16
            rol eax, 16
            mov edi, esi
            sub edi, 8
            
            xchg edx, eax
            stosd
            mov eax, edx
            stosd
            
            sub esi, 4
            
            loop second_loop
         
        cmp bx, 0
        jnz first_loop
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program