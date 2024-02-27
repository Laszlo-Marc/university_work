bits 32
global start
import exit msvcrt.dll
extern exit,printf
import printf msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
extern fread,fopen ,fclose
segment data use32 class=data
    file_name db "digits.txt",0
    acces_mode db "r",0
    file_descriptor dd -1
    nr_car_citite db 0
    len equ 100
    buffer resb len
    even_count db 0
    message2 db "File Error",0
    message db "Number of even digits: %d",0
;A text file is given. Read the content of the file, count the number of even digits and display the result on the screen. The name of text file is defined in the data segment.   
segment code use32 class=code
start:
    push dword acces_mode
    push dword file_name
    call [fopen]
    add esp,4*2
    
    mov [file_descriptor],eax
    
    cmp eax,0
    je final
    
    xor eax,eax
    mov edx, 0
    mov ecx, 0 ;Initialize even_count to 0
    mov [even_count],ecx
    bucla:
            push dword [file_descriptor]
            push dword len
            push dword 1
            push dword buffer
            call [fread]
            add esp, 4*4
            
            cmp eax, 0         
            je finish

            mov [nr_car_citite], eax
            mov edx, 0
            count:
                mov ebx, [buffer + edx] ;Get the current character
                cmp ebx, '0'
                jl done ;If the character is not a digit, go to done
                cmp ebx, '9'
                jg done ;If the character is not a digit, go to done
                sub ebx, '0' ;Convert the character to an integer
                cmp ebx, 1
                jle done ;If the digit is not even, go to done
                add ebx, ebx
                cmp ebx, 10
                jg done ;If the digit is not even, go to done
                inc byte[even_count] ;Increment even_count
                done:
                inc edx
                cmp edx, [nr_car_citite]
                jl count
    finish:
    
    push dword [even_count]
    push dword message
    call [printf]
    add esp, 4*2
    
    push dword [file_descriptor]
    call [fclose]
    add esp, 4
    
    final:
    
    push dword 0 
    call [exit]