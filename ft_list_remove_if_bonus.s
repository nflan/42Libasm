section .text
global _ft_list_remove_if
extern _free

_ft_list_remove_if:
	test	rdi, rdi
	jz		.done
	test	rdx, rdx
	jz		.done
	test	rcx, rcx
	jz		.done

	push	r12
	push	r13
	push	r14
	push	r15
	sub		rsp, 8

	mov		r12, rsi
	mov		r13, rdx
	mov		r14, rcx
	mov		r15, rdi

.loop:
	mov		r9, [r15]
	test	r9, r9
	jz		.finish
	mov		[rsp], r9

	mov		rdi, [r9]
	mov		rsi, r12
	call	r13
	test	eax, eax
	jnz		.keep

	mov		r9, [rsp]
	mov		rdi, [r9]
	call	r14

	mov		r9, [rsp]
	mov		rax, [r9 + 8]
	mov		[r15], rax
	mov		rdi, r9
	call	_free
	jmp		.loop

.keep:
	mov		r9, [rsp]
	lea		r15, [r9 + 8]
	jmp		.loop

.finish:
	add		rsp, 8
	pop		r15
	pop		r14
	pop		r13
	pop		r12

.done:
	ret
