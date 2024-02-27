bits 32
extern printf, scanf
import printf msvcrt.dll
import scanf msvcrt.dll

extern fopen, fclose
import fopen msvcrt.dll
import fclose msvcrt.dll

extern fprintf, fscanf    
import fprintf msvcrt.dll
import fscanf msvcrt.dll

global _print, _determina_pozitive, _determina_negative
extern format_afisare, format_citire, format_eticheta, file, descriptor, acces, element, contor

segment code use32 class=code
_print:
    
    mov eax, [esp+8]
    push eax
    push format_eticheta
    call [printf]
    add esp, 2*4

    
    cld
    mov ebx, [contor]
    .for:

        lodsd 
        cmp ebx, 0 
        jz .final

        push eax
        push format_afisare
        call [printf]
        add esp, 2*4

        dec ebx
    jmp .for


    .final:
        ret

_determina_pozitive:
    ; open file
    push acces
    push file
    call [fopen]
    add esp, 2*4 

    mov [descriptor], eax 

    ;adresa a unui sir de numere (dd) pe stiva
    mov edi, [esp+4]
    cld
    xor ebx, ebx

    .for:
        push element
        push format_citire
        push dword [descriptor]
        call [fscanf]
        add esp, 3*4

        cmp eax, -1 ; end of string
        jz .final

        mov eax, [element]
        cmp eax, 0
        jl .final_for 

        stosd 
        inc ebx

        .final_for:
    jmp .for


    .final:
        mov [contor], ebx 
        ret

_determina_negative:
    ; open file
    push acces
    push file
    call [fopen]
    add esp, 2*4 

    mov [descriptor], eax 

    
    mov edi, [esp+4]
    cld
    xor ebx, ebx

    .for:
        push element
        push format_citire
        push dword [descriptor]
        call [fscanf]
        add esp, 3*4

        cmp eax, -1 
        jz .final

        mov eax, [element]
        cmp eax, 0
        jge .final_for 

        stosd 
        inc ebx

        .final_for:
    jmp .for


    .final:
        mov [contor], ebx 
        ret