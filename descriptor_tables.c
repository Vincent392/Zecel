
/*
    descriptor_tables.c - GDT And IDT C File.

    Authors: Kap Petrov
*/

#include "descriptor_tables.h"

extern void gdt_flush(uint32);

static void init_gdt();
static void gdt_set_gate(s32int,uint32,uint32,uint8,uint8);

gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;

static void gdt_set_gate(s32int num, uint32 base, uint32 limit, uint8 access, uint8 gran)
{
	gdt_entries[num].base_low    = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high   = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low   = (limit & 0xFFFF);
	gdt_entries[num].granularity = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access      = access;
}

static void init_gdt()
{
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_ptr.base = (uint32)&gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

	gdt_flush((uint32)&gdt_ptr);
}

void init_descriptor_tables()
{
	init_gdt();
	idt_init();
}

idtr_g idtr_t;
idt_entry_g idt_entry_t;

static idt_entry_g idt[256];

void idt_set_descriptor(uint8 vector, void* isr, uint8 flags)
{
	idt_entry_g* descriptor = &idt[vector];

	descriptor->isr_low = (uint32)isr & 0xFFFF;
	descriptor->kernel_cs = 0x08;
	descriptor->isr_high = (uint32)isr >> 16;
	descriptor->reserved = 0;
}

extern void* isr_stub_table[];

void idt_init()
{
	idtr_t.base = (uint32)&idt[0];
	idtr_t.limit = (uint16)sizeof(idt_entry_t) * 256 - 1;

	for(uint8 vector = 0; vector < 32; vector++)
	{
		idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
	}

	__asm__ volatile ("lidt %0" : : "m"(idtr_t));
	__asm__ volatile ("sti");
}
