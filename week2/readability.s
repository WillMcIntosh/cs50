	.file	"readability.c"
	.text
	.section	.rodata
.LC0:
	.string	"Text: "
.LC1:
	.string	"Grade 16+"
.LC2:
	.string	"Before Grade 1"
.LC3:
	.string	"Grade %i\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$.LC0, %esi
	movl	$0, %edi
	movl	$0, %eax
	call	get_string
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	movl	%eax, -12(%rbp)
	movq	-8(%rbp), %rdx
	movl	-12(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	coleman_liau_index
	movl	%eax, -16(%rbp)
	cmpl	$16, -16(%rbp)
	jle	.L2
	movl	$.LC1, %edi
	call	puts
	jmp	.L3
.L2:
	cmpl	$0, -16(%rbp)
	jg	.L4
	movl	$.LC2, %edi
	call	puts
	jmp	.L3
.L4:
	movl	-16(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
.L3:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	coleman_liau_index
	.type	coleman_liau_index, @function
coleman_liau_index:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	movb	$32, -13(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L7
.L10:
	call	__ctype_b_loc
	movq	(%rax), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rcx
	movq	-64(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rdx), %edx
	movsbq	%dl, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$1024, %eax
	testl	%eax, %eax
	je	.L8
	addl	$1, -4(%rbp)
	call	__ctype_b_loc
	movq	(%rax), %rax
	movsbq	-13(%rbp), %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L9
	addl	$1, -8(%rbp)
	jmp	.L9
.L8:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	is_ending
	testb	%al, %al
	je	.L9
	addl	$1, -12(%rbp)
.L9:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movb	%al, -13(%rbp)
	addl	$1, -20(%rbp)
.L7:
	movl	-20(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jl	.L10
	cvtsi2ssl	-4(%rbp), %xmm0
	cvtsi2ssl	-8(%rbp), %xmm1
	divss	%xmm1, %xmm0
	movaps	%xmm0, %xmm1
	movss	.LC4(%rip), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -28(%rbp)
	cvtsi2ssl	-12(%rbp), %xmm0
	cvtsi2ssl	-8(%rbp), %xmm1
	divss	%xmm1, %xmm0
	movaps	%xmm0, %xmm1
	movss	.LC4(%rip), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -32(%rbp)
	cvtss2sd	-28(%rbp), %xmm1
	movsd	.LC5(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	cvtss2sd	-32(%rbp), %xmm2
	movsd	.LC6(%rip), %xmm1
	mulsd	%xmm2, %xmm1
	subsd	%xmm1, %xmm0
	movsd	.LC7(%rip), %xmm1
	subsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -36(%rbp)
	movl	$0, -24(%rbp)
	movss	-36(%rbp), %xmm0
	movss	.LC8(%rip), %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L11
	movss	-36(%rbp), %xmm1
	movss	.LC9(%rip), %xmm0
	addss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %eax
	movl	%eax, -24(%rbp)
.L11:
	movl	-24(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	coleman_liau_index, .-coleman_liau_index
	.globl	is_ending
	.type	is_ending, @function
is_ending:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	cmpb	$46, -4(%rbp)
	je	.L16
	cmpb	$33, -4(%rbp)
	je	.L16
	cmpb	$63, -4(%rbp)
	je	.L16
	cmpb	$58, -4(%rbp)
	jne	.L17
.L16:
	movl	$1, %eax
	jmp	.L18
.L17:
	movl	$0, %eax
.L18:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	is_ending, .-is_ending
	.section	.rodata
	.align 4
.LC4:
	.long	1120403456
	.align 8
.LC5:
	.long	2583852325
	.long	1068374792
	.align 8
.LC6:
	.long	4226247819
	.long	1070789033
	.align 8
.LC7:
	.long	2576980378
	.long	1076861337
	.align 4
.LC8:
	.long	1065353216
	.align 4
.LC9:
	.long	1056964608
	.ident	"GCC: (SUSE Linux) 9.3.1 20200406 [revision 6db837a5288ee3ca5ec504fbd5a765817e556ac2]"
	.section	.note.GNU-stack,"",@progbits
