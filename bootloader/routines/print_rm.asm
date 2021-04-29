print_rm:
    pusha

start:
    mov al, [bx] ; 'bx' is the base address for the string
    cmp al, 0 
    je done
    mov ah, 0x0e
    int 0x10 ;BIOS INt
    add bx, 1
    jmp start
done:
    popa
ret