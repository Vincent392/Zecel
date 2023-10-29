
#assemble boot.s file
as --32 boot.s -o boot.o

#assemble other asm files
nasm -f elf arch/x86/idt.asm -o idt.o
nasm -f elf arch/x86/isr.asm -o isr.o
nasm -f elf arch/x86/x86.asm -o x86asm.o

#compile c files
gcc -m32 -c arch/x86/system.c -o system.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c arch/x86/descriptor_tables.c -o descriptor_tables.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c arch/x86/isr.c -o isrc.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c arch/x86/i8259.c -o i8259.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c arch/hal/hal.c -o hal.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

#link all the fles
ld -m elf_i386 -T linker.ld system.o x86asm.o kernel.o boot.o descriptor_tables.o hal.o idt.o isr.o isrc.o i8259.o -o ZecelOS.bin -nostdlib

#grub
grub-file --is-x86-multiboot ZecelOS.bin

#building the iso file
mkdir -p isodir/boot/grub
cp ZecelOS.bin isodir/boot/ZecelOS.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o ZecelOS.iso isodir

#run it in qemu
qemu-system-x86_64 -cdrom ZecelOS.iso

#remove all .o, .iso, .bin, files
rm *.o
rm *.iso
rm *.bin

#clear the terminal
clear
