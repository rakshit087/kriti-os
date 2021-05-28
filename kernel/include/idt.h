#define low_16(address) (unsigned short)((address)&0xFFFF)
#define high_16(address) (unsigned short)(((address) >> 16) & 0xFFFF)
//Since IDT Vector has 256 Entries
#define IDT_ENTRIES 256

//Kernel Code Segment Offset
#define KERNEL_CS 0x08

//Defining IDT Handler Structure

typedef struct
{
    unsigned short low_offset;  // The lower 16 bits of the address to jump to when this interrupt fires.
    unsigned short sel;         // Kernel segment selector
    unsigned char always0;      // This byte is set to zero
    unsigned char flags;        // Flags
    unsigned short high_offset; // The higer 16 bits of the address to jump to when this interrupt fires.
} __attribute__((packed)) idt_gate_t;

// FLAGS ->
// Bit 7: "Interrupt is present"
// Bits 6-5: Privilege level of caller (0=kernel..3=user)
// Bit 4: Set to 0 for interrupt gates
// Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate"

// A pointer to the array of interrupt handlers.

typedef struct
{
    unsigned short limit;
    unsigned int base; // The address of the first element in our idt_entry_t array.
} __attribute__((packed)) idt_ptr_t;

idt_gate_t idt[IDT_ENTRIES];
idt_ptr_t idt_reg;

void flush_idt();
void set_idt_gate(int n, unsigned int handler);