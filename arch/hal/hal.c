#include "hal.h"

void hal_init()
{
    init_descriptor_tables();
	IDT_Init();
	initisr();
	irq_install();

	__asm__ __volatile__ ("sti");
}