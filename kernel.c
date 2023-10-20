
#include "descriptor_tables.h"
#include "system.h"

/*
    kernel.c - Main Kernel

    Authors: Kap Petrov
*/

void gdt_good()
{
    messages(OK, "KERNEL LOADED! \n");

    messages(OK, "GDT LOADED!");
    newline();
    newline();
    newline();
    newline();
    newline();
    newline();
}

void kernel_entry()
{
    init_term(WHITE, g_bg);
    init_descriptor_tables();

    printstring("Welcome to ZecelOS! \n", WHITE, g_bg);
    printstring("Codename: Bomber \n", WHITE, g_bg);
}
