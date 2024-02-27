bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data
      a db 4
      b dw 10
      c dd 9
      d dq 5
      x resq 1

segment code use32 class=code ;(b+b+d)-(c+a)
start:
        mov eax,0
        mov eax, dword[d]
        mov edx, dword[d+4]
        add eax, [b]
        add eax, [b]
        mov dword[x],eax
        mov dword[x+4],edx
   
   
    push dword 0 
    call [exit] 