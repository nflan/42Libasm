%include "platform.inc"

section .text
global NAME(ft_list_size)

NAME(ft_list_size):
	xor		eax, eax

.loop:
	test	rdi, rdi
	jz		.ret
	inc		eax
	mov		rdi, [rdi + 8]
	jmp		.loop

.ret:
	ret
