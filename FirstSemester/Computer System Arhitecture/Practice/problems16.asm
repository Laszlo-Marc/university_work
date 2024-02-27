bits 32
global start
import exit msvcrt.dll
extern exit,printf,fopen,fclose,fscanf
import printf msvcrt.dll
import fopen msvcrt.dll
import fscanf msvcrt.dll
import fclose msvcrt.dll
segment data use32 class=data
    mode db "r",0
    descriptor db -1
    file_name db "numere.txt",0
    text times 100 db 0
    len equ 100
    format_citire db "%d",0
    doi db 2
    N db 0
    P db 0
    pare db "Suma numerelor pare: %d",0
    impare db "Suma numerelor impare: %d ",0
    nr db 0
segment code use32 class=code
start:
    push dword mode
    push dword file_name
    call [fopen]
    add esp,4*2
    
    mov [descriptor],eax
    cmp eax,-1
    je final
    
    citire:
        push dword nr
        push dword format_citire
        push dword [descriptor]
        call [fscanf]
        add esp,4*3
        
        mov eax,[nr]
        mov edx,0
        div dword [doi]
        
        cmp edx,0
        je par
        jne impar
        cmp byte[nr],' '
        je final
        
    mov ecx,N
    mov ebx,P
  
    par:
       add ecx,[nr]
       jmp citire
       
    impar:
        add ebx,[nr]
        jmp citire
        
        
    
    final:
    push dword [N]
    push dword pare
    call [printf]
    add esp,4*2
    
    push dword [P]
    push dword impare
    call [printf]
    add esp,4*2
    
    push dword [descriptor]
    call [fclose]
    add esp,4
    push dword 0 
    call [exit]