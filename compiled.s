.att_syntax prefix
.global main

.extern access_node
.extern index_list
.extern list_size
.extern list_equals
.extern read_string
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
subq $32, %rsp
movq %rbx, -24(%rbp)
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
movq -24(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

factorial:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
movq %rbx, -24(%rbp)
movl %esi, -8(%rbp)
movl -8(%rbp), %eax
cmpl $1, %eax
setgb %al
xorb $1, %al
testb %al, %al
jnz .L_0
movl -8(%rbp), %eax
cmpl $10, %eax
setlb %al
xorb $1, %al
testb %al, %al
jnz .L_0
movb $1, %al
jmp .L_1
.L_0:
movb $0, %al
.L_1:
testb %al, %al
jnz .L_F3_1_1_B1_case0_0
jmp .L_F3_1_1_B1_case0_1
.L_F3_1_1_B1_case0_0:
leaq factorial.local(%rip), %rax
movq %rax, -16(%rbp)
movq -16(%rbp), %rdi
call get_env
movq %rax, %rdi
movl -8(%rbp), %eax
movl %eax, %esi
subl $1, %esi
movl -16(%rbp), %eax
call *%rax
movl -8(%rbp), %ebx
movl %ebx, %eax
imull %eax, %eax
movq -24(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret
.L_F3_1_1_B1_case0_1:
movl $1, %eax
movq -24(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

foo:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
movq %rbx, -24(%rbp)
movq %rdi, -8(%rbp)
movl %esi, -16(%rbp)
movq -8(%rbp), %rdi
movl $0, %esi
call access_var
movl (%rax), %eax
cmpb $1, %al
je .L_F4_1_1_1_B1_case0_0
jmp .L_F4_1_1_1_B1_case0_1
.L_F4_1_1_1_B1_case0_0:
movq -8(%rbp), %rdi
movl $1, %esi
call access_var
movb (%rax), %bl
movsbl %bl, %ebx
movl -16(%rbp), %eax
addl %ebx, %eax
movq -24(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret
.L_F4_1_1_1_B1_case0_1:
movl $0, %eax
movq -24(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

nest_check:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
movq %rbx, -32(%rbp)
movl %esi, -8(%rbp)
movb %dl, -16(%rbp)
movl $0, %edi
call allocate_env
movq %rax, -24(%rbp)
movq -24(%rbp), %rdi
movl $0, %esi
call access_var
movl -8(%rbp), %eax
movl %eax, (%rax)
movq -24(%rbp), %rdi
movl $1, %esi
call access_var
movb -16(%rbp), %al
movb %al, (%rax)
leaq foo(%rip), %rdi
movq -24(%rbp), %rsi
call allocate_closure
movq %rax, %rdi
call incr_closure
movq %rax, %rbx
movq %rbx, %rdi
call incr_closure
movq %rbx, %rdi
call decr_closure
movq %rax, %rdi
call decr_closure
movq %rbx, %rax
movq -32(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

get_val:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
movq %rbx, -16(%rbp)
movq %rsi, -8(%rbp)
movq -8(%rbp), %rdi
movq $0, %rsi
call struct_equals
testb %al, %al
jnz .L_F5_1_1_B1_case0_0
jmp .L_F5_1_1_B1_case0_1
.L_F5_1_1_B1_case0_0:
movq -8(%rbp), %rdi
call decr_struct
movl $0, %eax
movq -16(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret
.L_F5_1_1_B1_case0_1:
movq -8(%rbp), %rdi
movl $2, %esi
call access_field
movl (%rax), %ebx
movq -8(%rbp), %rdi
call decr_struct
movl %ebx, %eax
movq -16(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

div_check:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
movq %rbx, -8(%rbp)
movl %edx, %ebx
movl %esi, %eax
cdq
idivl %ebx
movl %ebx, %eax
cdq
idivl %esi
movq -8(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

atoi:
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
movq %rbx, -40(%rbp)
movq %rsi, -8(%rbp)
movl %edx, -16(%rbp)
movq -8(%rbp), %rdi
movq $0, %rsi
call list_equals
movq %rax, %rbx
testb %bl, %bl
jnz .L_F7_1_1_B1_case0_0
movq -8(%rbp), %rdi
call list_size
cmpl $1, %eax
jge .L_F7_1_1_B1_case0_1
.L_F7_1_1_B1_case0_0:
movq -8(%rbp), %rdi
call decr_list
movl -16(%rbp), %eax
movq -40(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret
.L_F7_1_1_B1_case0_1:
movq -8(%rbp), %rdi
movl $0, %esi
call index_list
movb (%rax), %al
movb %al, -24(%rbp)
movq -8(%rbp), %rdi
movl $1, %esi
call access_node
movq %rax, %rdi
call incr_list
movb -24(%rbp), %bl
cmpb $45, %bl
je .L_F7_1_1_B3_case1_0
jmp .L_F7_1_1_B3_case1_1
.L_F7_1_1_B3_case1_0:
leaq atoi.local(%rip), %rbx
movq %rbx, -32(%rbp)
movq -32(%rbp), %rdi
call get_env
movq %rax, %rdi
movq %rax, %rsi
movl -16(%rbp), %edx
movl -32(%rbp), %ebx
call *%rbx
movl %eax, %ebx
movl $0, %ebx
subl %ebx, %ebx
movq -8(%rbp), %rdi
call decr_list
movq %rax, %rdi
call decr_list
movl %ebx, %eax
movq -40(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret
.L_F7_1_1_B3_case1_1:
leaq atoi.local(%rip), %rbx
movq %rbx, -32(%rbp)
movq -32(%rbp), %rdi
call get_env
movq %rax, %rdi
movq %rax, %rsi
movb -24(%rbp), %bl
movb %bl, %cl
subb $48, %cl
movl -16(%rbp), %ebx
movl $10, %ebx
imull %ebx, %ebx
movsbl %cl, %ecx
movl %ecx, %edx
addl %ebx, %edx
movl -32(%rbp), %ebx
call *%rbx
movl %eax, %ebx
movq -8(%rbp), %rdi
call decr_list
movq %rax, %rdi
call decr_list
movl %ebx, %eax
movq -40(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

main:
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
movq %rbx, -48(%rbp)
call read_string
leaq atoi.local(%rip), %rbx
movq %rbx, -8(%rbp)
movq -8(%rbp), %rdi
call get_env
movq %rax, %rdi
movq %rax, %rsi
movl $0, %edx
movl -8(%rbp), %ebx
call *%rbx
leaq get_val.local(%rip), %rbx
movq %rbx, -16(%rbp)
movq -16(%rbp), %rdi
call get_env
movq %rax, %rdi
movq $0, %rsi
movl -16(%rbp), %ebx
call *%rbx
leaq factorial.local(%rip), %rbx
movq %rbx, -24(%rbp)
movq -24(%rbp), %rdi
call get_env
movq %rax, %rdi
movl %eax, %esi
movl -24(%rbp), %ebx
call *%rbx
call print_int
leaq nest_check.local(%rip), %rbx
movq %rbx, -32(%rbp)
movq -32(%rbp), %rdi
call get_env
movq %rax, %rdi
movl $1, %esi
movb $97, %dl
movq -32(%rbp), %rbx
call *%rbx
movq %rax, %rbx
movq %rbx, -40(%rbp)
movq -40(%rbp), %rdi
call get_env
movq %rax, %rdi
movl $2, %esi
movl -40(%rbp), %ebx
call *%rbx
movl %eax, %ebx
movq %rax, %rdi
call decr_list
movl %ebx, %eax
movq -48(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

