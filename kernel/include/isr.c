#include "isr.h"
#include "display.h"
#include "string.h"
#include "ports.h"
#include "mem.h"

char* exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

//The function registers a new interrupt into the IDT.
void register_interrupt_handler(uint8 n, interrupt_handler_t handler)
{
    interrupt_handlers[n] = handler;
    set_idt_gate(n, (uint32)handler);
}

void isr_install()
{
  idt_reg.limit = sizeof (idt_gate_t) * IDT_ENTRIES - 1;
  idt_reg.base  = (uint32) &idt;

  memory_set(&idt, 0, sizeof (idt_gate_t) * IDT_ENTRIES - 1);

  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  outb(0x21, 0x20);
  outb(0xA1, 0x28);
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  outb(0x21, 0x0);
  outb(0xA1, 0x0);

  set_idt_gate(0, (uint32)isr0);
  set_idt_gate(1, (uint32)isr1);
  set_idt_gate(2, (uint32)isr2);
  set_idt_gate(3, (uint32)isr3);
  set_idt_gate(4, (uint32)isr4);
  set_idt_gate(5, (uint32)isr5);
  set_idt_gate(6, (uint32)isr6);
  set_idt_gate(7, (uint32)isr7);
  set_idt_gate(8, (uint32)isr8);
  set_idt_gate(9, (uint32)isr9);
  set_idt_gate(10, (uint32)isr10);
  set_idt_gate(11, (uint32)isr11);
  set_idt_gate(12, (uint32)isr12);
  set_idt_gate(13, (uint32)isr13);
  set_idt_gate(14, (uint32)isr14);
  set_idt_gate(15, (uint32)isr15);
  set_idt_gate(16, (uint32)isr16);
  set_idt_gate(17, (uint32)isr17);
  set_idt_gate(18, (uint32)isr18);
  set_idt_gate(19, (uint32)isr19);
  set_idt_gate(20, (uint32)isr20);
  set_idt_gate(21, (uint32)isr21);
  set_idt_gate(22, (uint32)isr22);
  set_idt_gate(23, (uint32)isr23);
  set_idt_gate(24, (uint32)isr24);
  set_idt_gate(25, (uint32)isr25);
  set_idt_gate(26, (uint32)isr26);
  set_idt_gate(27, (uint32)isr27);
  set_idt_gate(28, (uint32)isr28);
  set_idt_gate(29, (uint32)isr29);
  set_idt_gate(30, (uint32)isr30);
  set_idt_gate(31, (uint32)isr31);
  set_idt_gate (32, (uint32)irq0);
  set_idt_gate (33, (uint32)irq1);
  set_idt_gate (34, (uint32)irq2);
  set_idt_gate (35, (uint32)irq3);
  set_idt_gate (36, (uint32)irq4);
  set_idt_gate (37, (uint32)irq5);
  set_idt_gate (38, (uint32)irq6);
  set_idt_gate (39, (uint32)irq7);
  set_idt_gate (40, (uint32)irq8);
  set_idt_gate (41, (uint32)irq9);
  set_idt_gate (42, (uint32)irq10);
  set_idt_gate (43, (uint32)irq11);
  set_idt_gate (44, (uint32)irq12);
  set_idt_gate (45, (uint32)irq13);
  set_idt_gate (46, (uint32)irq14);
  set_idt_gate (47, (uint32)irq15);
  set_idt_gate(128, (uint32)isr128);
  set_idt(); // Load with ASM
  memory_set(&interrupt_handlers, 0, sizeof (interrupt_handler_t) * IDT_ENTRIES);
}

/*Handlers*/
void isr0()
{
    display(exception_messages[0],RED);
    asm("hlt");
}
void isr1()
{
    display(exception_messages[1],RED);
    asm("hlt");
}
void isr2()
{
    display(exception_messages[2],RED);
    asm("hlt");
}
void isr3()
{
    display(exception_messages[3],RED);
    asm("hlt");
}
void isr4()
{
    display(exception_messages[4],RED);
    asm("hlt");
}
void isr5()
{
    display(exception_messages[5],RED);
    asm("hlt");
}
void isr6()
{
    display(exception_messages[6],RED);
    asm("hlt");
}
void isr7()
{
    display(exception_messages[7],RED);
    asm("hlt");
}
void isr8()
{
    display(exception_messages[8],RED);
    asm("hlt");
}
void isr9()
{
    display(exception_messages[9],RED);
    asm("hlt");
}
void isr10()
{
    display(exception_messages[10],RED);
    asm("hlt");
}
void isr11()
{
    display(exception_messages[11],RED);
    asm("hlt");
}
void isr12()
{
    display(exception_messages[12],RED);
    asm("hlt");
}
void isr13()
{
    display(exception_messages[13],RED);
    asm("hlt");
}
void isr14()
{
    display(exception_messages[14],RED);
    asm("hlt");
}
void isr15()
{
    display(exception_messages[15],RED);
    asm("hlt");
}
void isr16()
{
    display(exception_messages[16],RED);
    asm("hlt");
}
void isr17()
{
    display(exception_messages[17],RED);
    asm("hlt");
}
void isr18()
{
    display(exception_messages[18],RED);
    asm("hlt");
}
void isr19()
{
    display(exception_messages[19],RED);
    asm("hlt");
}
void isr20()
{
    display(exception_messages[20],RED);
    asm("hlt");
}
void isr21()
{
    display(exception_messages[21],RED);
    asm("hlt");
}
void isr22()
{
    display(exception_messages[22],RED);
    asm("hlt");
}
void isr23()
{
    display(exception_messages[23],RED);
    asm("hlt");
}
void isr24()
{
    display(exception_messages[24],RED);
    asm("hlt");
}
void isr25()
{
    display(exception_messages[25],RED);
    asm("hlt");
}
void isr26()
{
    display(exception_messages[26],RED);
    asm("hlt");
}
void isr27()
{
    display(exception_messages[27],RED);
    asm("hlt");
}
void isr28()
{
    display(exception_messages[28],RED);
    asm("hlt");
}
void isr29()
{
    display(exception_messages[29],RED);
    asm("hlt");
}
void isr30()
{
    display(exception_messages[30],RED);
    asm("hlt");
}
void isr31()
{
    display(exception_messages[31],RED);
    asm("hlt");
}
void isr128()
{
    display("isr 128!\n",RED);
    asm("hlt");
}

void irq_handler(registers32_t *regs)
{
    if (regs->int_no >= 40)
    {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);

    if (interrupt_handlers[regs->int_no] != 0)
    {
      interrupt_handlers[regs->int_no] (regs);
    }
}