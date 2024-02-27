bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data
      a dw 0111011101010111b
      b dd 0
      


segment code use32 class=code 
start:
;the bits 0-3 of B have the value 0
     mov bx,0;the bits 4-7 of B are the same as the bits 8-11 of A
     mov ax,[a]
     and ax,0000111100000000b
     mov cl,4
     ror ax,cl
     or bx,ax
     
     mov ax,0;the bits 8-9 and 10-11 of B are the invert of the bits 0-1 of A (so 2 times) ;
     mov ax,[b]
     and ax,0000000000111111b
     mov cl,3
     rol ax,cl
     or bx,ax
     
     mov ax,0;the bits 12-15 of B have the value 1
     mov ax,1111000000000000b
     and bx,ax
     
     mov eax,0;the bits 16-31 of B are the same as the bits 0-15 of B
     mov ax,[b]
     mov cl,16
     shl eax, cl;eax=a
     or ebx,eax
     
     
     
    push dword 0 
    call [exit] 