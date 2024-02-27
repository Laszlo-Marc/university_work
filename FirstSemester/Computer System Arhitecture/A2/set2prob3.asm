bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data ;(c+d)-(a+d)+b
      a db 10
      b db 14
      c db 7
      d db 8


segment code use32 class=code
start:
        mov ax,[c]
        add ax,[d]
        mov bx,[a]
        add bx,[d]
        sub ax,bx
        add ax,[b]
        

   
    push dword 0 
    call [exit] 