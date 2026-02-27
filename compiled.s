.att_syntax prefix
.global main

.extern list_size
.extern list_equals
.extern read_string
.extern access_index
.extern struct_equals
.extern decr_closure
.extern access_field
.extern allocate_closure
.extern decr_list
.extern allocate_env
.extern incr_closure
.extern get_env
.extern access_var
.extern print_int
.extern incr_list
.extern decr_struct
.extern concat_list

.section .data
.align 8
main.local:
	.quad 0
	.quad main
	.long 1
list_check.local:
	.quad 0
	.quad list_check
	.long 1
div_check.local:
	.quad 0
	.quad div_check
	.long 1
nest_check.local:
	.quad 0
	.quad nest_check
	.long 1
atoi.local:
	.quad 0
	.quad atoi
	.long 1
factorial.local:
	.quad 0
	.quad factorial
	.long 1
get_val.local:
	.quad 0
	.quad get_val
	.long 1

.section .rodata
.align 8

.section .text
list_check:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
movq %rsi, -8(%rbp)
movq %rdx, -16(%rbp)
movq $0, %rdi
movq -8(%rbp), %rsi
call concat_list
movq %rax, %rbx
movq -8(%rbp), %rdi
call incr_list
movq %rbx, %rdi
movq -16(%rbp), %rsi
call concat_list
movq %rax, %rbx
movq -16(%rbp), %rdi
call incr_list
movq -8(%rbp), %rdi
call decr_list
movq -16(%rbp), %rdi
call decr_list
movq %rbx, %rdi
call decr_list
movl $0, %eax
movq %rbp, %rsp
popq %rbp
ret

factorial:
pushq %rbp
movq %rsp, %rbp
subq $8, %rsp
movl %esi, -8(%rbp)
movl -8(%rbp), %eax
cmpl %eax, $1
setgb %al
xorb $1, %al
testb %al, %al
jnz .L_0
movl -8(%rbp), %eax
cmpl %eax, $10
setlb %al
xorb $1, %al
testb %al, %al
jnz .L_0
movb $1, %al
jmp .L_1
.L_0
movb $0, %al
.L_1
testb %al, %al
jnz .L_F3_1_1_B1_case0_0
jmp .L_F3_1_1_B1_case0_1
.L_F3_1_1_B1_case0_0
leaq factorial.local(%rip), %rbx
movq %rbx, %rdi
call get_env
movq %rax, %rdi
movl -8(%rbp), %eax
movl %eax, %esi
subl $1, %esi
call *%rbx
movl -8(%rbp), %ebx
movl %ebx, %eax
imull %eax, %eax
movq %rbp, %rsp
popq %rbp
ret
.L_F3_1_1_B1_case0_1
movl $1, %eax
movq %rbp, %rsp
popq %rbp
ret

foo:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
movq %rdi, -8(%rbp)
movl %esi, -16(%rbp)
movq -8(%rbp), %rdi
movl $0, %esi
call access_var
movl (%eax), %eax
cmpb %al, $1
je .L_F4_1_1_1_B1_case0_0
jmp .L_F4_1_1_1_B1_case0_1
.L_F4_1_1_1_B1_case0_0
movq -8(%rbp), %rdi
movl $1, %esi
call access_var
movb (%al), %bl
movsbl %bl, %ebx
movl -16(%rbp), %eax
addl %ebx, %eax
movq %rbp, %rsp
popq %rbp
ret
.L_F4_1_1_1_B1_case0_1
movl $0, %eax
movq %rbp, %rsp
popq %rbp
ret

nest_check:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
movl %esi, -8(%rbp)
movb %dl, -16(%rbp)
movl $0, %edi
call allocate_env
movq %rax, -24(%rbp)
movq -24(%rbp), %rdi
movl $0, %esi
call access_var
movl -8(%rbp), %eax
movl %eax, (%eax)
movq -24(%rbp), %rdi
movl $1, %esi
call access_var
movb -16(%rbp), %al
movb %al, (%al)
leaq foo(%rip), %rdi
movq -24(%rbp), %rsi
call allocate_closure
movq %rax, %r12
movq %r12, %rdi
call incr_closure
movq %r12, %rbx
movq %rbx, %rdi
call incr_closure
movq %rbx, %rdi
call decr_closure
movq %r12, %rdi
call decr_closure
movq %rbx, %rax
movq %rbp, %rsp
popq %rbp
ret

