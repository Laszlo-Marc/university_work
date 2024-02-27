bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data
      a db 10
      b dw 70
      c dd 90
      d dq 100


segment code use32 class=code ;(d+d)-a-b-c
start:
        mov eax,0
        mov eax,[d]
        add eax,[d]
        sub ax,[a]
        sub ax,[b]
        sub ax,[c]

   
    push dword 0 
    call [exit] 