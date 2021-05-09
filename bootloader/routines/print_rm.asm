;Reference - https://stanislavs.org/helppc/int_10-e.html
print_rm:
    pusha

start:
    mov al, [bp] ; 'bx' is the base address for the string
    cmp al, 0 
    je done ;jump if equal
    mov ah, 0x0e
    int 0x10 ;BIOS INt
    add bp, 1
    jmp start
done:
    popa
ret