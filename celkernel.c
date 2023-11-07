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
    
    g_bg = BLACK;

    init_term(WHITE, g_bg);
	resetfg();

    printf("\n");
    printf("CelOS Embedded\n");
    printf("Version 0.6.5\n");
    printf("Codename: Cel to C\t");

    printf("real");
}