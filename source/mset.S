#include "launcher_path.h"

	.arm
	.section .text.mset, "ax"
	.global	mset
	.type	mset, %function
mset:
	mov	r0, sp
	sub	sp, #20
	adr	r1, path
	mov	r2, #0x14000000
	mov	r3, #0x400000
	b	_start

path:
	.string16 "YS:/" LAUNCHER_PATH

	.size	mset, . - mset
