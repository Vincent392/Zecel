
#include "arch/x86/system.h"
#include "arch/x86/descriptor_tables.h"

/*
    kernel.c - Main Kernel

    Authors: Kap Petrov
*/

void gdt_good()
{
    messages(OK, "KERNEL LOADE \n");

    messages(OK, "GDT LOADED! \n");

}

void idt_good()
{
    messages(OK, "IDT LOADED! \n");
}

void kernel_entry()
{
    init_term(WHITE, g_bg);
    init_descriptor_tables();

    printstring("Welcome to ZecelOS! \n", WHITE, g_bg);
    printstring("Codename: Bomber \n", WHITE, g_bg);
    newline();
}
