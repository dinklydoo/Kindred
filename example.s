.att_syntax prefix
.global _main

.extern _print_string
.extern _decr_list
.extern _index_list
.extern _alloc_list
.extern _init_struct_layout
.extern _init_env_layout

.section __DATA,__data
.align 8
main.local:
	.quad 0
	.quad _main
	.long 1
	.long 0

.section __TEXT,__const
.align 8

.section __TEXT,__text
_main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
call _init_env_layout
call _init_struct_layout
movl $0, %edi
movq $1, %rsi
movl $11, %edx
call _alloc_list
movq %rax, -8(%rbp)
movq -8(%rbp), %rdi
movl $0, %esi
call _index_list
movb $72, (%rax)
movq -8(%rbp), %rdi
movl $1, %esi
call _index_list
movb $101, (%rax)
movq -8(%rbp), %rdi
movl $2, %esi
call _index_list
movb $108, (%rax)
movq -8(%rbp), %rdi
movl $3, %esi
call _index_list
movb $108, (%rax)
movq -8(%rbp), %rdi
movl $4, %esi
call _index_list
movb $111, (%rax)
movq -8(%rbp), %rdi
movl $5, %esi
call _index_list
movb $32, (%rax)
movq -8(%rbp), %rdi
movl $6, %esi
call _index_list
movb $87, (%rax)
movq -8(%rbp), %rdi
movl $7, %esi
call _index_list
movb $111, (%rax)
movq -8(%rbp), %rdi
movl $8, %esi
call _index_list
movb $114, (%rax)
movq -8(%rbp), %rdi
movl $9, %esi
call _index_list
movb $108, (%rax)
movq -8(%rbp), %rdi
movl $10, %esi
call _index_list
movb $100, (%rax)
movq -8(%rbp), %rdi
call _print_string
movq -8(%rbp), %rdi
call _decr_list
movl $0, %eax
movq %rbp, %rsp
popq %rbp
ret

