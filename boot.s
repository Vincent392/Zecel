
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

.macro isr_err_stub number
isr_stub_\number:
    call exception_handler
    iret
.endm

.macro isr_no_err_stub number
isr_stub_\number:
    call exception_handler
    iret
.endm

.extern exception_handler

isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31

.global isr_stub_table

isr_stub_table:
    .int isr_stub_0
    .int isr_stub_1
    .int isr_stub_2
    .int isr_stub_3
    .int isr_stub_4
    .int isr_stub_5
    .int isr_stub_6
    .int isr_stub_7
    .int isr_stub_8
    .int isr_stub_9
    .int isr_stub_10
    .int isr_stub_11
    .int isr_stub_12
    .int isr_stub_13
    .int isr_stub_14
    .int isr_stub_15
    .int isr_stub_16
    .int isr_stub_17
    .int isr_stub_18
    .int isr_stub_19
    .int isr_stub_20
    .int isr_stub_21
    .int isr_stub_22
    .int isr_stub_23
    .int isr_stub_24
    .int isr_stub_25
    .int isr_stub_26
    .int isr_stub_27
    .int isr_stub_28
    .int isr_stub_29
    .int isr_stub_30
    .int isr_stub_31

_start:

    mov $stackTop, %esp

    call kernel_entry

    cli

hltLoop:
    hlt
    jmp hltLoop

.size _start, . - _start
