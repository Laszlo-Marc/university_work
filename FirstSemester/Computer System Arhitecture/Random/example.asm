bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data
      a dw 5
      b dw -9


segment code use32 class=code
start:
   

   
    push dword 0 
    call [exit] 