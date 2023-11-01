
all:
	as --32 arch/x86/asm/gnu/boot.s -o boot.o

	nasm -f elf arch/x86/asm/idt.asm -o idt.o
	nasm -f elf arch/x86/asm/isr.asm -o isr.o
	nasm -f elf arch/x86/asm/x86.asm -o x86asm.o

	gcc -m32 -c arch/x86/lib/stdio.c -o stdio.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -m32 -c arch/x86/descriptor_tables.c -o descriptor_tables.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -m32 -c arch/x86/isr.c -o isrc.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -m32 -c arch/hal/hal.c -o hal.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

	ld -m elf_i386 -T linker.ld stdio.o x86asm.o kernel.o boot.o descriptor_tables.o hal.o idt.o isr.o isrc.o -o ZecelOS.bin -nostdlib

	grub-file --is-x86-multiboot ZecelOS.bin

	mkdir -p isodir/boot/grub
	cp ZecelOS.bin isodir/boot/ZecelOS.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o ZecelOS.iso isodir

	qemu-system-x86_64 -cdrom ZecelOS.iso

	rm *.o
	rm *.iso
	rm *.bin

	clear