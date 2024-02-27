bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data ;200-[3*(c+b-d/a)-300]
      a db 2
      b db 10
      c db 12
      d dw 10
      
      

segment code use32 class=code
start:
        mov ax,[d]
        div byte[a]
        mov bl,[c]
        add bl,[b]
        sub al,bl
        mov dl,3
        mul dl
        sub al,300
        mov bl,200
        sub bl,al
        
        
    push dword 0 
    call [exit] 