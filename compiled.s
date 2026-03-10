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
	.fp_imm_18: .double 4.44659e-323
	.fp_imm_17: .double 3.95253e-323
	.fp_imm_14: .double 2.47033e-323
	.fp_imm_13: .double 1.97626e-323
	.fp_imm_12: .double 1.4822e-323
	.fp_imm_0: .double 0.1
	.fp_imm_10: .double 4.94066e-324
	.fp_imm_15: .double 2.96439e-323
	.fp_imm_8: .double 5.25526e-315
	.fp_imm_3: .double 0.4
	.fp_imm_7: .double 5.24697e-315
	.fp_imm_16: .double 3.45846e-323
	.fp_imm_5: .double 0.6
	.fp_imm_4: .double 0.5
	.fp_imm_9: .double 0
	.fp_imm_6: .double 0.7
	.fp_imm_19: .double 4.94066e-323
	.fp_imm_2: .double 0.3
	.fp_imm_11: .double 9.88131e-324
	.fp_imm_1: .double 0.2

.section __TEXT,__text
_register:
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
movsd .fp_imm_0(%rip), %xmm0
movsd .fp_imm_1(%rip), %xmm14
movsd %xmm14, -40(%rbp)
movsd .fp_imm_2(%rip), %xmm1
movsd %xmm1, %xmm14
movsd %xmm14, -32(%rbp)
movsd .fp_imm_3(%rip), %xmm1
movsd %xmm1, %xmm14
movsd %xmm14, -24(%rbp)
movsd .fp_imm_4(%rip), %xmm1
movsd %xmm1, %xmm14
movsd %xmm14, -16(%rbp)
movsd .fp_imm_5(%rip), %xmm1
movsd %xmm1, %xmm14
movsd %xmm14, -8(%rbp)
movsd .fp_imm_6(%rip), %xmm13
movss .fp_imm_7(%rip), %xmm12
movss .fp_imm_8(%rip), %xmm11
movsd .fp_imm_9(%rip), %xmm14
movsd %xmm14, -48(%rbp)
movsd .fp_imm_10(%rip), %xmm10
movsd .fp_imm_11(%rip), %xmm9
movsd .fp_imm_12(%rip), %xmm8
movsd .fp_imm_13(%rip), %xmm7
movsd .fp_imm_14(%rip), %xmm6
movsd .fp_imm_15(%rip), %xmm5
movsd .fp_imm_16(%rip), %xmm4
movsd .fp_imm_17(%rip), %xmm3
movss .fp_imm_18(%rip), %xmm2
movss .fp_imm_19(%rip), %xmm1
movsd -40(%rbp), %xmm14
addsd %xmm14, %xmm0
movsd -32(%rbp), %xmm14
addsd %xmm14, %xmm0
movsd -24(%rbp), %xmm14
addsd %xmm14, %xmm0
movsd -16(%rbp), %xmm14
addsd %xmm14, %xmm0
movsd -8(%rbp), %xmm14
addsd %xmm14, %xmm0
addsd %xmm13, %xmm0
cvtss2sd %xmm12, %xmm12
addsd %xmm12, %xmm0
cvtss2sd %xmm11, %xmm11
addsd %xmm11, %xmm0
movsd -48(%rbp), %xmm14
addsd %xmm14, %xmm0
addsd %xmm10, %xmm0
addsd %xmm9, %xmm0
addsd %xmm8, %xmm0
addsd %xmm7, %xmm0
addsd %xmm6, %xmm0
addsd %xmm5, %xmm0
addsd %xmm4, %xmm0
addsd %xmm3, %xmm0
cvtss2sd %xmm2, %xmm2
addsd %xmm2, %xmm0
cvtss2sd %xmm1, %xmm1
addsd %xmm1, %xmm0
movq %rbp, %rsp
popq %rbp
ret

_main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
movq %rbx, -16(%rbp)
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
movq -8(%rbp), %r10
call *%r10
call _print_double
movl $0, %eax
movq -16(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

