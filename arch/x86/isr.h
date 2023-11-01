
#pragma once

#include "lib/stdint.h"
#include "lib/stdio.h"

typedef struct {

	uint32 ds;
	uint32 edi, esi, ebp, kern_esp, ebx, edx, ecx, eax;
	uint32 interrupt, error;
	uint32 eip, cs, eflags, esp, ss;

} __attribute__((packed)) Registers;

void initisr();

typedef void (*ISRHANDLER)(Registers* regs);

void ISRRegisterHandler(int interrupt, ISRHANDLER handler);
void ISR_InitializeGates();