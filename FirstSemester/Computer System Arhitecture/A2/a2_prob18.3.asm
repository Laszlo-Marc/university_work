bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data
      a db 10
      b dw 128
      c dw 90
      x dq 100
      e dd 200


segment code use32 class=code ;(a+b*c+2/c)/(2+a)+e+x; a,b-byte; c-word; e-doubleword; x-qword
start:
        

   
    push dword 0 
    call [exit] 