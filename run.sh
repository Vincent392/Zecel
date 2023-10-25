
#assemble boot.s file
as --32 boot.s -o boot.o

nasm -f elf arch/x86/idt.asm -o idt.o
nasm -f elf arch/x86/isr.asm -o isr.o

#compile kernel.c file
gcc -m32 -c arch/x86/system.c -o system.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c arch/x86/descriptor_tables.c -o descriptor_tables.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c arch/x86/isrs_gen.c -o isrs_genc.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c arch/x86/isr.c -o isrc.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra


ld -m elf_i386 -T linker.ld system.o kernel.o boot.o descriptor_tables.o idt.o isr.o isrc.o -o ZecelOS.bin -nostdlib

grub-file --is-x86-multiboot ZecelOS.bin

#building the iso file
mkdir -p isodir/boot/grub
cp ZecelOS.bin isodir/boot/ZecelOS.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o ZecelOS.iso isodir

#run it in qemu
qemu-system-x86_64 -cdrom ZecelOS.iso
