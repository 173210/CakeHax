	.arm
	.section .text.mset, "ax"
	ldr	r0, =app
	str	sp, [r0]
	sub	sp, #20
