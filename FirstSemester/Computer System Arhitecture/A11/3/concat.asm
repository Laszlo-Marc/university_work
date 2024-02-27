bits 32
extern sirfinal1
extern sirfinal2
global concatenare1
global concatenare2
segment code use32 public code class='code'
    concatenare1:
        mov edi, sirfinal1
        mov esi, eax
        sir1loop:
            lodsb
            cmp al, '0'
            jl notdecimalsir1
            cmp al, '9'
            jg notdecimalsir1
            stosb
            jmp sir1loop
        notdecimalsir1:
            test al, al
            jz sir2
            jmp sir1loop
        sir2:
            mov esi,ebx
            sir2loop:
                lodsb
                cmp al, '0'
                jl notdecimalsir2
                cmp al, '9'
                jg notdecimalsir2
                stosb
                jmp sir2loop
            notdecimalsir2:
                test al, al
                jz gata1
                jmp sir2loop
        gata1:
            stosb
            ret
    concatenare2:
        mov edi, sirfinal2
        mov esi, eax
        sir1loop2:
            lodsb
            cmp al, '0'
            jl notdecimal1
            cmp al, '9'
            jg notdecimal1
            stosb
            jmp sir1loop2
        notdecimal1:
            test al, al
            jz sir2
            jmp sir1loop
        sir2.2:
            mov esi, ebx
            sir2loop2:
                lodsb
                cmp al, '0'
                jl notdecimal2
                cmp al, '9'
                jg notdecimal2
                stosb
                jmp sir2loop2
            notdecimal2:
                test al, al
                jz gata2
                jmp sir2loop2
        gata2:
            stosb
            ret