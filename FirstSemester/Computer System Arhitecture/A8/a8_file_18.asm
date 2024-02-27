bits 32 ;assembling for the 32 bits architecture
global start

; we ask the assembler to give global visibility to the symbol called start 
;(the start label will be the entry point in the program) 
extern exit ; we inform the assembler that the exit symbol is foreign; it exists even if we won't be defining it
import exit msvcrt.dll  ; we specify the external library that defines the symbol
extern fopen
extern fclose
extern fread
extern printf  
import fread msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
      
segment data use32 class=data
    file_name db "file2.txt",0
    access_mode db "r",0
    file_descriptor dd -1
    len equ 100
    text times len db 0
    message db "The number of words is %d", 10,0
segment code use32 class=code
start:
 push dword access_mode     
    push dword file_name
    call [fopen]
    add esp, 4*2
    
    mov [file_descriptor],eax
    
    cmp eax,0
    je final
    
    push dword [file_descriptor]
    push dword len
    push dword 1
    push dword text        
    call [fread]
    add esp, 4*4
    
    cmp eax,0
    jl final
    
    mov ecx, text  ; initialize ecx to the start of the text buffer
    mov edx, text + len  ; initialize edx to the end of the text buffer
    mov eax, 0  ; initialize the counter to 0
    
count_words:
    cmp ecx, edx  ; compare ecx and edx
    jae done      ; if ecx is greater than or equal to edx, we are done
    mov bl, [ecx] ; load the character at the current position into bl
    cmp bl, ' '   ; compare the character to ' ' (space)
    je increment  ; if the character is a space, increment the counter
    cmp bl, '.'   ; compare the character to '.' (period)
    je increment  ; if the character is a period, increment the counter
    jmp next      ; otherwise, move on to the next character
    
increment:
    inc eax       ; increment the counter

next:
    inc ecx       ; move to the next character
    jmp count_words   ; loop until we are done

done:
    
    push eax      ; push the count onto the stack
    push message  ; push the address of the message string onto the stack
    call [printf]  
    add esp, 8
    
final:
    push dword [file_descriptor]
    call [fclose]
    add esp, 4
    
    push dword 0 
    call [exit] 
