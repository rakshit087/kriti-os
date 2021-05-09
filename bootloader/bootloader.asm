[org 0x7c00]
KERNEL_OFFSET equ 0x1000  ;This is the memory offset to which we will load our kernel

mov [BOOT_DRIVE], dl ; Remember that the BIOS sets us the boot drive in 'dl' on boot
mov bp, 0x9000 ;initializing stack
mov sp, bp
mov bx , LOADING_MSG ;printing a loading message
call print_rm
call load_kernel ;Load our kernel, it requires BIOS interupts
call enter_pm ;Switch to protected mode
jmp $

%include "routines/print_rm.asm"
%include "routines/load_disk.asm"
%include "routines/gdt.asm"
%include "routines/print_pm.asm"
%include "routines/enter_pm.asm"

[bits 16]
; load_kernel
%include "routines/load_kernel.asm"

[bits 32]
    BEGIN_PM:
    mov ebx , MSG_PROT_MODE 
    call print_pm 
    call KERNEL_OFFSET 
    jmp $ 

; Global variables
BOOT_DRIVE db 0
LOADING_MSG db "Loading OS",0
MSG_PROT_MODE db "Welcome to Kriti OS",0

; Bootsector padding
times (0x1be - ($-$$)) db 0 ;offset 1be has partition 4 entries (each with 8 bytes)
    db 80h ;indicates boot partition
    db 0,2,0 ;indicates cylinder,head,sector
    db 0f0h ;partition type
    db 0ffh,0ffh,0ffh ;ending chs to max
    dd 1 ;logical boot address of starting sector
    dd (20*16*63-1) ;size

    times (16*3) db 0 ;setting the next 3 entries to 0

dw 0xaa55 ;magic number