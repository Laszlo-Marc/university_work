bits 32
global start
import exit msvcrt.dll
extern exit,printf,scanf
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    input times 100 db -1
    destinatie times 100 db -1
    format db "%s",0
    print_format "%d"
segment code use32 class=code
start:
    push dword input
    push dword format
    call [scanf]
    add esp,4*2
    
    
    
    
    
    push dword 0 
    call [exit]