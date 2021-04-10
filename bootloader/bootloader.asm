[org 0x7c00]
KERNEL_OFFSET equ 0x1000  ; This is the memory offset to which we will load our kernel

mov [BOOT_DRIVE], dl ; Remember that the BIOS sets us the boot drive in 'dl' on boot
mov bp, 0x9000
mov sp, bp
mov bx , LOADING_MSG 
call print_rm
call load_kernel ;Load our kernel
call enter_pm ;Switch to protected mode , from which
jmp $

%include "routines/print_rm.asm"
%include "routines/load_disk.asm"
%include "routines/gdt.asm"
%include "routines/print_pm.asm"
%include "routines/enter_pm.asm"

[bits 16]
; load_kernel
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print_rm
    mov bx, KERNEL_OFFSET ; Read from disk and store in 0x1000
    mov dh, 2
    mov dl, [BOOT_DRIVE]
    call load_disk
    ret

[bits 32]
    BEGIN_PM:
    mov ebx , MSG_PROT_MODE 
    call print_pm 
    call KERNEL_OFFSET 
    jmp $ 

; Global variables
BOOT_DRIVE db 0
LOADING_MSG db "Started in 16 - bit Real Mode",0
MSG_PROT_MODE db "Successfully landed in 32 - bit Protected Mode",0
MSG_LOAD_KERNEL db "Loading kernel into memory.",0

; Bootsector padding
times 510 - ($-$$) db 0
dw 0xaa55
