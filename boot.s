
.set MAGIC, 0x1BADB002
.set FLAGS, 0
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot

.long MAGIC
.long FLAGS
.long CHECKSUM

stackBottom:

.skip 1024

stackTop:

.section .text
.global _start
.type _start, @function

gdt_flush:
    movl 4(%esp), %eax
    lgdt (%eax)

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    jmp $0x08, $flush

.global gdt_flush

flush:
    call gdt_good
	ret

_start:

    mov $stackTop, %esp

    call kernel_entry

    cli

hltLoop:
    hlt
    jmp hltLoop

.size _start, . - _start
