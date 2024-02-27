bits 32
global sirfinal1
global sirfinal2
import printf msvcrt.dll
import exit msvcrt.dll
extern printf,exit,concatenare1,concatenare2
global start

segment code use32 punlic code class='code'
	start:
		mov eax,sir1
		mov ebx,sir2
        
		call concatenare1
		push sirfinal1
		push dword format1
		call [printf]
		add esp,2*4
        
		mov eax,sir2
		mov ebx,sir1
        
		call concatenare2
		push sirfinal2
		push dword format2
		call [printf]
		add esp,2*4
        
		push dword 0 
		call [exit]

segment data use32
	sir1 db "abc123",0
	sir2 db "def456",0
    sirfinal1 resb 1000
    sirfinal2 resb 1000
	format1 db "First concatenation: %s ",0
	format2 db "Second concatenation: %s",0