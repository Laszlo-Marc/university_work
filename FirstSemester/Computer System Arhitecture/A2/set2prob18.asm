bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data ;d-(a+b)+c
      a db 10
      b db 14
      c db 7
      d db 8


segment code use32 class=code
start:
        mov bx,[a]
        add bx,[b]
        mov ax,[d]
        sub ax,bx
        add ax,[c]
        

   
    push dword 0 
    call [exit] 