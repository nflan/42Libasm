section .text
global _ft_list_sort

_ft_list_sort:
	test	rdi, rdi
	jz		.done
	test	rsi, rsi
	jz		.done
	mov		rax, [rdi]
	test	rax, rax
	jz		.done

	push	rbx
	push	r12
	push	r13
	sub		rsp, 8
	mov		rbx, rdi
	mov		r12, rsi

.outer:
	xor		r13d, r13d
	mov		rdx, [rbx]

.inner:
	test	rdx, rdx
	jz		.after_inner
	mov		rcx, [rdx + 8]
	test	rcx, rcx
	jz		.after_inner

	push	rdx
	push	rcx
	mov		rdi, [rdx]
	mov		rsi, [rcx]
	call	r12
	pop		rcx
	pop		rdx

	cmp		eax, 0
	jle		.no_swap
	mov		r8, [rdx]
	mov		r9, [rcx]
	mov		[rdx], r9
	mov		[rcx], r8
	mov		r13d, 1

.no_swap:
	mov		rdx, rcx
	jmp		.inner

.after_inner:
	test	r13d, r13d
	jnz		.outer

	add		rsp, 8
	pop		r13
	pop		r12
	pop		rbx

.done:
	ret
