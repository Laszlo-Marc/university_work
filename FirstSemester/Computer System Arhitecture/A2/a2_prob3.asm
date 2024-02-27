bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data
      a db 10
      b dw 128
      c dd 90
      d dq 100


segment code use32 class=code ;(c+d)-(a+d)+b
start:
        mov eax,0
        mov ax,[c]
        add eax,[d]
        mov ebx,0
        mov bl,[a]
        add bx,[d]
        sub eax,ebx
        add eax,[b]

   
    push dword 0 
    call [exit] 