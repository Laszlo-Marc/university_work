;Two byte strings S1 and S2 are given. Obtain the string D by concatenating the elements of S1 from the left hand side to the right hand side and the elements of S2 from the right hand side to the left hand side.
bits 32 
global start
extern exit 
import exit msvcrt.dll  
segment data use32 class=data
    s1 db 1, 2, 3, 4
    l1 equ $-s1
    s2 db 5, 6, 7
    l2 equ $-s2
    d times l1+l2 db 0
segment code use32 class=code
start:
    mov ecx,l1
    mov esi,s1
    mov edi,d
    cld
    jecxz stop 
    ;parcurgem s1
    repeats1:
       mov bl,[esi]
       mov al,[esi]
       mov [edi],bl
       inc edi
       nexts1:
            inc esi
            loop repeats1
    stop:
    
    ;parcurgem s2
    mov ecx,l2
    ;mov esi,0
    cld
    jecxz stop2 
    repeats2:
       mov eax,ecx
       mov bl,[s2+eax-1]
       ;mov al,[s2]
       mov [edi],bl
       inc edi
       nexts2:
            
            loop repeats2
    stop2:
    
    push dword 0 
    call [exit] 
