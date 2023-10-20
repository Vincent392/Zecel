
#assemble boot.s file
as --32 boot.s -o boot.o

#compile kernel.c file
gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c descriptor_tables.c -o descriptor_tables.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c isr.c -o isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

#linking the kernel with kernel.o and boot.o files
ld -m elf_i386 -T linker.ld kernel.o boot.o descriptor_tables.o isr.o -o ZecelOS.bin -nostdlib

grub-file --is-x86-multiboot ZecelOS.bin

#building the iso file
mkdir -p isodir/boot/grub
cp ZecelOS.bin isodir/boot/ZecelOS.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o ZecelOS.iso isodir

#run it in qemu
qemu-system-x86_64 -cdrom ZecelOS.iso
