section .text
global _ft_atoi_base

_ft_atoi_base:
	test	rdi, rdi
	jz		.invalid
	test	rsi, rsi
	jz		.invalid

	xor		r8d, r8d

.base_check_i:
	mov		al, [rsi + r8]
	test	al, al
	jz		.base_done
	cmp		al, '+'
	je		.invalid
	cmp		al, '-'
	je		.invalid
	cmp		al, 32
	je		.invalid
	cmp		al, 9
	jb		.base_check_dup
	cmp		al, 13
	jbe		.invalid

.base_check_dup:
	mov		r9, r8
	inc		r9

.base_check_j:
	mov		dl, [rsi + r9]
	test	dl, dl
	jz		.base_next_i
	cmp		al, dl
	je		.invalid
	inc		r9
	jmp		.base_check_j

.base_next_i:
	inc		r8
	jmp		.base_check_i

.base_done:
	cmp		r8, 2
	jb		.invalid

	mov		r9, rdi

.skip_space:
	mov		al, [r9]
	cmp		al, 32
	je		.space_next
	cmp		al, 9
	jb		.sign_init
	cmp		al, 13
	jbe		.space_next
	jmp		.sign_init

.space_next:
	inc		r9
	jmp		.skip_space

.sign_init:
	mov		r10d, 1

.sign_loop:
	mov		al, [r9]
	cmp		al, '+'
	je		.sign_plus
	cmp		al, '-'
	je		.sign_minus
	jmp		.convert_init

.sign_plus:
	inc		r9
	jmp		.sign_loop

.sign_minus:
	neg		r10d
	inc		r9
	jmp		.sign_loop

.convert_init:
	xor		eax, eax

.convert_loop:
	mov		dl, [r9]
	test	dl, dl
	jz		.done
	xor		ecx, ecx

.find_digit:
	mov		r11b, [rsi + rcx]
	test	r11b, r11b
	jz		.done
	cmp		dl, r11b
	je		.apply_digit
	inc		rcx
	jmp		.find_digit

.apply_digit:
	imul	eax, r8d
	add		eax, ecx
	inc		r9
	jmp		.convert_loop

.done:
	cmp		r10d, 1
	je		.ret
	neg		eax
	ret

.ret:
	ret

.invalid:
	xor		eax, eax
	ret
