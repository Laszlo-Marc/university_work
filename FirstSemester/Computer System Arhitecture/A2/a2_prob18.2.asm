bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data
    a db 4
    b dw 4
    c dd 2
    d dq 14
    x resq 1


segment code use32 class=code ;(d-b)-a-(b-c)
start:
    mov eax,0
    mov eax, dword[d]
    mov edx, dword[d+4]
    sub eax, [b]
    mov dword[x],eax
    mov dword[x+4],edx
    
    mov eax,0
    mov al,[a]
    cbw
    cwde;a is in eax
    sub dword[x],eax
    sbb dword[x+4],edx
    
    mov edx,0
    mov eax,0
    mov ax,[b]
    cwde;b is on eax
    mov ebx,[c]
    sub eax,ebx;in eax is b-c
    sub dword[x],eax
    sbb dword[x+4],edx
    
    push dword 0 
    call [exit] 