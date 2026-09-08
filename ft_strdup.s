section .text
global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy

ft_strdup:
	push	rdi
	call	ft_strlen
	inc		rax
	mov		rdi, rax
	call	malloc
	test	rax, rax
	je		.malloc_failed
	mov		rdi, rax
	mov		rsi, [rsp]
	call	ft_strcpy
	add		rsp, 8
	ret

.malloc_failed:
	add		rsp, 8
	ret
