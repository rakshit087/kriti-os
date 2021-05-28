#include "idt.h"

// Sets IDT Gate for the given address
void set_idt_gate(int n, unsigned int handler) {
    idt[n].low_offset = low_16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E; 
    idt[n].high_offset = high_16(handler);
}

//Fills the entire idt table
void flush_idt() {
    idt_reg.base = (unsigned int) &idt; //The pointer to idt array
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1; //256 * size of each entry
    asm volatile ("lidtl (%0)" : : "r" (&idt_reg));
}