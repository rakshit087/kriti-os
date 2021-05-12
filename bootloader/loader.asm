[BITS 16]
[ORG 0x7e00]

jmp load_kernel

%include "bootloader/routines/functions.asm"
%include "bootloader/routines/gdt.asm"

load_error:
    call new_line_rm
    mov bp, ErrorMsg
    call print_rm
    call new_line_rm
end:
    hlt
    jmp end

load_kernel:
    mov [DriveId],dl
    mov si,ReadPacket
    mov word[si],0x10
    mov word[si+2],100
    mov word[si+4],0
    mov word[si+6],0x1000
    mov dword[si+8],6
    mov dword[si+0xc],0
    mov dl,[DriveId]
    mov ah,0x42
    int 0x13
    jc  load_error

enter_pm:
    cli ;clear all inturrupts
    lgdt [gdt_descriptor] ;load gdt
    ;entering protected mode
    mov eax, cr0
    or eax, 0x1 
    mov cr0, eax
jmp CODE_SEG:init_pm 

[bits 32]

KERNEL equ 0x10000

init_pm: ; we are now using 32-bit instructions
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 
    mov esp, ebp
    
    call KERNEL 
  
DriveId:    db 0
ReadPacket: times 16 db 0
ErrorMsg db "Unable to Load Kernel", 0
