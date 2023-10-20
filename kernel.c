
#include "descriptor_tables.h"
#include "system.h"

/*
    kernel.c - Main Kernel

    Authors: Kap Petrov
*/

const char* username;

void gdt_good()
{
    messages(OK, "KERNEL LOADED! \n");

    messages(OK, "GDT LOADED! \n");

    messages(OK, "IDT LOADED! \n");
    newline();
    newline();
    newline();
    newline();
    newline();
    username = "balls";
}

void kernel_entry()
{
    init_term(WHITE, g_bg);
    init_descriptor_tables();

    printstring("Welcome to ZecelOS! \n", WHITE, g_bg);
    printstring("Codename: Bomber \n", WHITE, g_bg);

    asm volatile ("int $0x3");

    if(username == "OSDEV")
    {

        messages(FAILURE, "<- You All For Real.");

    }
}
