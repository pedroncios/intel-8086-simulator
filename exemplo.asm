one EQU 1

jmp start

soma proc
	mov AL, 2
	add AL, 5
	ret
soma endp

x DB 1
y DW 3

start:

call soma

mov AL, one
mov AH, 2

add AL, x
add x, AL
add AL, AH
add x, 1
add AL, 2

sub AL, x
sub x, AL
sub AL, AH
sub x, 1
sub AL, 2

mov AL, 2
mov x, 5
mov BL, 5
mul x
mul BL

mov AL, 10
mov BL, 2
div BL

mov AL, 01100001b
and AL, 11011111b 

mov AL, 01000001b
or AL, 00100000b

mov AL, 00000111b
xor AL, 00000010b

not x
not AL

mov AL, 1
mov AH, 1
cmp AL, AH 
je igual  
jmp fim

igual:
mov AH, 2  
cmp AL, AH     
jne diferente 
jmp fim

diferente:
mov AH, 1
cmp AL, AH 	
jge maiorigual 
jmp fim

maiorigual:
mov AL, 2
cmp AL, AH 	 
jge maiorigual2 
jmp fim

maiorigual2:
cmp AH, AL	 
jle menorigual  
jmp fim

menorigual:
mov AL, one
cmp AH, AL 	 
jle menorigual2  
jmp fim

menorigual2:
mov AH, 2
cmp AL, AH 
jl menor  
jmp fim

menor:
cmp AH, AL 
jg zera   
jmp fim

zera:
mov AH, 0
mov AL, 0

fim:
hlt