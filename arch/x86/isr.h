
#pragma once

#include "types.h"
#include "system.h"
#include "isrs_gen.h"

typedef struct {

	uint32 ds;
	uint32 edi, esi, ebp, kern_esp, ebx, edx, ecx, eax;
	uint32 interrupt, error;
	uint32 eip, cs, eflags, esp, ss;

} __attribute__((packed)) Registers;

void initisr();

typedef void (*ISRHANDLER)(Registers* regs);

void ISRRegisterHandler(int interrupt);
