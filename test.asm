use64

_test:
	push rbp
	mov	 rbp, rsp
	sub  rsp, $40
	mov qword [rbp - 24], rdi
	mov qword [rbp - 32], rsi
	mov dword [rbp - 36], edx
	cmp qword [rbp - 24], 0
	je	.L2
	cmp qword [rbp - 32], 0
	jne	.L3

.L2:
	cli
	finit
	hlt

.L3:
	mov rax, 1077h
	mov rcx, rax
	hlt

