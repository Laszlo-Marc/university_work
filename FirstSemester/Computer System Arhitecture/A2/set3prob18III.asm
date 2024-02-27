bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data ;f+(c-2)*(3+a)/(d-4)
      a db 8
      d db 12
      c db 10
      f dw 12
      
      
      

segment code use32 class=code
start:
       mov al,[c]
       sub al,2 ;al=c-2 = 8
       mov bl,[a]
       add bl,3 ; bl=11 
       mul bl; bl*al=>ax
       add ax,[f]
       mov bl,[d]
       sub bl,4
       div bl ;ax:bl= al cat
        
    push dword 0 
    call [exit] 