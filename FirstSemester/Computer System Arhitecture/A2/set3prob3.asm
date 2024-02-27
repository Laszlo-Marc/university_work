bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data ;[-1+d-2*(b+1)]/a
      a db 8
      b db 10
      d dw 10
      
      

segment code use32 class=code
start:
        mov al,[b]
        add al,1
        mov ah,2
        mul ah
        sub al,1
        add al,[d]
        mov ah,[a]
        div BYTE [a]
    push dword 0 
    call [exit] 