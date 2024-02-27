bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data ;(a-b-c)+(a-c-d-d)
      a dw 8
      b dw 10
      c dw 12
      d dw 14


segment code use32 class=code
start:
        mov ax,[a]
        sub ax,[b]
        sub ax,[c]
        mov bx,[a]
        sub bx,[c]
        sub bx,[d]
        sub bx,[d]
        add ax,bx
    push dword 0 
    call [exit] 