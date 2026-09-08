%include "platform.inc"

section .text
global NAME(ft_strcmp)

NAME(ft_strcmp):
	xor		rcx, rcx

.loop:
	mov		al, [rdi + rcx]
	mov		dl, [rsi + rcx]
	cmp		al, dl
	jne		.diff
	test	al, al
	je		.equal
	inc		rcx
	jmp		.loop

.diff:
	movzx	eax, al
	movzx	edx, dl
	sub		eax, edx
	ret

.equal:
	xor		eax, eax
	ret
