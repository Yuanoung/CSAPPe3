	.file	"134-test.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	test
	.type	test, @function
test:
.LFB0:
	.cfi_startproc
	cmpq	$-3, %rdi
	jge	.L2
	cmpq	%rdx, %rsi
	jge	.L3
	movq	%rdi, %rax
	imulq	%rsi, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L2:
	cmpq	$2, %rdi
	jle	.L7
	movq	%rdi, %rax
	imulq	%rdx, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L3:
	movq	%rsi, %rax
	imulq	%rdx, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L7:
	leaq	(%rdi,%rsi), %rax
	addq	%rdx, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	test, .-test
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
