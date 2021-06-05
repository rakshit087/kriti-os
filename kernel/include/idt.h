#ifndef IDT_H
#define IDT_H

#include "types.h"
//Since IDT Vector has 256 Entries
#define IDT_ENTRIES 256

//Kernel Code Segment Offset
#define KERNEL_CS 0x08

//Defining IDT Handler Structure

typedef struct
{
    uint16 low_offset;  // The lower 16 bits of the address to jump to when this interrupt fires.
    uint16 sel;         // Kernel segment selector
    uint8 always0;      // This byte is set to zero
    uint8 flags;        // Flags
    uint16 high_offset; // The higer 16 bits of the address to jump to when this interrupt fires.
} __attribute__((packed)) idt_gate_t;

// FLAGS ->
// Bit 7: "Interrupt is present"
// Bits 6-5: Privilege level of caller (0=kernel..3=user)
// Bit 4: Set to 0 for interrupt gates
// Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate"

// A pointer to the array of interrupt handlers.

typedef struct
{
    uint16 limit;
    uint32 base;
} __attribute__((packed)) idt_register_t;

/* Struct which aggregates many registers */
typedef struct
{
   uint32 ds;                  // Data segment selector
   uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   uint32 int_no, err_code;    // Interrupt number and error code (if applicable)
   uint32 eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers32_t;

typedef struct
{
   uint16 di, si, bp, sp, bx, dx, cx, ax;
   uint16 gs, fs, es, ds, eflags;
} registers16_t;

idt_gate_t idt[IDT_ENTRIES]; //An array of idt_gate_t
idt_register_t idt_reg;


typedef void (*interrupt_handler_t)(registers32_t *);
interrupt_handler_t interrupt_handlers[IDT_ENTRIES];
void set_idt(); //Sets the IDT
void set_idt_gate(int n, unsigned int handler); //Sets IDT Gate

#endif