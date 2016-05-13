/*
 * Remember clang is using LLVM as front end, it generated different
 * assembler code as what we get from GCC
 */ 
long exchange(long *xp, long y)
{
    long x = *xp;
    *xp = y;
    return x;
}

/*
 * We get below assembly code by using clang in Mac OSX El Captain
 * gcc -S exchange.c
 *
 * -------------------------------------------------------------------------------
	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_exchange
	.align	4, 0x90
_exchange:                              ## @exchange
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)         # Read first parameter to %1
	movq	%rsi, -16(%rbp)        # Read second parameter to %2
	movq	-8(%rbp), %rsi         # Read first parameter xp to rsi
	movq	(%rsi), %rsi           # Read *xp to rsi
	movq	%rsi, -24(%rbp)        # put *xp to %3, actually it's return value
	movq	-16(%rbp), %rsi        # read second value y to rsi
	movq	-8(%rbp), %rdi         # read first value xp back to rdi
	movq	%rsi, (%rdi)           # move value y to *x
	movq	-24(%rbp), %rax        # move %3 to rax as return value 
	popq	%rbp                   # Restore stack base address
	retq
	.cfi_endproc


.subsections_via_symbols
*/
