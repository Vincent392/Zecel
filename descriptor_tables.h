
/*
    descriptor_tables.h - GDT And IDT Header File.

    Authors: Kap Petrov
*/

#include "types.h"

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

void init_descriptor_tables();

struct idt_entry
{

    uint16 isr_low;
    uint16 kernel_cs;
    uint8 reserved;
    uint8 attributes;
    uint16 isr_high;

}__attribute__((packed));

typedef struct idt_entry idt_entry_g;

struct idtr
{

    uint16 limit;
    uint32 base;

}__attribute__((packed));

typedef struct idtr idtr_g;
