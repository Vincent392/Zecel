
[bits 32]

global crash_me
crash_me:

	mov eax, 0
	div eax
	ret

global EnableInterrupts
EnableInterrupts:
	sti
	ret

global DisableInterrupts
DisableInterrupts:
	cli
	ret