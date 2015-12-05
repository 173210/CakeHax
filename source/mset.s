# 1 "source/mset.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "source/mset.S"
# 1 "source/launcher_path.h" 1
# 2 "source/mset.S" 2

 .arm
 .section .text.mset, "ax"
mset:
 mov r0, sp
 sub sp, #20
 adr r1, path
 mov r2, #0x14000000
 mov r3, #0x400000
 b _start

path:
 .string16 "YS:/" "/Cakes.dat"
