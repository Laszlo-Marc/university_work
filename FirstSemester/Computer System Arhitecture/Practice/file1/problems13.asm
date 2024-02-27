bits 32
global start
import exit msvcrt.dll
extern exit,printf
import printf msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
extern fread,fopen ,fclose
segment data use32 class=data
    file_name db "letters.txt",0
    acces_mode db "r",0
    file_descriptor dd -1
    count resd 1
    len equ 100
    text times len db 0
    message db "Number of vowels: %d",0
    error db "File Error",0
segment code use32 class=code
start:
    push dword acces_mode
    push dword file_name
    call [fopen]
    add esp,4*2
    
    mov [file_descriptor],eax
    
    cmp eax,0
    je final
    
    push dword [file_descriptor]
    push dword len
    push dword 1
    push dword text        
    call [fread]
    add esp, 4*4
    mov ecx,text
    mov edx,text+len
    mov eax,0
    vowel_count:
    cmp ecx,edx
    jae done
    mov al,[ecx]
    cmp al,'a'
    je increment
    cmp al,'e'
    je increment
    cmp al,'i'
    je increment
    cmp al,'o'
    je increment
    cmp al,'u'
    je increment
    
    increment:
        inc eax
     next:
        inc ecx
        cmp ecx,edx
        jl vowel_count
    
    done:    
    push eax
    push dword message
    call [printf]
    add esp, 4*2
    push dword [file_descriptor]
    call [fclose]
    add esp, 4
    
    final:
    
    push dword 0 
    call [exit] 