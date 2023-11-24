##########################################################################
# Created by: Riley Fink
#	      CruzID: 1895647
#             16 May 2022
#
# Assignment: Lab 3
#	      CMPE 012, Computer Systems and Assembly Language
#	      UC Santa Cruz, Winter 2022
#
# Description: takes an int input above 0 and prints the following for the amount of lines specified in input:
#$1
#$*$3
#$*$*$5
#$*$*$*$7
#
# Notes: This program is intended to be run from the RARS IDE.
##########################################################################

.macro print_str(%string1)
	li a7,4 
	la a0, %string1
	ecall
	.end_macro
	
.macro print_int (%x)
	li a7, 1
	add a0, zero, %x
	ecall
	.end_macro

.data
	prompt: .asciz  "Enter the height of the pattern (must be greater than 0): "
	error: .asciz "Invalid Entry!"
	newline: .asciz "\n"
	dollar: .asciz "$"
	dollarA: .asciz "$*"
	
	
.text

.main
	#set 1 var
	li t1, 1
	Loop:
		#print prompt
		li a7,4
		la a0, prompt
		ecall
	
		#store input
		li a7, 5
		ecall
	
		#copy input
		li t2, 0
		addi t0, a0, 0
		addi a1, a0, 0
	
		#conditionals
		blt a1, t1, err
		bge a1, t1, cont
	err:
		print_str(error)
		print_str(newline)
		blt a1, t1, Loop
	
	cont:
		li a7,4
		#print line
		li a2, 0
		addi a2, t2, 0
		bge a2, t1, Loop2
		blt a2, t1, cont2
	Loop2:
		print_str(dollarA)
		addi a2, a2, -1
		bge a2, t1, Loop2
	cont2:
		print_str(dollar)
		li a4, 2
		mul a3, t2, a4
		addi a3, a3, 1
		print_int(a3)
		print_str(newline)
		addi t0, t0, -1
		addi t2, t2, 1
		bne t0, zero, cont 
		
