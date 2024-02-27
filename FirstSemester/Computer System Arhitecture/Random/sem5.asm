bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    sir dd 12ab5678h, 1256abcdh, 12344344h
    len_sir equ ($ - sir) / 4

; our code starts here
segment code use32 class=code
    start:
        ; initialize the loop variables
        mov bx, 0
        cld
        mov esi, sir
        mov ecx, len_sir - 1
        
        ; begin the outer loop
        first_loop:
            ; initialize the inner loop variables
            mov edi, esi
            mov ebx, 0
            
            ; begin the inner loop
            second_loop:
                ; load the next doubleword from the array
                lodsd
                
                ; rotate the doubleword to move the high word to the low word position
                rol eax, 16
                
                ; compare the current doubleword's low word to the next doubleword's low word
                cmp dx, ax
                
                ; if the current doubleword's low word is greater than the next doubleword's low word,
                ; swap the two doublewords
                jb swap
                
                ; if the current doubleword's low word is equal to or less than the next doubleword's low word,
                ; continue to the next iteration of the loop
                jmp no_swap
                
                ; define the "swap" label, which is called when the two doublewords need to be swapped
                swap:
                    xchg dx, ax
                    mov ebx, 1
                    jmp no_swap
                    
                ; define the "no_swap" label, which is called when the two doublewords do not need to be swapped
                no_swap:
                    rol eax, 16
                    mov edi, esi
                    sub edi, 8
                    
                    ; store the doublewords back in the array
                    xchg edx, eax
                    stosd
                    mov eax, edx
                    stosd
                    
                    sub esi, 4
                    
                    ; continue to the next iteration of the inner loop
                    loop second_loop
                    
            ; check if any swaps were made in the inner loop
            cmp ebx, 0
            
            ; if any swaps were made, continue to the next iteration of the outer loop
            jnz first_loop
            
        ; push the parameter for exit onto the stack
        push    dword 0
        
        ; call exit to terminate the program
        call    [exit]