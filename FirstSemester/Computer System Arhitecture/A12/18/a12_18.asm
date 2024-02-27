
bits 32
global _minim
extern _printf
extern _scanf
segment data use32 public data
	n dd 0
	mesaj db "Give a number: ",0
    format_afis db "%x",0
	nr times 100 dd 0
	format db "%d",0

;Read a string of unsigned numbers in base 10 from keyboard. 
;Determine the minimum value of the string and write it in the 
;file min.txt (it will be created) in 16 base
    
segment code use32 public code
_minim:
       	cld
       	mov edi,nr
        
        citire:
        	push dword mesaj
        	call _printf
        	add esp,1*4
        	
        	push dword n
        	push format
        	call _scanf
        	add esp,2*4

            
        	mov eax,[n]
        	cmp eax,0
        	je outside
            ;verificam daca inputul e diferit de 0 si il stocam sau sarim la eticheta outside daca e 0
        	stosd
        jmp citire
        
       	outside:

       		mov ecx,99
       		cld
       		mov esi,nr
            
            push ecx
            lodsd
            mov ebx,eax
            cmp eax,0
            pop ecx
            je final
            ;punem primul element citit in ebx
       	compare:
       		push ecx
            
       		lodsd
       		cmp eax,0
       		je final
            
            cmp ebx,eax
            pop ecx
            jb gata
            mov ebx,eax
            ; comparam toate elementele citite si il punem pe cel mai mic in ebx
        gata:
       	loop compare
    final:
       push ebx
       push format_afis
       call _printf
       add esp, 2*4
       ;afisam cel mai mic element (care se afla in ebx)
    ret
