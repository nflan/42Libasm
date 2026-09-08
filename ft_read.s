%include "platform.inc"

section .text
global NAME(ft_read)
extern ERRNO_FN

NAME(ft_read):
	mov		rax, SYS_READ
	syscall
%ifidn __OUTPUT_FORMAT__, elf64
	cmp		rax, 0
	jl		.error
	ret

.error:
	neg		rax
%else
	jc		.error
	ret

.error:
%endif
	push	rax
	call	ERRNO_FN
	pop		rdx
	mov		[rax], edx
	mov		rax, -1
	ret
