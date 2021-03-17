; Infinite loop
loop:
    jmp loop 

; Fill with 510 zeros minus the size of the previous code (since bootloader is 512 bytes)

times 510-($-$$) db 0
; Magic number (2 bytes) It tells the computer about bootloader 
dw 0xaa55 