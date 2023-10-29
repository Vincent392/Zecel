
/*
    descriptor_tables.c - GDT And IDT C File.

    Authors: Kap Petrov
*/

#include "descriptor_tables.h"
#include "../../util/binary.h"
#include "isr.h"

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
}

typedef struct
{

    uint16 BaseLow;
    uint16 SegmentSelector;
    uint8 Reserved;
    uint8 Flags;
    uint16 BaseHigh;

}__attribute__((packed)) IDTEntry;

typedef struct
{

    uint16 Limit;
    IDTEntry* Ptr;

}__attribute__((packed)) IDTDescriptor;

IDTEntry g_IDT[256];

IDTDescriptor g_IDTDescriptor = { sizeof(g_IDT) - 1, g_IDT };

void __attribute__((cdecl)) IDTASM_Load(IDTDescriptor* idtDescriptor);

void IDT_SetGate(int interrupt, void* base, uint16 segmentDescriptor, uint8 flags)
{
	g_IDT[interrupt].BaseLow = ((uint32)base) & 0xFFFF;
	g_IDT[interrupt].SegmentSelector = segmentDescriptor;
	g_IDT[interrupt].Reserved = 0;
	g_IDT[interrupt].Flags = flags;
	g_IDT[interrupt].BaseHigh = ((uint32)base >> 16) & 0xFFFF;
}

void IDT_EnableGate(int interrupt)
{
	FLAG_SET(g_IDT[interrupt].Flags, IDT_FLAG_PRESENT);
}

void IDT_DisableGate(int interrupt)
{
	FLAG_UNSET(g_IDT[interrupt].Flags, IDT_FLAG_PRESENT);
}

void IDT_Init()
{
	IDTASM_Load(&g_IDTDescriptor);
}
