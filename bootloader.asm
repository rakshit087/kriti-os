[org 0x7c00]

mov bp , 0x9000 ;stack
mov sp , bp

call switch_to_pm 

jmp $
%include "gdt.asm"
%include "print.asm"
%include "enter32bit.asm"

[ bits 32]
BEGIN_PM :
    mov ebx , PRINT_ME
    call print 
jmp $


PRINT_ME db "Running on 32 bits " , 0

;filling rest of the code with 0s
times 510 -( $ - $$ ) db 0
;magic number
dw 0xaa55