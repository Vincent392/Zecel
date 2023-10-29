#include "i8259.h"

void i8259_PIC_Configure(uint8 offsetPic1, uint8 offsetPic2)
{
	outb(PIC1_COMMAND_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INITIALIZE);
	io_wait();
	outb(PIC2_COMMAND_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INITIALIZE);
	io_wait();

	outb(PIC1_DATA_PORT, offsetPic1);
	io_wait();
	outb(PIC2_DATA_PORT, offsetPic2);
	io_wait();

	outb(PIC1_DATA_PORT, 0x4);
	io_wait();
	outb(PIC2_DATA_PORT, 0x2);
	io_wait();

	outb(PIC1_DATA_PORT, PIC_ICW4_8086);
	io_wait();
	outb(PIC2_DATA_PORT, PIC_ICW4_8086);
	io_wait();

	outb(PIC1_DATA_PORT, 0);
	io_wait();
	outb(PIC2_DATA_PORT, 0);
	io_wait();
}

void i8259_PIC_Mask(int irq)
{
	uint8 port;

	if (irq < 8)
		port = PIC1_DATA_PORT;
	else {
		port = PIC2_DATA_PORT;
		irq -= 8;
	}

	uint8 mask = inb(PIC1_DATA_PORT);
	outb(PIC1_DATA_PORT, mask | (1 << irq));
}

void i8259_PIC_Unmask(int irq)
{
	uint8 port;

	if (irq < 8)
		port = PIC1_DATA_PORT;
	else {
		port = PIC2_DATA_PORT;
		irq -= 8;
	}

	uint8 mask = inb(PIC1_DATA_PORT);
	outb(PIC1_DATA_PORT, mask & ~(1 << irq));
}