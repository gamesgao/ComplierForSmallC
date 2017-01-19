.data
fib.x:	.word	0
fib.__:	.word	0
main.__:	.word	0
main.x:	.word	0
.text
fib:	sw	$ra		0($sp)	
	add	$sp	$sp	-4	
l2:	lw	$t0		fib.x+0	
	ble	$t0	2	l5	
l4:	j			l8	
l5:	li	$t1		1	
	move	$v0	$t1		
	add	$sp	$sp	4	
	lw	$ra		0($sp)	
	jr	$ra			
l7:	j			l22	
l8:	lw	$t2		fib.x+0	
	sub	$t3	$t2	1	
	lw	$a0		fib.__+0	
	sw	$a0		0($sp)	
	add	$sp	$sp	-4	
	lw	$a0		fib.x+0	
	sw	$a0		0($sp)	
	add	$sp	$sp	-4	
	sw	$t3		fib.x	
	jal			fib	
	move	$t4	$v0		
	add	$sp	$sp	4	
	lw	$a0		0($sp)	
	sw	$a0		fib.x+0	
	add	$sp	$sp	4	
	lw	$a0		0($sp)	
	sw	$a0		fib.__+0	
l12:	sw	$t4		fib.__+0	
	lw	$t5		fib.x+0	
	sub	$t6	$t5	2	
	lw	$a0		fib.__+0	
	sw	$a0		0($sp)	
	add	$sp	$sp	-4	
	lw	$a0		fib.x+0	
	sw	$a0		0($sp)	
	add	$sp	$sp	-4	
	sw	$t6		fib.x	
	jal			fib	
	move	$t7	$v0		
	add	$sp	$sp	4	
	lw	$a0		0($sp)	
	sw	$a0		fib.x+0	
	add	$sp	$sp	4	
	lw	$a0		0($sp)	
	sw	$a0		fib.__+0	
l17:	sw	$t7		fib.__+0	
	lw	$t8		fib.__+0	
	lw	$t9		fib.__+0	
	add	$t0	$t8	$t9	
	move	$v0	$t0		
	add	$sp	$sp	4	
	lw	$ra		0($sp)	
	jr	$ra			
main:	sw	$ra		0($sp)	
	add	$sp	$sp	-4	
	li	$v0	5		
	syscall				
l23:	move	$t1	$v0		
	sw	$t1		main.x+0	
	lw	$t2		main.x+0	
	lw	$a0		main.x+0	
	sw	$a0		0($sp)	
	add	$sp	$sp	-4	
	lw	$a0		main.__+0	
	sw	$a0		0($sp)	
	add	$sp	$sp	-4	
	sw	$t2		fib.x	
	jal			fib	
	move	$t3	$v0		
	add	$sp	$sp	4	
	lw	$a0		0($sp)	
	sw	$a0		main.__+0	
	add	$sp	$sp	4	
	lw	$a0		0($sp)	
	sw	$a0		main.x+0	
l28:	sw	$t3		main.__+0	
	lw	$t4		main.__+0	
	move	$a0	$t4		
	li	$v0	1		
	syscall				
	li	$t5		0	
	li	$v0	10		
	syscall				
