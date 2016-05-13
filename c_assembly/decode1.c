/*
 * Remember clang is using LLVM as front end, it generated different
 * assembler code as what we get from GCC
 * Page 225: Practice 3.5 
 */
void decode1 (long *xp, long *yp, long *zp)
{
    long a = *xp;
    long b = *yp;
    long c = *zp;
    *yp = a;
    *zp = b;
    *xp = c;
}

/*
 * We get below assembly code by using clang in Mac OSX El Captain
 * gcc -S decode1.c
 *
 * -------------------------------------------------------------------------------
	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_decode1
	.align	4, 0x90
_decode1:                               ## @decode1
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
	movq	%rdi, -8(%rbp)          # move xp to local varialble %1
	movq	%rsi, -16(%rbp)         # move yp to local varialble %2
	movq	%rdx, -24(%rbp)         # move zp to local varialble %3
	movq	-8(%rbp), %rdx          # move xp to rdx
	movq	(%rdx), %rdx            # move *xp to rdx 
	movq	%rdx, -32(%rbp)         # move *xp to local varialble %4
	movq	-16(%rbp), %rdx         # move yp to rdx
	movq	(%rdx), %rdx            # move *yp to rdx
	movq	%rdx, -40(%rbp)         # move *yp to local varialble %5
	movq	-24(%rbp), %rdx         # move zp to rdx
	movq	(%rdx), %rdx            # move *zp to rdx
	movq	%rdx, -48(%rbp)         # move *zp to local varialble %6
	movq	-32(%rbp), %rdx         # move %4(*x) to rdx
	movq	-16(%rbp), %rsi         # move %2(y) to rsi
	movq	%rdx, (%rsi)            # *y = *x
	movq	-40(%rbp), %rdx         # move %5(*y) to rdx
	movq	-24(%rbp), %rsi         # move %3(z) to rsi
	movq	%rdx, (%rsi)            # *z = *x
	movq	-48(%rbp), %rdx         # move %6(*z) to rdx
	movq	-8(%rbp), %rsi          # move %1(x) to rsi
	movq	%rdx, (%rsi)            # *x = *z
	popq	%rbp                    # restore stack base address
	retq
	.cfi_endproc


.subsections_via_symbols
*/
