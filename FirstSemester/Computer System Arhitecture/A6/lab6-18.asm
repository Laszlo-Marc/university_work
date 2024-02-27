bits 32
global start
extern exit
import exit msvcrt.dll
segment data use32 class=data
    sir dd 12ab5678h, 1256abcdh, 12344344h
    len_sir equ ($ - sir) / 4
    
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
            
    push dword 0
    call [exit]