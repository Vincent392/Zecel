#include "hal.h"

void hal_init()
{
    init_descriptor_tables();
	IDT_Init();
	initisr();
}