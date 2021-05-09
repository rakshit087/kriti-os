[bits 32]
VIDEO_MEMORY equ 0xb8000
COLORS equ 0x05 ;magenta color

print_pm:
    pusha ;save registers in the stack 
    mov edx, VIDEO_MEMORY

print_loop:
    mov al, [ ebx ] ;al has ASCII character
    mov ah, COLORS ;ah has colors
    cmp al, 0 
    je print_done 
    mov [edx], ax 
    add ebx, 1
    add edx, 2 
jmp print_loop 

print_done:
popa
ret 