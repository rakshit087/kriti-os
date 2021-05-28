[BITS 16]
[ORG 0x7c00]

jmp real_mode

%include "bootloader/routines/functions.asm"

real_mode:
mov [DriveId],dl
    ;Initialize registers with 0
    xor ax,ax   
    mov ds,ax
    mov es,ax  
    mov ss,ax
    ;initialize stack
    mov sp,0x7c00
    ;clear screen
    call clear_screen_rm
    ;Enable A20 gate
    in al, 0x92
    or al, 2
    out 0x92, al
    ;Print Welcome Message
    mov bp,WelcomeMsg
    call print_rm
    call new_line_rm
    ;Ask for key input
    mov bp,PressMsg
    call print_rm
    call new_line_rm
    call key_wait
    call clear_screen_rm
    mov bp, LoadingMsg
    call print_rm
    call new_line_rm

LoadLoader:
    mov si,ReadPacket
    mov word[si],0x10
    mov word[si+2],5
    mov word[si+4],0x7e00
    mov word[si+6],0
    mov dword[si+8],1
    mov dword[si+0xc],0
    mov dl,[DriveId]
    mov ah,0x42
    int 0x13
    jc  ReadError
    mov dl,[DriveId]
    jmp 0x7e00 

ReadError:
    mov bp, ErrorMsg
    call print_rm
    call new_line_rm

hlt
jmp $

DriveId db 0
WelcomeMsg db "Welcome to Kriti OS Bootloader", 0
PressMsg db "Press Any Key to Continue", 0
LoadingMsg db "Loading Kernel", 0
ErrorMsg db "32 bits not supported / Disk Read Error", 0

ReadPacket: times 16 db 0

times (0x1be-($-$$)) db 0

    db 80h
    db 0,2,0
    db 0f0h
    db 0ffh,0ffh,0ffh
    dd 1
    dd (20*16*63-1)
	
    times (16*3) db 0

    db 0x55
    db 0xaa
