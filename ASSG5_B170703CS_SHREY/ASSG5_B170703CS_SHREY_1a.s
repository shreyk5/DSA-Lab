	.file	"ASSG5_B170703CS_SHREY_1a.c"
	.text
	.globl	N
	.section	.rodata
	.align 4
	.type	N, @object
	.size	N, 4
N:
	.long	10000
	.comm	fp,8,8
	.comm	fo,8,8
	.comm	parent,4004,32
	.comm	Rank,4004,32
	.comm	Size,4004,32
	.text
	.globl	make_set
	.type	make_set, @function
make_set:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	leaq	parent(%rip), %rax
	movl	-4(%rbp), %edx
	movl	%edx, (%rcx,%rax)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Rank(%rip), %rax
	movl	$0, (%rdx,%rax)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Size(%rip), %rax
	movl	$1, (%rdx,%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	make_set, .-make_set
	.globl	find_set
	.type	find_set, @function
find_set:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	parent(%rip), %rax
	movl	(%rdx,%rax), %eax
	cmpl	%eax, -4(%rbp)
	jne	.L3
	movl	-4(%rbp), %eax
	jmp	.L4
.L3:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	parent(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, %edi
	call	find_set
	movl	%eax, %ecx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	parent(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	parent(%rip), %rax
	movl	(%rdx,%rax), %eax
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	find_set, .-find_set
	.globl	union_set
	.type	union_set, @function
union_set:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, %edi
	call	find_set
	movl	%eax, -8(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, %edi
	call	find_set
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	cmpl	-4(%rbp), %eax
	je	.L9
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Rank(%rip), %rax
	movl	(%rdx,%rax), %edx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	leaq	Rank(%rip), %rax
	movl	(%rcx,%rax), %eax
	cmpl	%eax, %edx
	jne	.L7
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	leaq	parent(%rip), %rax
	movl	-8(%rbp), %edx
	movl	%edx, (%rcx,%rax)
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Rank(%rip), %rax
	movl	(%rdx,%rax), %eax
	leal	1(%rax), %ecx
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Rank(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Size(%rip), %rax
	movl	(%rdx,%rax), %edx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	leaq	Size(%rip), %rax
	movl	(%rcx,%rax), %eax
	leal	(%rdx,%rax), %ecx
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Size(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	jmp	.L9
.L7:
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Rank(%rip), %rax
	movl	(%rdx,%rax), %edx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	leaq	Rank(%rip), %rax
	movl	(%rcx,%rax), %eax
	cmpl	%eax, %edx
	jle	.L8
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	leaq	parent(%rip), %rax
	movl	-8(%rbp), %edx
	movl	%edx, (%rcx,%rax)
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Size(%rip), %rax
	movl	(%rdx,%rax), %edx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	leaq	Size(%rip), %rax
	movl	(%rcx,%rax), %eax
	leal	(%rdx,%rax), %ecx
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Size(%rip), %rax
	movl	%ecx, (%rdx,%rax)
	jmp	.L9
.L8:
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	leaq	parent(%rip), %rax
	movl	-4(%rbp), %edx
	movl	%edx, (%rcx,%rax)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Size(%rip), %rax
	movl	(%rdx,%rax), %edx
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	leaq	Size(%rip), %rax
	movl	(%rcx,%rax), %eax
	leal	(%rdx,%rax), %ecx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	Size(%rip), %rax
	movl	%ecx, (%rdx,%rax)
.L9:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	union_set, .-union_set
	.globl	init_graph
	.type	init_graph, @function
init_graph:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$16, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movl	$12012, %edi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	init_graph, .-init_graph
	.globl	cmp
	.type	cmp, @function
cmp:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	movl	8(%rax), %edx
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	%eax, %edx
	setg	%al
	movzbl	%al, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	cmp, .-cmp
	.globl	push_edge
	.type	push_edge, @function
push_edge:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -36(%rbp)
	movl	%esi, -40(%rbp)
	movl	%edx, -44(%rbp)
	movl	-36(%rbp), %eax
	movl	%eax, -24(%rbp)
	movl	-40(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-44(%rbp), %eax
	movl	%eax, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -12(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -4(%rbp)
	movq	-12(%rbp), %rdx
	movl	-4(%rbp), %eax
	movq	%rdx, %rcx
	movl	%eax, %edx
	movq	%rcx, %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	push_edge, .-push_edge
	.section	.rodata
.LC0:
	.string	"%d--%d\n"
	.text
	.globl	kruskal
	.type	kruskal, @function
kruskal:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movl	$0, -24(%rbp)
	jmp	.L17
.L18:
	movl	-24(%rbp), %eax
	movl	%eax, %edi
	call	make_set
	addl	$1, -24(%rbp)
.L17:
	movq	-40(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, -24(%rbp)
	jl	.L18
	movq	-40(%rbp), %rax
	movl	4(%rax), %eax
	movslq	%eax, %rsi
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	leaq	cmp(%rip), %rcx
	movl	$12, %edx
	movq	%rax, %rdi
	call	qsort@PLT
	movl	$0, -20(%rbp)
	jmp	.L19
.L21:
	movq	-40(%rbp), %rax
	movq	8(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	movl	%eax, %edi
	call	find_set
	movl	%eax, %ebx
	movq	-40(%rbp), %rax
	movq	8(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	4(%rax), %eax
	movl	%eax, %edi
	call	find_set
	cmpl	%eax, %ebx
	je	.L20
	movq	-40(%rbp), %rax
	movq	8(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	4(%rax), %ecx
	movq	-40(%rbp), %rax
	movq	8(%rax), %rsi
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rsi, %rax
	movl	(%rax), %eax
	movl	%ecx, %edx
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-40(%rbp), %rax
	movq	8(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	4(%rax), %ecx
	movq	-40(%rbp), %rax
	movq	8(%rax), %rsi
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rsi, %rax
	movl	(%rax), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	union_set
.L20:
	addl	$1, -20(%rbp)
.L19:
	movq	-40(%rbp), %rax
	movl	4(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L21
	nop
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	kruskal, .-kruskal
	.section	.rodata
.LC1:
	.string	"%d%d%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movl	$0, %eax
	call	init_graph
	movq	%rax, -32(%rbp)
	movl	$0, -40(%rbp)
	movq	-32(%rbp), %rax
	movl	$4, (%rax)
	movq	-32(%rbp), %rax
	movl	$5, 4(%rax)
	movl	$0, -36(%rbp)
	jmp	.L23
.L24:
	leaq	-44(%rbp), %rcx
	leaq	-48(%rbp), %rdx
	leaq	-52(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-44(%rbp), %edi
	movl	-48(%rbp), %esi
	movl	-52(%rbp), %ecx
	movq	-32(%rbp), %rax
	movq	8(%rax), %r8
	movl	-40(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -40(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	leaq	(%r8,%rax), %rbx
	movl	%edi, %edx
	movl	%ecx, %edi
	call	push_edge
	movq	%rax, %rcx
	movl	%edx, %eax
	movq	%rcx, (%rbx)
	movl	%eax, 8(%rbx)
	addl	$1, -36(%rbp)
.L23:
	cmpl	$4, -36(%rbp)
	jle	.L24
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	kruskal
	movl	$0, %eax
	movq	-24(%rbp), %rbx
	xorq	%fs:40, %rbx
	je	.L26
	call	__stack_chk_fail@PLT
.L26:
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
