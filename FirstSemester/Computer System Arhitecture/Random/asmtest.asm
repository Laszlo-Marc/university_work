bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data
      ;a0 db 10b
      ;a1 dw 0h12
      ;a2 db 123456h
      ;a3 db 1111_0011_1111_0000b
      ;_a4 dw 124h
      ;a5 db 33b
      ;?a6 dw 233h
      ;a7~ db 1233h
       b0 db 256
       b1 dd 100h

segment code use32 class=code
start:
        

   
    push dword 0 
    call [exit] 