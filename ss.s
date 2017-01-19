.data
fib.x:	.word	0
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
l7:	j			l18	
l8:	lw	$t2		fib.x+0	
	sub	$t3	$t2	1	
	lw	$a0		fib.x+0	
	sw	$a0		0($sp)	
	add	$sp	$sp	-4	
	sw	$t3		fib.x	
	jal			fib	
	move	$t4	$v0		
	add	$sp	$sp	4	
	lw	$a0		0($sp)	
	sw	$a0		fib.x+0	
l12:	lw	$t5		fib.x+0	
	sub	$t6	$t5	2	
	lw	$a0		fib.x+0	
	sw	$a0		0($sp)	
	add	$sp	$sp	-4	
	sw	$t6		fib.x	
	jal			fib	
	move	$t7	$v0		
	add	$sp	$sp	4	
	lw	$a0		0($sp)	
	sw	$a0		fib.x+0	
l16:	add	$t8	$t4	$t7	
	move	$v0	$t8		
	add	$sp	$sp	4	
	lw	$ra		0($sp)	
	jr	$ra			
main:	sw	$ra		0($sp)	
	add	$sp	$sp	-4	
	li	$v0	5		
	syscall				
l19:	move	$t9	$v0		
	sw	$t9		main.x($t0)	
	lw	$t0		main.x+0	
	lw	$a0		main.x+0	
	sw	$a0		0($sp)	
	add	$sp	$sp	-4	
	sw	$t0		fib.x	
	jal			fib	
	move	$t1	$v0		
	add	$sp	$sp	4	
	lw	$a0		0($sp)	
	sw	$a0		main.x+0	
l24:	move	$a0	$t1		
	li	$v0	1		
	syscall				
	li	$t2		0	
	li	$v0	10		
	syscall				
