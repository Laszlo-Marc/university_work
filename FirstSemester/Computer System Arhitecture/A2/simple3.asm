bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data
      a dw 128
      b dw 128


segment code use32 class=code
start:
        mov ax,[a]
        add ax,[b]

   
    push dword 0 
    call [exit] 