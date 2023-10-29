
#include "arch/x86/system.h"
#include "arch/hal/hal.h"

void gdt_good()
{
    messages(OK, "\n");

    messages(OK, "GDT LOADED! \n");

}

void idt_good()
{
    messages(OK, "IDT LOADED! \n \n");
}

void kernel_entry()
{
    init_term(g_fg, g_bg);
    hal_init();

    printf("Welcome to ZecelOS! \n");
    printf("Codename: Bomber \n \n");

    crash_me();
}
