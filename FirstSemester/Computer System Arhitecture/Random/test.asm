bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data;a*b + c*d
      a db 8 
      b dw 6
      c dw 4
      d dw 5


segment code use32 class=code 
start:
     mov ax, 0
     mov al,[a]
     mov dx,[b]
     mul dx ;dx:ax = a*b
     mov cx,dx
     mov bx,ax
     mov ax,[c]
     mov dx,[d]
     mul dx;dx:ax = c*d
     add ax,bx
     adc dx,cx
     
     
    push dword 0 
    call [exit] 