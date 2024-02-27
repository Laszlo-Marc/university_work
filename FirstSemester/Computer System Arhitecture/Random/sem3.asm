bits 32 
global start
extern exit 
import exit msvcrt.dll  
        
segment data use32 class=data
      a db 'abc'
      b equ $-a
      c times b db 0


segment code use32 class=code 
start:
;Method 1 esi as an index in the string
     ; mov esi,0
    ;calc:
      ;mov al,[a+ESI]
      ;sub al,'a'-'A'
      ;mov [c+esi],al
      ;add esi,1
      ;cmp esi,b;
      ;jb calc
;Method 2 esi as an offset of the current byte
      mov esi,a
      mov edi,c
      calc:
            mov al,[esi]
            sub al,'a'-'A'
            mov [edi],al
            inc esi
            inc edi
            dec ecx
            cmp ecx,0
            ja calc
   
    push dword 0 
    call [exit] 