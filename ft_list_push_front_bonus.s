section .text
global _ft_list_push_front
extern _malloc

_ft_list_push_front:
	test	rdi, rdi
	jz		.ret

	sub		rsp, 24
	mov		[rsp], rdi
	mov		[rsp + 8], rsi
	mov		rdi, 16
	call	_malloc
	test	rax, rax
	jz		.cleanup

	mov		rdx, [rsp + 8]
	mov		[rax], rdx
	mov		rdx, [rsp]
	mov		rdx, [rdx]
	mov		[rax + 8], rdx
	mov		rdx, [rsp]
	mov		[rdx], rax

.cleanup:
	add		rsp, 24

.ret:
	ret
