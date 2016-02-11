a.out:
(__TEXT,__text) section
_main:
0000000100000f40	pushq	%rbp
0000000100000f41	movq	%rsp, %rbp
0000000100000f44	subq	$0x10, %rsp
0000000100000f48	leaq	0x4b(%rip), %rdi        ## literal pool for: "%d"
0000000100000f4f	movl	$0x0, -0x4(%rbp)
0000000100000f56	movl	$0x5, -0x8(%rbp)
0000000100000f5d	movl	-0x8(%rbp), %esi
0000000100000f60	movb	$0x0, %al
0000000100000f62	callq	0x100000f78             ## symbol stub for: _printf
0000000100000f67	movl	$0x3, %esi
0000000100000f6c	movl	%eax, -0xc(%rbp)
0000000100000f6f	movl	%esi, %eax
0000000100000f71	addq	$0x10, %rsp
0000000100000f75	popq	%rbp
0000000100000f76	retq