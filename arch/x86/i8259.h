
#pragma once

#include "system.h"

#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA1

enum {
	PIC_ICW1_ICW4 				= 0x01,
	PIC_ICW1_SINGLE 			= 0x02,
	PIC_ICW1_INTERVAL 			= 0x04,
	PIC_ICW1_LEVEL				= 0x08,
	PIC_ICW1_INITIALIZE 		= 0x10
} PIC_ICW1;

enum {
	PIC_ICW4_8086 				= 0x1,
	PIC_ICW4_AUTO_EOI 			= 0x2,
	PIC_ICW4_BUFFER_MASTER 		= 0x4,
	PIC_ICW4_BUFFER_SLAVE		= 0x0,
	PIC_ICW4_BUFFERRED			= 0x8,
	PIC_ICW4_SFNM				= 0x10
} PIC_ICW4;

void i8259_PIC_Configure(uint8 offsetPic1, uint8 offsetPic2);
void i8259_PIC_Mask(int irq);
void i8259_PIC_Unmask(int irq);