get_val:
pushq %rbp
movq %rsp, %rbp
subq $8, %rsp
movq %rsi, -8(%rbp)
movq -8(%rbp), %rdi
movq $0, %rsi
call struct_equals
testb %al, %al
jnz .L_F5_1_1_B1_case0_0
jmp .L_F5_1_1_B1_case0_1
.L_F5_1_1_B1_case0_0
movq -8(%rbp), %rdi
call decr_struct
movl $0, %eax
movq %rbp, %rsp
popq %rbp
ret
.L_F5_1_1_B1_case0_1
movq -8(%rbp), %rdi
movl $2, %esi
call access_field
movl (%eax), %ebx
movq -8(%rbp), %rdi
call decr_struct
movl %ebx, %eax
movq %rbp, %rsp
popq %rbp
ret

div_check:
pushq %rbp
movq %rsp, %rbp
subq $8, %rsp
movl %edx, %ebx
movl %esi, %eax
cdq
idivl %ebx
movl %edx, %r1d
movl %ebx, %eax
cdq
idivl %esi
movq %rbp, %rsp
popq %rbp
ret

atoi:
pushq %rbp
movq %rsp, %rbp
subq $40, %rsp
movq %rsi, -8(%rbp)
movl %edx, -16(%rbp)
movq -8(%rbp), %rdi
movq $0, %rsi
call list_equals
testb %al, %al
jnz .L_F7_1_1_B1_case0_0
movq -8(%rbp), %rdi
call list_size
cmpl %eax, $1
jge .L_F7_1_1_B1_case0_1
.L_F7_1_1_B1_case0_0
movq -8(%rbp), %rdi
call decr_list
movl -16(%rbp), %eax
movq %rbp, %rsp
popq %rbp
ret
.L_F7_1_1_B1_case0_1
movq -8(%rbp), %rdi
movl $0, %esi
call access_index
movq %rax, -24(%rbp)
movb -24(%rbp), %al
movb (%al), %al
movb %al, -32(%rbp)
movq -8(%rbp), %rdi
movl $1, %esi
call access_index
movq %rax, -24(%rbp)
movq -24(%rbp), %rdi
call incr_list
movb -32(%rbp), %al
cmpb %al, $45
je .L_F7_1_1_B3_case1_0
jmp .L_F7_1_1_B3_case1_1
.L_F7_1_1_B3_case1_0
leaq atoi.local(%rip), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
call get_env
movq %rax, %rdi
movq -24(%rbp), %rsi
movl -16(%rbp), %edx
movl -40(%rbp), %eax
call *%rax
movl $0, %ebx
subl %eax, %ebx
movq -8(%rbp), %rdi
call decr_list
movq -24(%rbp), %rdi
call decr_list
movl %ebx, %eax
movq %rbp, %rsp
popq %rbp
ret
.L_F7_1_1_B3_case1_1
leaq atoi.local(%rip), %rax
movq %rax, -40(%rbp)
movq -40(%rbp), %rdi
call get_env
movq %rax, %rdi
movq -24(%rbp), %rsi
movb -32(%rbp), %al
movb %al, %bl
subb $48, %bl
movl -16(%rbp), %eax
movl $10, %eax
imull %eax, %eax
movsbl %bl, %ebx
movl %ebx, %edx
addl %eax, %edx
movl -40(%rbp), %eax
call *%rax
movl %eax, %ebx
movq -8(%rbp), %rdi
call decr_list
movq -24(%rbp), %rdi
call decr_list
movl %ebx, %eax
movq %rbp, %rsp
popq %rbp
ret

main:
pushq %rbp
movq %rsp, %rbp
subq $40, %rsp
call read_string
movq %rax, -8(%rbp)
leaq atoi.local(%rip), %rax
movq %rax, -16(%rbp)
movq -16(%rbp), %rdi
call get_env
movq %rax, %rdi
movq -8(%rbp), %rsi
movl $0, %edx
movl -16(%rbp), %eax
call *%rax
movl %eax, -24(%rbp)
leaq get_val.local(%rip), %rbx
movq %rbx, %rdi
call get_env
movq %rax, %rdi
movq $0, %rsi
call *%rbx
leaq factorial.local(%rip), %rbx
movq %rbx, %rdi
call get_env
movq %rax, %rdi
movl -24(%rbp), %esi
call *%rbx
call print_int
leaq nest_check.local(%rip), %rax
movq %rax, -32(%rbp)
movq -32(%rbp), %rdi
call get_env
movq %rax, %rdi
movl $1, %esi
movb $97, %dl
movq -32(%rbp), %rax
call *%rax
movq %rax, %rbx
movq %rbx, %rdi
call get_env
movq %rax, %rdi
movl $2, %esi
call *%rbx
movl %eax, %ebx
movq -8(%rbp), %rdi
call decr_list
movl %ebx, %eax
movq %rbp, %rsp
popq %rbp
ret

