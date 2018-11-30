	.file	"132-cond-goto.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	cond
	.type	cond, @function
cond:
.LFB0:
	.cfi_startproc
	testq	%rsi, %rsi
	je	.L1
	cmpq	%rdi, (%rsi)
	jge	.L1
	movq	%rdi, (%rsi)
.L2:
.L1:
	rep ret
	.cfi_endproc
.LFE0:
	.size	cond, .-cond
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
