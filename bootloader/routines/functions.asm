clear_screen_rm:
    pusha
    mov ah, 0x06
    xor al, al
    xor bx, bx
    mov bh, 0x07
    xor cx, cx
    mov dh, 24
    mov dl, 79
    int 0x10
    popa
    ret

new_line_rm:
    pusha
	mov ah, 0Eh
    mov al, 0Ah
    int 10h
    mov al, 0Dh
    int 10h
    popa
    ret

key_wait:
    pusha
    mov al, 0xD2
    out 64h, al
    mov al, 0x80
    out 60h, al
    .keyup:
        in al, 0x60
        and al, 10000000b
        jnz .keyup
    .keydown:
    in al, 0x60
    popa
    ret

print_rm:
    pusha

start_print_rm:
    mov al, [bp] ; 'bx' is the base address for the string
    cmp al, 0 
    je done ;jump if equal
    mov ah, 0x0e
    int 0x10 ;BIOS INt
    add bp, 1
    jmp start_print_rm
done:
    popa
ret