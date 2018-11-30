	.file	"170-dw.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	dw_loop
	.type	dw_loop, @function
dw_loop:
.LFB0:
	.cfi_startproc
	movq	%rdi, %rcx
	leaq	(%rdi,%rdi), %rdx
	movq	%rdi, %rax
	imulq	%rdi, %rcx
	.p2align 4,,10
	.p2align 3
.L2:
	subq	$1, %rdx
	leaq	1(%rcx,%rax), %rax
	testq	%rdx, %rdx
	jg	.L2
	rep ret
	.cfi_endproc
.LFE0:
	.size	dw_loop, .-dw_loop
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
