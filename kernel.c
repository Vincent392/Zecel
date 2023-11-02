
#include "arch/x86/lib/stdio.h"
#include "arch/hal/hal.h"

void gdt_good()
{
    log(OK, "\n");

    log(OK, "GDT LOADED! \n");

}

void idt_good()
{
    log(OK, "IDT LOADED! \n \n");
}

void kernel_entry()
{
    init_term(g_fg, g_bg);
    hal_init();

	resetfg();

    printf("Welcome to ZecelOS!\n");
    printf("Codename: Bomber\t");

    printf("Version Number 0.0.1\n");
}