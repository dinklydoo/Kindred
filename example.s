.att_syntax prefix
.global _main

.extern _print_double
.extern _get_function
.extern _get_env
.extern _init_struct_layout
.extern _init_env_layout

.section __DATA,__data
.align 8
main.local:
	.quad 0
	.quad _main
	.long 1
	.long 0
register.local:
	.quad 0
	.quad _register
	.long 1
	.long 0

.section __TEXT,__const
.align 8
	.fp_imm_1: .double 0
	.fp_imm_0: .double 4.94066e-323

.section __TEXT,__text
_register:
pushq %rbp
movq %rsp, %rbp
subq $96, %rsp
movq %rbx, -56(%rbp)
movq %r12, -64(%rbp)
movq %r13, -72(%rbp)
movq %r14, -80(%rbp)
movq %r15, -88(%rbp)
movss %xmm0, %xmm2
movsd %xmm1, %xmm2
movl $10, %ebx
movss .fp_imm_0(%rip), %xmm3
movsd .fp_imm_0(%rip), %xmm2
movl $10, %eax
movb $10, %r15b
movl $10, %r14d
movl $10, %r13d
movl $10, %r12d
movl $10, %r9d
movl $10, %r8d
movl $10, %esi
movl $10, %r10d
movl %r10d, -32(%rbp)
movl $10, %r10d
movl %r10d, -8(%rbp)
movl $10, %edi
movl %ebx, %edx
addl %edi, %edx
movl %ebx, %ecx
addl %edx, %ecx
movl $12, %r10d
movl %r10d, -48(%rbp)
movl $12, %r10d
movl %r10d, -40(%rbp)
movl $12, %r10d
movl %r10d, -24(%rbp)
movl $12, %r10d
movl %r10d, -16(%rbp)
cvtsi2ssl %ebx, %xmm1
addss %xmm3, %xmm1
cvtss2sd %xmm1, %xmm1
addsd %xmm2, %xmm1
movslq %eax, %rax
cvtsi2sdq %rax, %xmm0
addsd %xmm0, %xmm1
movsbq %r15b, %r15
cvtsi2sdq %r15, %xmm0
addsd %xmm0, %xmm1
movslq %r14d, %r14
cvtsi2sdq %r14, %xmm0
addsd %xmm0, %xmm1
movslq %r13d, %r13
cvtsi2sdq %r13, %xmm0
addsd %xmm0, %xmm1
movslq %r12d, %r12
cvtsi2sdq %r12, %xmm0
addsd %xmm0, %xmm1
movslq %r9d, %r9
cvtsi2sdq %r9, %xmm0
addsd %xmm0, %xmm1
movslq %r8d, %r8
cvtsi2sdq %r8, %xmm0
addsd %xmm0, %xmm1
movslq %esi, %rsi
cvtsi2sdq %rsi, %xmm0
addsd %xmm0, %xmm1
movl -32(%rbp), %r10d
movslq %r10d, %r10
cvtsi2sdq %r10, %xmm0
addsd %xmm0, %xmm1
movl -8(%rbp), %r10d
movslq %r10d, %r10
cvtsi2sdq %r10, %xmm0
addsd %xmm0, %xmm1
movslq %edi, %rdi
cvtsi2sdq %rdi, %xmm0
addsd %xmm0, %xmm1
movslq %edx, %rdx
cvtsi2sdq %rdx, %xmm0
addsd %xmm0, %xmm1
movslq %ecx, %rcx
cvtsi2sdq %rcx, %xmm0
addsd %xmm0, %xmm1
movl -48(%rbp), %r10d
movslq %r10d, %r10
cvtsi2sdq %r10, %xmm0
addsd %xmm0, %xmm1
movl -40(%rbp), %r10d
movslq %r10d, %r10
cvtsi2sdq %r10, %xmm0
addsd %xmm0, %xmm1
movl -24(%rbp), %r10d
movslq %r10d, %r10
cvtsi2sdq %r10, %xmm0
addsd %xmm0, %xmm1
movl -16(%rbp), %r10d
movslq %r10d, %r10
cvtsi2sdq %r10, %xmm0
addsd %xmm0, %xmm1
movsd %xmm1, %xmm0
movq -88(%rbp), %r15
movq -80(%rbp), %r14
movq -72(%rbp), %r13
movq -64(%rbp), %r12
movq -56(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

_main:
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
movq %rbx, -16(%rbp)
movq %r12, -24(%rbp)
movq %r13, -32(%rbp)
movq %r14, -40(%rbp)
movq %r15, -48(%rbp)
call _init_env_layout
call _init_struct_layout
leaq register.local(%rip), %rbx
movq %rbx, %rdi
call _get_function
movq %rax, %r10
movq %r10, -8(%rbp)
movq %rbx, %rdi
call _get_env
movq %rax, %rdi
movss .fp_imm_1(%rip), %xmm0
movsd .fp_imm_1(%rip), %xmm1
movq -8(%rbp), %r10
call *%r10
call _print_double
movl $0, %eax
movq -48(%rbp), %r15
movq -40(%rbp), %r14
movq -32(%rbp), %r13
movq -24(%rbp), %r12
movq -16(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

