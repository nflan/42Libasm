section .text
global ft_list_size

ft_list_size:
	xor		eax, eax

.loop:
	test	rdi, rdi
	jz		.ret
	inc		eax
	mov		rdi, [rdi + 8]
	jmp		.loop

.ret:
	ret
