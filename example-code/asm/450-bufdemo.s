	.file	"450-bufdemo.c"
	.text
	.globl	gets
	.type	gets, @function
gets:
.LFB38:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, %rbp
	movq	%rdi, %rbx
	jmp	.L2
.L4:
	movb	%al, (%rbx)
	leaq	1(%rbx), %rbx
.L2:
	movq	stdin(%rip), %rdi
	call	_IO_getc
	cmpl	$10, %eax
	je	.L3
	cmpl	$-1, %eax
	jne	.L4
.L3:
	cmpl	$-1, %eax
	sete	%dl
	cmpq	%rbp, %rbx
	sete	%al
	testb	%al, %dl
	jne	.L6
	movb	$0, (%rbx)
	movq	%rbp, %rax
	jmp	.L5
.L6:
	movl	$0, %eax
.L5:
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE38:
	.size	gets, .-gets
	.globl	echo
	.type	echo, @function
echo:
.LFB39:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%rsp, %rdi
	call	gets
	movq	%rsp, %rdi
	call	puts
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE39:
	.size	echo, .-echo
	.globl	good_echo
	.type	good_echo, @function
good_echo:
.LFB40:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	stdin(%rip), %rdx
	movl	$8, %esi
	movq	%rsp, %rdi
	call	fgets
	testq	%rax, %rax
	je	.L10
	movq	%rax, %rdi
	call	puts
.L10:
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE40:
	.size	good_echo, .-good_echo
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Type a string:"
	.text
	.globl	main
	.type	main, @function
main:
.LFB41:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	%edi, %ebx
	movl	$.LC0, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	cmpl	$1, %ebx
	jle	.L14
	movl	$0, %eax
	call	good_echo
	jmp	.L15
.L14:
	movl	$0, %eax
	call	echo
.L15:
	movl	$0, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE41:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
