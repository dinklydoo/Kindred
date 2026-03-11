.att_syntax prefix
.global _main

.extern _get_env
.extern _get_function
.extern _init_struct_layout
.extern _init_env_layout
.extern _incr_closure
.extern _decr_closure
.extern _allocate_closure
.extern _allocate_env
.extern _print_int
.extern _access_var

.section __DATA,__data
.align 8
main.local:
	.quad 0
	.quad _main
	.long 1
	.long 0
outer.local:
	.quad 0
	.quad _outer
	.long 1
	.long 0

.section __TEXT,__const
.align 8

.section __TEXT,__text
_generate:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
movq %rbx, -24(%rbp)
movq %rdi, %r10
movq %r10, -16(%rbp)
movq -16(%rbp), %r10
movq %r10, %rdi
movl $0, %esi
call _access_var
movl (%rax), %r10d
movl %r10d, -8(%rbp)
movq -16(%rbp), %r10
movq %r10, %rdi
movl $1, %esi
call _access_var
movl (%rax), %ebx
movl -8(%rbp), %r10d
movl %r10d, %eax
addl %ebx, %eax
movq -24(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

_outer:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
movq %rbx, -32(%rbp)
movl %esi, %r10d
movl %r10d, -16(%rbp)
movl %edx, %r10d
movl %r10d, -8(%rbp)
movl $0, %edi
call _allocate_env
movq %rax, %r10
movq %r10, -24(%rbp)
movq -24(%rbp), %r10
movq %r10, %rdi
movl $0, %esi
call _access_var
movl -16(%rbp), %r10d
movl %r10d, (%rax)
movq -24(%rbp), %r10
movq %r10, %rdi
movl $1, %esi
call _access_var
movl -8(%rbp), %r10d
movl %r10d, (%rax)
leaq _generate(%rip), %rdi
movq -24(%rbp), %r10
movq %r10, %rsi
call _allocate_closure
movq %rax, %rbx
movq %rbx, %rdi
call _incr_closure
movq %rbx, %rdi
call _decr_closure
movq %rbx, %rax
movq -32(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

_main:
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
movq %rbx, -48(%rbp)
call _init_env_layout
call _init_struct_layout
movl $3, %r10d
movl %r10d, -16(%rbp)
movl $7, %r10d
movl %r10d, -8(%rbp)
leaq outer.local(%rip), %rbx
movq %rbx, %rdi
call _get_function
movq %rax, %r10
movq %r10, -24(%rbp)
movq %rbx, %rdi
call _get_env
movq %rax, %rdi
movl -16(%rbp), %r10d
movl %r10d, %esi
movl -8(%rbp), %r10d
movl %r10d, %edx
movq -24(%rbp), %r10
call *%r10
movq %rax, %r10
movq %r10, -40(%rbp)
movq -40(%rbp), %r10
movq %r10, %rdi
call _incr_closure
movq -40(%rbp), %r10
movq %r10, %rdi
call _get_function
movq %rax, %r10
movq %r10, -32(%rbp)
movq -40(%rbp), %r10
movq %r10, %rdi
call _get_env
movq %rax, %rdi
movq -32(%rbp), %r10
call *%r10
movl %eax, %edi
call _print_int
movq -40(%rbp), %r10
movq %r10, %rdi
call _decr_closure
movl $0, %eax
movq -48(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

