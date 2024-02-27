bits 32 
global start
extern exit 
import exit msvcrt.dll  

segment data use32 class=data
    doubleword_array dd 0702090Ah, 0B0C0304h, 05060108h 
    doubleword_count equ 3
    byte_array db doubleword_count * 2
    byte_count equ doubleword_count * 2

segment code use32 class=code
start:
 mov ecx, doubleword_count
    mov esi, 0
    mov edi, 0

doubleword_loop:
    ; unpack each value in the doubleword into two separate variables
    mov eax, [doubleword_array + esi]
    mov edx, eax
    and eax, 0x0000ffff
    shr edx, 16

    ; store the unpacked values in the byte array
    mov [byte_array + edi], al
    inc edi
    mov [byte_array + edi], dl
    inc edi

    ; move to the next doubleword in the array
    add esi, 4

    ; repeat the loop until all doublewords have been processed
    loop doubleword_loop

    ; sort the byte array in ascending order
    call sort_byte_array

    ; exit the program
    mov eax, 1
    xor ebx, ebx
    int 0x80

sort_byte_array:
        mov ecx, byte_count
    dec ecx
    mov esi, 0

bubble_sort_loop:
    ; initialize inner loop variable
    mov edi, 0

bubble_sort_inner_loop:
    ; compare the current and next values in the array
    mov al, [byte_array + esi]
    cmp al, [byte_array + esi + 1]
    jg swap_values

    ; move to the next pair of values in the array
    inc esi

    ; repeat the inner loop until all pairs have been compared
    inc edi
    cmp edi, ecx
    jl bubble_sort_inner_loop

    ; move to the next pair of values in the outer loop
    inc esi

    ; repeat the outer loop until all pairs have been compared
    dec ecx
    jnz bubble_sort_loop

    ; exit the sorting function
    ret

swap_values:
    ; swap the values in the array
    mov dl, [byte_array + esi + 1]
    mov [byte_array + esi + 1], al
    mov [byte_array + esi], dl

    ; continue with the next pair of values in the array
    jmp bubble_sort_inner_loop

    push dword 0 
    call [exit] 


