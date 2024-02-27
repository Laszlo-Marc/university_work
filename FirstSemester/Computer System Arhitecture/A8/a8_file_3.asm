bits 32 ;assembling for the 32 bits architecture
global start

extern exit 
import exit msvcrt.dll    
extern fopen
extern fclose
extern fread
extern printf
import fread msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    file_name db "file.txt",0
    access_mode db "r",0
    file_descriptor dd -1
    len equ 100
    text times len db 0
    message db "The number of even digits is %d", 10,0

; A text file is given. Read the content of the file, count the number of even digits and display the result on the screen. The name of text file is defined in the data segment.
segment code use32 class=code
start:
    mov eax,0
    push dword access_mode     
    push dword file_name
    call [fopen]
    add esp, 4*2
    
    mov [file_descriptor],eax
    
    cmp eax,0
    jl final
    
    push dword [file_descriptor]
    push dword len
    push dword 1
    push dword text        
    call [fread]
    add esp, 4*4
    
    cmp eax,0
    jl final
    
    mov ecx,text
    mov edx,text + len
    mov eax,0
count_even_digits:
    cmp ecx, edx  ; compare ecx and edx
    jae done      ; if ecx is greater than or equal to edx, we are done
    mov bl, [ecx] ; load the character at the current position into bl
    cmp bl, '0'   ; compare the character to '0'
    jb next       ; if the character is less than '0', we are done
    cmp bl, '9'   ; compare the character to '9'
    ja next      ; if the character is greater than '9', we are done
    and bl, 1     ; mask off all but the least significant bit
    jz increment       ; if the least significant bit is 0, increment the counter
    jmp next      ; otherwise, move on to the next character
    
increment:
    inc eax       ; increment the counter

next:
    inc ecx       ; move to the next character
    jmp count_even_digits   ; loop until we are done

done:
    
    push eax      ; push the count onto the stack
    push message  ; push the address of the message string onto the stack
    call [printf]  
    add esp, 8
final:
    push dword 0 ; saves on stack the parameter of the function exit
    call [exit]
