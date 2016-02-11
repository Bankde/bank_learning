	.section	__TEXT,__text,regular,pure_instructions
	.section	__TEXT,__literal4,4byte_literals
	.align	2
LCPI0_0:
	.long	1095761920              ## float 13
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp2:
	.cfi_def_cfa_offset 16
Ltmp3:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp4:
	.cfi_def_cfa_register %rbp
	movabsq	$15, %rax
	cvtsi2sdq	%rax, %xmm0
	movl	$0, -4(%rbp)
	movl	$5, -8(%rbp)
	movl	$7, -12(%rbp)
	movq	$35, -24(%rbp)
	flds	LCPI0_0(%rip)
	fstpt	-48(%rbp)
	movsd	%xmm0, -56(%rbp)
	movl	-8(%rbp), %eax
	popq	%rbp
	retq
	.cfi_endproc


.subsections_via_symbols
a.out:
(__TEXT,__text) section
_main:
0000000100000f40	pushq	%rbp
0000000100000f41	movq	%rsp, %rbp
0000000100000f44	movabsq	$0xf, %rax
0000000100000f4e	cvtsi2sdq	%rax, %xmm0
0000000100000f53	movl	$0x0, -0x4(%rbp)
0000000100000f5a	movl	$0x5, -0x8(%rbp)
0000000100000f61	movl	$0x7, -0xc(%rbp)
0000000100000f68	movq	$0x23, -0x18(%rbp)
0000000100000f70	flds	0x1a(%rip)
0000000100000f76	fstpt	-0x30(%rbp)
0000000100000f79	movsd	%xmm0, -0x38(%rbp)
0000000100000f7e	movl	$0xb, -0x3c(%rbp)
0000000100000f85	movb	$0x1, -0x3d(%rbp)
0000000100000f89	movl	-0x8(%rbp), %eax
0000000100000f8c	popq	%rbp
0000000100000f8d	retq
