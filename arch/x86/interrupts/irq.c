
#include "irq.h"
#include "../lib/stdio.h"
#include "../descriptor_tables.h"

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void *irq_routines[16] = 
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void irq_install_handler(int irq, void (*handler)(Registers* regs))
{
	irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq)
{
	irq_routines[irq] = 0;
}

void irq_remap(void)
{
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x00);
	outb(0xA1, 0x00);
}

void irq_install()
{
	irq_remap();
	IDT_SetGate(32, (unsigned)irq0, 0x08, 0x8E);
	IDT_SetGate(33, (unsigned)irq1, 0x08, 0x8E);
	IDT_SetGate(34, (unsigned)irq2, 0x08, 0x8E);
	IDT_SetGate(35, (unsigned)irq3, 0x08, 0x8E);
	IDT_SetGate(36, (unsigned)irq4, 0x08, 0x8E);
	IDT_SetGate(37, (unsigned)irq5, 0x08, 0x8E);
	IDT_SetGate(38, (unsigned)irq6, 0x08, 0x8E);
	IDT_SetGate(39, (unsigned)irq7, 0x08, 0x8E);
	IDT_SetGate(40, (unsigned)irq8, 0x08, 0x8E);
	IDT_SetGate(41, (unsigned)irq9, 0x08, 0x8E);
	IDT_SetGate(42, (unsigned)irq10, 0x08, 0x8E);
	IDT_SetGate(43, (unsigned)irq11, 0x08, 0x8E);
	IDT_SetGate(44, (unsigned)irq12, 0x08, 0x8E);
	IDT_SetGate(45, (unsigned)irq13, 0x08, 0x8E);
	IDT_SetGate(46, (unsigned)irq14, 0x08, 0x8E);
	IDT_SetGate(47, (unsigned)irq15, 0x08, 0x8E);
}

void irq_handler(Registers* regs)
{
	void (*handler)(Registers* regs);

	handler = irq_routines[regs->interrupt - 32];
	if(handler)
	{
		handler(regs);
	}

	if(regs->interrupt >= 40)
	{
		outb(0xA0, 0x20);
	}

	outb(0x20, 0x20);
}