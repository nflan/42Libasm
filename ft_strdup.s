%include "platform.inc"

section .text
global NAME(ft_strdup)
extern NAME(malloc)
extern NAME(ft_strlen)
extern NAME(ft_strcpy)

NAME(ft_strdup):
	push	rdi
	call	NAME(ft_strlen)
	inc		rax
	mov		rdi, rax
	call	NAME(malloc)
	test	rax, rax
	je		.malloc_failed
	mov		rdi, rax
	mov		rsi, [rsp]
	call	NAME(ft_strcpy)
	add		rsp, 8
	ret

.malloc_failed:
	add		rsp, 8
	ret
