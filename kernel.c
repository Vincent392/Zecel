
#include "descriptor_tables.h"
#include "system.h"

/*
    kernel.c - Main Kernel

    Authors: Kap Petrov
*/

const char* username;

void gdt_good()
{
    messages(OK, "KERNEL LOADE \n");

    messages(OK, "GDT LOADED! \n");

    messages(OK, "IDT LOADED! \n");
    username = "DefaultUser0";

    messages(TEST, "Your Username Is: ");
    printstring(username, WHITE, g_bg);
    newline();
}

void panic()
{
        g_bg = RED;

        init_term(WHITE, g_bg);

        messages(FAILURE, "UNRESOLVED PANIC 0x00000");
        vga_index = 80*1;
        messages(TEST, "IN OTHER WORDS, THE SYSTEM CRASHED YOU *****!");

        asm volatile ("cli");
        asm volatile ("hlt");
}


void kernel_entry()
{
    init_term(WHITE, g_bg);
    init_descriptor_tables();

    if(username == "OSDEV")
    {

        messages(FAILURE, "<- You All For Real.");

    }

    if(username == "System")
    {
        panic();
    }

    printstring("Welcome to ZecelOS! \n", WHITE, g_bg);
    printstring("Codename: Bomber \n", WHITE, g_bg);
    newline();
    printstring("CelOS Credits: \n", WHITE, g_bg);
    printstring("Vincent - Lead Dev \n", WHITE, g_bg);
    printstring("Kap - Conversion Of CelOS To C \n", WHITE, g_bg);
    printstring("Github Contributors - you people rock \n", WHITE, g_bg);
    newline();
    printstring("ZecelOS Credits: \n", WHITE, g_bg);
    printstring("Kap - Lead Dev \n", WHITE, g_bg);
    printstring("Vincent - Ideas \n", WHITE, g_bg);
    printstring("GZB - For Existing. \n", WHITE, g_bg);
    printstring("amrix - Lead Dev 2 \n", WHITE, g_bg);
    printstring("yeti - for the small things you did to help \n", WHITE, g_bg);
    printstring("OSDev Wiki - Knowledge on OSDev \n", WHITE, g_bg);
    newline();
    printstring("Random Shoutouts: \n", WHITE, g_bg);
    printstring("The C Dev Team - For making C, obviously. \n", WHITE, g_bg);
    printstring("The ASM Dev Team - For making Assembly, obviously. \n", WHITE, g_bg);
    printstring("The NASM Dev Team - For making an absolutely based assembly compiler, Nasm. \n", WHITE, g_bg);
}
