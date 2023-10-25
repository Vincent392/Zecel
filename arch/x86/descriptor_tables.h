
/*
    descriptor_tables.h - GDT And IDT Header File.

    Authors: Kap Petrov
*/

#include "types.h"

void init_descriptor_tables();

struct gdt_entry
{
    uint16 limit_low;
    uint16 base_low;
    uint8 base_middle;
    uint8 access;
    uint8 granularity;
    uint8 base_high;
}__attribute__((packed));

typedef struct gdt_entry gdt_entry_t;

struct gdt_ptr
{
    uint16 limit;
    uint32 base;
}__attribute__((packed));

typedef struct gdt_ptr gdt_ptr_t;

typedef enum
{
    IDT_FLAG_GATE_TASK = 0x5,
    IDT_FLAG_GATE_16BIT_INT = 0x6,
	IDT_FLAG_GATE_16BIT_TRAP = 0x7,
	IDT_FLAG_GATE_32BIT_INT = 0xE,
	IDT_FLAG_GATE_32BIT_TRAP = 0xF,

	IDT_FLAG_RING0 = (0 << 5),
	IDT_FLAG_RING1 = (1 << 5),
	IDT_FLAG_RING2 = (2 << 5),
	IDT_FLAG_RING3 = (3 << 5),

	IDT_FLAG_PRESENT = 0x80,

    GDT_CODE_SEGMENT = 0x08,


} IDT_FLAGS;

void IDT_SetGate(int interrupt, void* base, uint16 segmentDescriptor, uint8 flags);
void IDT_EnableGate(int interrupt);
void IDT_DisableGate(int interrupt);
