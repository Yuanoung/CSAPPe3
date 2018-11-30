	.file	"480-charbuf.c"
	.text
	.globl	len
	.type	len, @function
len:
.LFB60:
	.cfi_startproc
	movl	$0, %eax
	movq	$-1, %rcx
	repnz scasb
	movq	%rcx, %rax
	notq	%rax
	subq	$1, %rax
	ret
	.cfi_endproc
.LFE60:
	.size	len, .-len
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%ld"
	.text
	.globl	iptoa
	.type	iptoa, @function
iptoa:
.LFB61:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movq	(%rsi), %r8
	movl	$.LC0, %ecx
	movq	$-1, %rdx
	movl	$1, %esi
	movl	$0, %eax
	call	__sprintf_chk
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE61:
	.size	iptoa, .-iptoa
	.globl	intlen
	.type	intlen, @function
intlen:
.LFB62:
	.cfi_startproc
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	%rdi, 24(%rsp)
	leaq	24(%rsp), %rsi
	movq	%rsp, %rdi
	call	iptoa
	movq	%rsp, %rdi
	call	len
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE62:
	.size	intlen, .-intlen
	.section	.rodata.str1.1
.LC1:
	.string	"%d"
	.text
	.globl	itoa
	.type	itoa, @function
itoa:
.LFB63:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	%esi, %r8d
	movl	$.LC1, %ecx
	movq	$-1, %rdx
	movl	$1, %esi
	movl	$0, %eax
	call	__sprintf_chk
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE63:
	.size	itoa, .-itoa
	.globl	storeint
	.type	storeint, @function
storeint:
.LFB64:
	.cfi_startproc
	movl	%edi, (%rsi)
	ret
	.cfi_endproc
.LFE64:
	.size	storeint, .-storeint
	.globl	intlen2
	.type	intlen2, @function
intlen2:
.LFB65:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	leaq	12(%rsp), %rsi
	call	storeint
	movl	12(%rsp), %esi
	movq	%rsp, %rdi
	call	itoa
	movq	%rsp, %rdi
	call	len
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE65:
	.size	intlen2, .-intlen2
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
