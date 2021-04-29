gdt_start:

; null descripter
gdt_null: 
dd 0x0 
dd 0x0

;code segment descriptor
gdt_code: 
dw 0xffff
dw 0x0 
db 0x0 
db 10011010b ; 1st flags
db 11001111b ; 2nd flags
db 0x0

;data segment descriptor
gdt_data:
dw 0xffff
dw 0x0 
db 0x0 
db 10010010b ; 1st flags
db 11001111b ; 2nd flags
db 0x0 

gdt_end:

gdt_descriptor:
; Size of our GDT 
dw gdt_end - gdt_start - 1 
dd gdt_start 
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start