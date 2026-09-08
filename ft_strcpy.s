%include "platform.inc"

section .text
global NAME(ft_strcpy)

NAME(ft_strcpy):
	mov		rax, rdi

.loop:
	mov		dl, [rsi]
	mov		[rdi], dl
	inc		rsi
	inc		rdi
	test	dl, dl
	jne		.loop
	ret
