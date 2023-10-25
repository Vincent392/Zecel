
[bits 32]

global IDTASM_Load

extern idt_good

IDTASM_Load:
	push ebp
	mov ebp, esp

	mov eax, [ebp + 8]
	lidt [eax]

	mov esp, ebp
	pop ebp
	call idt_good
	ret
