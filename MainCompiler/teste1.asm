extern printf
extern scanf
section .data
fmt_d: db "%ld", 0
fmt_f: db "%f", 0
fmt_s: db "%s", 0
fmt_dln: db "%ld", 10, 0
fmt_fln: db "%f", 10, 0
fmt_sln: db "%s", 10, 0

var_x: dq 0
var_y: dq 0
total: dq 0
media: dq 0
impar: dq 0

section .text
global main

main:
#Funcao write
mov rdi,fmt_f
mov rsi,var_x
mov rax,0
call scanf
#Funcao write
mov rdi,fmt_d
mov rsi,var_y
mov rax,0
call scanf
#Codigo atribuicao
mov rbx,[var_x]
push rbx
#Codigo soma
mov rbx,[var_y]
push rbx
pop rcx
pop rbx
add rbx,rcx
push rbx
pop rbx
mov [total],rbx
#Codigo atribuicao
mov rbx,[total]
push rbx
#Codigo divisao
mov rbx,2
push rbx
pop r8
pop rax
xor rdx,rdx
idiv r8
push rax
pop rbx
mov [media],rbx
#Funcao print
mov rdi,fmt_d
mov rsi,[media]
mov rax,0
call printf
#Codigo atribuicao
mov rbx,0
push rbx
pop rbx
mov [impar],rbx
label2:
mov rbx,0
push rbx
pop rcx
mov rbx, [total]
cmp rbx, rcx
jng label3
mov rbx,0
push rbx
pop rcx
mov rbx, [impar]
cmp rbx, rcx
jne label0
#Codigo atribuicao
mov rbx,1
push rbx
pop rbx
mov [impar],rbx
jmp label1
label0:
#Codigo atribuicao
mov rbx,0
push rbx
pop rbx
mov [impar],rbx
label1:
#Codigo atribuicao
mov rbx,[total]
push rbx
#Codigo subtracao
mov rbx,1
push rbx
pop rcx
pop rbx
sub rbx,rcx
push rbx
pop rbx
mov [total],rbx
jmp label2
label3:
#Funcao print
mov rdi,fmt_d
mov rsi,[impar]
mov rax,0
call printf
mov rax,0
ret
