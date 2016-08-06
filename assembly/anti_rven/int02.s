	.file	"dr.c"
	.intel_syntax noprefix
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "AAAA\0"
LC1:
	.ascii "BBBB\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB10:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	and	esp, -16
	sub	esp, 48
	call	___main
	xor eax, eax      	# set EAX=0;
	int 0x2d            # invoke the exception handler
	inc eax             # if executed, will set EAX=1
	cmp eax, 0
	JZ _printB         # if EAX=0, will skip printf("BBBB");
	mov	DWORD PTR [esp], OFFSET FLAT:LC0
	call	_printf
	mov	eax, DWORD PTR __imp___iob
	add	eax, 32
	mov	DWORD PTR [esp], eax
	call	_fflush
_printB:
	mov	DWORD PTR [esp+44], 0
	mov	DWORD PTR [esp+40], 0
	mov	DWORD PTR [esp+36], 0
	mov	DWORD PTR [esp+32], 0
	mov	DWORD PTR [esp+28], 0
	mov	DWORD PTR [esp], OFFSET FLAT:LC1
	call	_printf
	mov	eax, DWORD PTR __imp___iob
	add	eax, 32
	mov	DWORD PTR [esp], eax
	call	_fflush
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE10:
	.ident	"GCC: (GNU) 4.8.1"
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_fflush;	.scl	2;	.type	32;	.endef

