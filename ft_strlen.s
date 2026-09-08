%include "platform.inc"

section .text
global NAME(ft_strlen)

NAME(ft_strlen):
	xor		rax, rax

.loop:
	cmp		byte [rdi + rax], 0
	je		.done
	inc		rax
	jmp		.loop

.done:
	ret
