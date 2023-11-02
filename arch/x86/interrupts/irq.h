
#pragma once

#include "../isr.h"

void irq_install_handler(int irq, void (*handler)(Registers* regs)); // Install a custom IRQ Handler
void irq_uninstall_handler(int irq); // uninstall a specific IRQ Handler
void irq_remap(void);
void irq_install();
void irq_handler(Registers* regs);