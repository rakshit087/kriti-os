load_kernel:
    mov bx, KERNEL_OFFSET ; Read from disk and store in 0x1000
    mov dh, 16 ;No of sectors to read
    mov dl, [BOOT_DRIVE]
    call load_disk
    ret