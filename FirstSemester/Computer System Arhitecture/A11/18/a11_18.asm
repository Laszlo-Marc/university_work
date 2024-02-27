bits 32 
global start

global format_afisare, format_citire, format_eticheta, file, descriptor, acces, element, contor
extern exit, _print, _determina_pozitive, _determina_negative

import exit msvcrt.dll
segment data use32 class=data
    file db "numbers.txt", 0
    descriptor dd 0
    acces db "r", 0

    format_eticheta db "%s", 0
    format_afisare db "%d ", 0
    format_citire db "%d", 0

    ; etichete
    eticheta_poz db "Positive numbers : ", 0
    eticheta_neg db 13, 10, "Negative numbers : ", 0

    ;numere
    contor dd 0 
    element dd 0
    sir dd 0

;Read from file numbers.txt a string of numbers (positive and negative). Build two strings using readen numbers:
;P – only with positive numbers
;N – only with negative numbers
;Display the strings on the screen.
segment code use32 class=code
    start:
    ;positive numbers
    push sir
    call _determina_pozitive

   
    push eticheta_poz
    push sir
    call _print

    ;negative numbers
    push sir
    call _determina_negative

  
    push eticheta_neg
    push sir
    call _print
    

    _exit_program:
        push    dword 0
        call    [exit]