bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data ;(e+f)*g
      e dw 10
      f dw 12
      g dw 2
      
      

segment code use32 class=code
start:
       mov ax,[e]
       add ax,[f]
       mov bx,[g]
       mul bx
        
    push dword 0 
    call [exit] 