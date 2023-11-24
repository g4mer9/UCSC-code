
#Note that this file only contains a function xyCoordinatesToAddress
#As such, this function should work independent of any caller funmction which calls it
#When using regisetrs, you HAVE to make sure they follow the register usage convention in RISC-V as discussed in lectures.
#Else, your function can potentially fail when used by the autograder and in such a context, you will receive a 0 score for this part

xyCoordinatesToAddress:
	#(x,y) in (a0,a1) arguments
	#a2 argument contains base address
	#returns pixel address in a0
	
	#make sure to return to calling function after putting correct value in a0!
	#Enter code below!DO NOT MODIFY ANYTHING BEFORE THIS COMMENT LINE!
	li t0, 1
	LoopY:	
		blt a1, t0, LoopX
		addi a2, a2, 0x80
		addi a1, a1, -1
		bge a1, t0, LoopY
	LoopX:
		blt a0, t0, Return
		addi a2, a2, 0x4
		addi a0, a0, -1
		bge a0, t0, LoopX
	Return:
		li a0, 0
		addi a0, a2, 0
		ret
		
					
