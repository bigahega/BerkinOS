	.file	"main.c"
	.local	hour
	.comm	hour,4,4
	.local	min
	.comm	min,4,4
	.local	sec
	.comm	sec,4,4
	.local	day
	.comm	day,4,4
	.local	mon
	.comm	mon,4,4
	.local	year
	.comm	year,4,4
	.text
	.globl	_get_cursor
	.type	_get_cursor, @function
_get_cursor:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
#APP
# 13 "main.c" 1
		push %eax;
	push %edx;
	mov %dx, 0x3D4;
	mov %al, 0x0E;
	out %dx, %al;
	inc %dx;
	in %al, %dx;
	mov %bh, %al;
	mov %al, 0x0F;
	dec %dx;
	out %dx;
	inc %dx;
	in %al, %dx;
	mov %bl, %al;
	pop %edx;
	pop %eax;
# 0 "" 2
#NO_APP
	movl	%ebx, %eax
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_get_cursor, .-_get_cursor
	.section	.rodata
.LC0:
	.string	"/"
.LC1:
	.string	"  "
.LC2:
	.string	":"
	.text
	.globl	print_clock
	.type	print_clock, @function
print_clock:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movl	$0, %edi
	call	read_cmos
	movzbl	%al, %eax
	andl	$15, %eax
	movl	%eax, %ebx
	movl	$0, %edi
	call	read_cmos
	shrb	$4, %al
	movzbl	%al, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	addl	%ebx, %eax
	movl	%eax, sec(%rip)
	movl	$2, %edi
	call	read_cmos
	movzbl	%al, %eax
	andl	$15, %eax
	movl	%eax, %ebx
	movl	$2, %edi
	call	read_cmos
	shrb	$4, %al
	movzbl	%al, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	addl	%ebx, %eax
	movl	%eax, min(%rip)
	movl	$4, %edi
	call	read_cmos
	movzbl	%al, %eax
	andl	$15, %eax
	movl	%eax, %ebx
	movl	$4, %edi
	call	read_cmos
	shrb	$4, %al
	movzbl	%al, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	addl	%ebx, %eax
	movl	%eax, hour(%rip)
	movl	$7, %edi
	call	read_cmos
	movzbl	%al, %eax
	andl	$15, %eax
	movl	%eax, %ebx
	movl	$7, %edi
	call	read_cmos
	shrb	$4, %al
	movzbl	%al, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	addl	%ebx, %eax
	movl	%eax, day(%rip)
	movl	$8, %edi
	call	read_cmos
	movzbl	%al, %eax
	andl	$15, %eax
	movl	%eax, %ebx
	movl	$8, %edi
	call	read_cmos
	shrb	$4, %al
	movzbl	%al, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	addl	%ebx, %eax
	movl	%eax, mon(%rip)
	movl	$9, %edi
	call	read_cmos
	movzbl	%al, %eax
	andl	$15, %eax
	movl	%eax, %ebx
	movl	$9, %edi
	call	read_cmos
	shrb	$4, %al
	movzbl	%al, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	addl	%ebx, %eax
	movl	%eax, year(%rip)
	movb	$0, -17(%rbp)
	movb	$62, -18(%rbp)
	movl	$0, %eax
	call	get_cursor
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$5, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movb	%al, -25(%rbp)
	movl	-24(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$5, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	movb	%dl, -26(%rbp)
	movzbl	-17(%rbp), %edx
	movzbl	-18(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	set_cur
	movl	$4, %edi
	movl	$0, %eax
	call	set_forecolor
	movl	day(%rip), %eax
	cmpl	$9, %eax
	ja	.L4
	movl	$0, %edi
	movl	$0, %eax
	call	monitor_write_dec
.L4:
	movl	day(%rip), %eax
	movl	%eax, %edi
	movl	$0, %eax
	call	monitor_write_dec
	movl	$2, %edi
	movl	$0, %eax
	call	set_forecolor
	movl	$.LC0, %edi
	call	monitor_write
	movl	$4, %edi
	movl	$0, %eax
	call	set_forecolor
	movl	mon(%rip), %eax
	cmpl	$9, %eax
	ja	.L5
	movl	$0, %edi
	movl	$0, %eax
	call	monitor_write_dec
.L5:
	movl	mon(%rip), %eax
	movl	%eax, %edi
	movl	$0, %eax
	call	monitor_write_dec
	movl	$2, %edi
	movl	$0, %eax
	call	set_forecolor
	movl	$.LC0, %edi
	call	monitor_write
	movl	$4, %edi
	movl	$0, %eax
	call	set_forecolor
	movl	year(%rip), %eax
	movl	%eax, %edi
	movl	$0, %eax
	call	monitor_write_dec
	movl	$.LC1, %edi
	call	monitor_write
	movl	$6, %edi
	movl	$0, %eax
	call	set_forecolor
	movl	hour(%rip), %eax
	cmpl	$9, %eax
	ja	.L6
	movl	$0, %edi
	movl	$0, %eax
	call	monitor_write_dec
.L6:
	movl	hour(%rip), %eax
	movl	%eax, %edi
	movl	$0, %eax
	call	monitor_write_dec
	movl	$15, %edi
	movl	$0, %eax
	call	set_forecolor
	movl	$.LC2, %edi
	call	monitor_write
	movl	$6, %edi
	movl	$0, %eax
	call	set_forecolor
	movl	min(%rip), %eax
	cmpl	$9, %eax
	ja	.L7
	movl	$0, %edi
	movl	$0, %eax
	call	monitor_write_dec
.L7:
	movl	min(%rip), %eax
	movl	%eax, %edi
	movl	$0, %eax
	call	monitor_write_dec
	movl	$15, %edi
	movl	$0, %eax
	call	set_forecolor
	movl	$.LC2, %edi
	call	monitor_write
	movl	$6, %edi
	movl	$0, %eax
	call	set_forecolor
	movl	sec(%rip), %eax
	cmpl	$9, %eax
	ja	.L8
	movl	$0, %edi
	movl	$0, %eax
	call	monitor_write_dec
.L8:
	movl	sec(%rip), %eax
	movl	%eax, %edi
	movl	$0, %eax
	call	monitor_write_dec
	movzbl	-25(%rbp), %edx
	movzbl	-26(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	set_cur
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	print_clock, .-print_clock
	.globl	init_clock
	.type	init_clock, @function
init_clock:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	$print_clock, %esi
	movl	$32, %edi
	call	register_interrupt_handler
	movl	$1193180, %eax
	movl	$0, %edx
	divl	-20(%rbp)
	movl	%eax, -4(%rbp)
	movl	$54, %esi
	movl	$67, %edi
	call	outb
	movl	-4(%rbp), %eax
	movb	%al, -5(%rbp)
	movl	-4(%rbp), %eax
	shrl	$8, %eax
	movb	%al, -6(%rbp)
	movzbl	-5(%rbp), %eax
	movl	%eax, %esi
	movl	$64, %edi
	call	outb
	movzbl	-6(%rbp), %eax
	movl	%eax, %esi
	movl	$64, %edi
	call	outb
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	init_clock, .-init_clock
	.section	.rodata
.LC3:
	.string	"Welcome to OSx383 Kernel...\n"
.LC4:
	.string	"[OSx383]$ "
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	$0, %eax
	call	init_descriptor_tables
	movl	$0, %eax
	call	monitor_clear
	movl	$20, %edi
	call	init_clock
	movl	$1, %edi
	movl	$0, %eax
	call	set_forecolor
	movl	$.LC3, %edi
	call	monitor_write
	movl	$15, %edi
	movl	$0, %eax
	call	set_forecolor
	movl	$.LC4, %edi
	call	monitor_write
#APP
# 110 "main.c" 1
	sti
# 0 "" 2
#NO_APP
	movl	$-559039814, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.2 20131212 (Red Hat 4.8.2-7)"
	.section	.note.GNU-stack,"",@progbits
