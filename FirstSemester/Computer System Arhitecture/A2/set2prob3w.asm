bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data ;(b+b+d)-(c+a)
      a dw 8
      b dw 10
      c dw 12
      d dw 14


segment code use32 class=code
start:
        mov ax,[b]
        add ax,[b]
        add ax,[d]
        mov bx,[c]
        add bx,[a]
        sub ax,bx
    push dword 0 
    call [exit] 