.att_syntax prefix
.global _main

.extern _print_int
.extern _init_struct_layout
.extern _init_env_layout
.extern _get_env
.extern _get_function
.extern _list_equals
.extern _index_list
.extern _decr_list
.extern _access_node
.extern _list_size
.extern _read_string
.extern _incr_list

.section __DATA,__data
.align 8
main.local:
	.quad 0
	.quad _main
	.long 1
	.long 0
atoi.local:
	.quad 0
	.quad _atoi
	.long 1
	.long 0

.section __TEXT,__const
.align 8

.section __TEXT,__text
_atoi:
pushq %rbp
movq %rsp, %rbp
subq $80, %rsp
movq %rsi, %r10
movq %r10, -16(%rbp)
movl %edx, %r10d
movl %r10d, -8(%rbp)
movq -16(%rbp), %r10
movq %r10, %rdi
call _incr_list
movq -16(%rbp), %r10
movq %r10, %rdi
movq $0, %rsi
call _list_equals
movq %r10, -72(%rbp)
movb -72(%rbp), %r10b
testb %r10b, %r10b
jnz .L_F2_1_1_B1_case0_0
movq -16(%rbp), %r10
movq %r10, %rdi
call _list_size
cmpl $1, %eax
jge .L_F2_1_1_B1_case0_1
mov -72(%rbp), %r10
.L_F2_1_1_B1_case0_0:
mov %r11, -72(%rbp)
movq -16(%rbp), %r10
movq %r10, %rdi
call _decr_list
movl -8(%rbp), %r10d
movl %r10d, %eax
movq %rbp, %rsp
popq %rbp
ret
mov -72(%rbp), %r10
.L_F2_1_1_B1_case0_1:
mov %r11, -72(%rbp)
movq -16(%rbp), %r10
movq %r10, %rdi
movl $0, %esi
call _index_list
movb (%rax), %r10b
movb %r10b, -32(%rbp)
movq -16(%rbp), %r10
movq %r10, %rdi
movl $1, %esi
call _access_node
movq %rax, %r10
movq %r10, -24(%rbp)
movq -24(%rbp), %r10
movq %r10, %rdi
call _incr_list
movb -32(%rbp), %r10b
cmpb $45, %r10b
je .L_F2_1_1_B3_case1_0
jmp .L_F2_1_1_B3_case1_1
mov -72(%rbp), %r10
.L_F2_1_1_B3_case1_0:
mov %r11, -72(%rbp)
leaq atoi.local(%rip), %r10
movq %r10, -56(%rbp)
movq -56(%rbp), %r10
movq %r10, %rdi
call _get_function
movq %rax, %r10
movq %r10, -40(%rbp)
movq -56(%rbp), %r10
movq %r10, %rdi
call _get_env
movq %rax, %rdi
movq -24(%rbp), %r10
movq %r10, %rsi
movl -8(%rbp), %r10d
movl %r10d, %edx
movq -40(%rbp), %r10
call *%r10
movl $0, %r10d
movl %r10d, -80(%rbp)
movl -80(%rbp), %r10d
subl %eax, %r11d
movl %r11d, -80(%rbp)
movq -16(%rbp), %r10
movq %r10, %rdi
call _decr_list
movq -24(%rbp), %r10
movq %r10, %rdi
call _decr_list
movl -80(%rbp), %r10d
movl %r10d, %eax
movq %rbp, %rsp
popq %rbp
ret
mov -72(%rbp), %r10
.L_F2_1_1_B3_case1_1:
mov %r11, -72(%rbp)
movb -32(%rbp), %r10b
subb $48, %r11b
movb %r11b, -32(%rbp)
movl $10, %eax
movl -8(%rbp), %r10d
imull %r10d, %eax
movb -32(%rbp), %r10b
movzbl %r10b, %r11d
movl %r11d, -32(%rbp)
movl -32(%rbp), %r10d
addl %eax, %r11d
movl %r11d, -32(%rbp)
leaq atoi.local(%rip), %r10
movq %r10, -56(%rbp)
movq -56(%rbp), %r10
movq %r10, %rdi
call _get_function
movq %rax, %r10
movq %r10, -48(%rbp)
movq -56(%rbp), %r10
movq %r10, %rdi
call _get_env
movq %rax, %rdi
movq -24(%rbp), %r10
movq %r10, %rsi
movl -32(%rbp), %r10d
movl %r10d, %edx
movq -48(%rbp), %r10
call *%r10
movl %eax, %r10d
movl %r10d, -64(%rbp)
movq -16(%rbp), %r10
movq %r10, %rdi
call _decr_list
movq -24(%rbp), %r10
movq %r10, %rdi
call _decr_list
movl -64(%rbp), %r10d
movl %r10d, %eax
movq %rbp, %rsp
popq %rbp
ret

_main:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
movq %rbx, -24(%rbp)
call _init_env_layout
call _init_struct_layout
call _read_string
movq %rax, %r10
movq %r10, -16(%rbp)
leaq atoi.local(%rip), %rbx
movq %rbx, %rdi
call _get_function
movq %rax, %r10
movq %r10, -8(%rbp)
movq %rbx, %rdi
call _get_env
movq %rax, %rdi
movq -16(%rbp), %r10
movq %r10, %rsi
movl $0, %edx
movq -8(%rbp), %r10
call *%r10
movl %eax, %edi
addl $7, %edi
call _print_int
movq -16(%rbp), %r10
movq %r10, %rdi
call _decr_list
movl $0, %eax
movq -24(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

