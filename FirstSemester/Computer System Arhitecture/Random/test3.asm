bits 32 
global start
extern exit 
import exit msvcrt.dll  
segment data use32 class=data
    a db 2
    b db 5
    d db 10
    c dd 3
    x dq 10
    y resq 1
    z resd 1

segment code use32 class=code
start: ;(8-a*b*100+c)/d+x; a,b,d-byte; c-doubleword; x-qword
    mov eax,0
    mov al, [a]
    imul byte[b];ax=a*b
    mov bx,100
    imul bx;dx:ax=a*b*100
    mov ebx,8
    push dx
    push ax
    pop eax
    sub ebx,eax;ebx=8-a*b*100
    mov eax,ebx
    add eax,[c];eax=8-a*b*100+c=-989
    mov bl,[d]
    cbw
    idiv bx
    mov dword[y],eax
    mov eax,0
    mov edx,0
    mov eax,dword[x]
    mov edx,dword[x+4]
    add dword[y],eax
    adc dword[y+4],edx
    mov ebx,dword[y]
    mov ecx,dword[y+4]
    
    
    push dword 0 
    call [exit] 