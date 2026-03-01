.att_syntax prefix
.global main

.extern _print_int
.extern _read_string
.extern _access_node
.extern _list_size
.extern _decr_struct
.extern _index_list
.extern _list_equals
.extern _struct_equals
.extern _decr_closure
.extern _incr_closure
.extern _allocate_closure
.extern _access_var
.extern _access_field
.extern _get_env
.extern _decr_list
.extern _allocate_env
.extern _incr_list
.extern _concat_list

.section __DATA,__data
.align 8
main.local:
	.quad 0
	.quad _main
	.long 1
list_check.local:
	.quad 0
	.quad _list_check
	.long 1
div_check.local:
	.quad 0
	.quad _div_check
	.long 1
nest_check.local:
	.quad 0
	.quad _nest_check
	.long 1
atoi.local:
	.quad 0
	.quad _atoi
	.long 1
factorial.local:
	.quad 0
	.quad _factorial
	.long 1
get_val.local:
	.quad 0
	.quad _get_val
	.long 1

.section __TEXT,__const
.align 8

.section 
_list_check:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
movq %rbx, -24(%rbp)
movq %rsi, -8(%rbp)
movq %rdx, -16(%rbp)
movq $0, %rdi
movq -8(%rbp), %rsi
call _concat_list
movq %rax, %rbx
movq -8(%rbp), %rdi
call _incr_list
movq %rbx, %rdi
movq -16(%rbp), %rsi
call _concat_list
movq %rax, %rbx
movq -16(%rbp), %rdi
call _incr_list
movq -8(%rbp), %rdi
call _decr_list
movq -16(%rbp), %rdi
call _decr_list
movq %rbx, %rdi
call _decr_list
movl $0, %eax
movq -24(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

_factorial:
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
call _get_env
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

_foo:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
movq %rbx, -24(%rbp)
movq %rdi, -8(%rbp)
movl %esi, -16(%rbp)
movq -8(%rbp), %rdi
movl $0, %esi
call _access_var
movl (%rax), %eax
cmpb $1, %al
je .L_F4_1_1_1_B1_case0_0
jmp .L_F4_1_1_1_B1_case0_1
.L_F4_1_1_1_B1_case0_0:
movq -8(%rbp), %rdi
movl $1, %esi
call _access_var
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

_nest_check:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
movq %rbx, -32(%rbp)
movl %esi, -8(%rbp)
movb %dl, -16(%rbp)
movl $0, %edi
call _allocate_env
movq %rax, -24(%rbp)
movq -24(%rbp), %rdi
movl $0, %esi
call _access_var
movl -8(%rbp), %eax
movl %eax, (%rax)
movq -24(%rbp), %rdi
movl $1, %esi
call _access_var
movb -16(%rbp), %al
movb %al, (%rax)
leaq _foo(%rip), %rdi
movq -24(%rbp), %rsi
call _allocate_closure
movq %rax, %rdi
call _incr_closure
movq %rax, %rbx
movq %rbx, %rdi
call _incr_closure
movq %rbx, %rdi
call _decr_closure
movq %rax, %rdi
call _decr_closure
movq %rbx, %rax
movq -32(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

_get_val:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
movq %rbx, -16(%rbp)
movq %rsi, -8(%rbp)
movq -8(%rbp), %rdi
movq $0, %rsi
call _struct_equals
testb %al, %al
jnz .L_F5_1_1_B1_case0_0
jmp .L_F5_1_1_B1_case0_1
.L_F5_1_1_B1_case0_0:
movq -8(%rbp), %rdi
call _decr_struct
movl $0, %eax
movq -16(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret
.L_F5_1_1_B1_case0_1:
movq -8(%rbp), %rdi
movl $2, %esi
call _access_field
movl (%rax), %ebx
movq -8(%rbp), %rdi
call _decr_struct
movl %ebx, %eax
movq -16(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

_div_check:
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

_atoi:
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
movq %rbx, -40(%rbp)
movq %rsi, -8(%rbp)
movl %edx, -16(%rbp)
movq -8(%rbp), %rdi
movq $0, %rsi
call _list_equals
movq %rax, %rbx
testb %bl, %bl
jnz .L_F7_1_1_B1_case0_0
movq -8(%rbp), %rdi
call _list_size
cmpl $1, %eax
jge .L_F7_1_1_B1_case0_1
.L_F7_1_1_B1_case0_0:
movq -8(%rbp), %rdi
call _decr_list
movl -16(%rbp), %eax
movq -40(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret
.L_F7_1_1_B1_case0_1:
movq -8(%rbp), %rdi
movl $0, %esi
call _index_list
movb (%rax), %al
movb %al, -24(%rbp)
movq -8(%rbp), %rdi
movl $1, %esi
call _access_node
movq %rax, %rdi
call _incr_list
movb -24(%rbp), %bl
cmpb $45, %bl
je .L_F7_1_1_B3_case1_0
jmp .L_F7_1_1_B3_case1_1
.L_F7_1_1_B3_case1_0:
leaq atoi.local(%rip), %rbx
movq %rbx, -32(%rbp)
movq -32(%rbp), %rdi
call _get_env
movq %rax, %rdi
movq %rax, %rsi
movl -16(%rbp), %edx
movl -32(%rbp), %ebx
call *%rbx
movl %eax, %ebx
movl $0, %ebx
subl %ebx, %ebx
movq -8(%rbp), %rdi
call _decr_list
movq %rax, %rdi
call _decr_list
movl %ebx, %eax
movq -40(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret
.L_F7_1_1_B3_case1_1:
leaq atoi.local(%rip), %rbx
movq %rbx, -32(%rbp)
movq -32(%rbp), %rdi
call _get_env
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
call _decr_list
movq %rax, %rdi
call _decr_list
movl %ebx, %eax
movq -40(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

_main:
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
movq %rbx, -48(%rbp)
call _read_string
leaq atoi.local(%rip), %rbx
movq %rbx, -8(%rbp)
movq -8(%rbp), %rdi
call _get_env
movq %rax, %rdi
movq %rax, %rsi
movl $0, %edx
movl -8(%rbp), %ebx
call *%rbx
leaq get_val.local(%rip), %rbx
movq %rbx, -16(%rbp)
movq -16(%rbp), %rdi
call _get_env
movq %rax, %rdi
movq $0, %rsi
movl -16(%rbp), %ebx
call *%rbx
leaq factorial.local(%rip), %rbx
movq %rbx, -24(%rbp)
movq -24(%rbp), %rdi
call _get_env
movq %rax, %rdi
movl %eax, %esi
movl -24(%rbp), %ebx
call *%rbx
call _print_int
leaq nest_check.local(%rip), %rbx
movq %rbx, -32(%rbp)
movq -32(%rbp), %rdi
call _get_env
movq %rax, %rdi
movl $1, %esi
movb $97, %dl
movq -32(%rbp), %rbx
call *%rbx
movq %rax, %rbx
movq %rbx, -40(%rbp)
movq -40(%rbp), %rdi
call _get_env
movq %rax, %rdi
movl $2, %esi
movl -40(%rbp), %ebx
call *%rbx
movl %eax, %ebx
movq %rax, %rdi
call _decr_list
movl %ebx, %eax
movq -48(%rbp), %rbx
movq %rbp, %rsp
popq %rbp
ret

