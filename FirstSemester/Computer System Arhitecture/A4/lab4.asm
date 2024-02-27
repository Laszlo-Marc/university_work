bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data
      a dw 0111011101010111b
      b dw 1001101110111110b
      c dd 0


segment code use32 class=code 
start:
     mov bx,0;the bits 0-2 of C are the same as the bits 12-14 of A
     mov ax,[a]
     and ax,0111000000000000b
     mov cl,12
     ror ax,cl
     or bx,ax; in bx pe 0-2 sunt biti de pe 12-14 a lui A
     
     mov ax,0;the bits 3-8 of C are the same as the bits 0-5 of B
     mov ax,[b]
     and ax,0000000000111111b
     mov cl,3
     rol ax,cl
     or bx,ax;in bx sunt primele 2 cerinte
     
     mov ax,0;the bits 9-15 of C are the same as the bits 3-9 of A
     mov ax,[a]
     and ax,0000001111111000b
     mov cl,6
     rol ax,cl
     or bx,ax; bx= 1101010111110111
     
     mov eax,0
     mov ax,[a]
     mov cl,16
     shl eax, cl;eax=a
     or ebx,eax
     
     
     
    push dword 0 
    call [exit] 