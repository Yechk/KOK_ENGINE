	.file	"matrix.cpp"
	.text
	.p2align 4,,15
	.globl	_Z3MutN3glm3matILi4ELi4EfLNS_9qualifierE0EEES2_
	.type	_Z3MutN3glm3matILi4ELi4EfLNS_9qualifierE0EEES2_, @function
_Z3MutN3glm3matILi4ELi4EfLNS_9qualifierE0EEES2_:
.LFB6934:
	.cfi_startproc
	pushq	%r10
	.cfi_def_cfa_offset 16
	.cfi_offset 10, -16
	movq	%rdi, %rax
	leaq	16(%rsp), %r10
	vmovups	(%r10), %xmm0
	vinsertf128	$0x1, 16(%r10), %ymm0, %ymm0
	vmovups	32(%r10), %xmm1
	vinsertf128	$0x1, 48(%r10), %ymm1, %ymm1
	vmovups	96(%r10), %xmm3
	vperm2f128	$0, %ymm0, %ymm0, %ymm4
	vperm2f128	$17, %ymm0, %ymm0, %ymm2
	vmovups	64(%r10), %xmm0
	vinsertf128	$0x1, 112(%r10), %ymm3, %ymm3
	vinsertf128	$0x1, 80(%r10), %ymm0, %ymm0
	vperm2f128	$0, %ymm1, %ymm1, %ymm7
	vperm2f128	$17, %ymm1, %ymm1, %ymm1
	vpermilps	$0, %ymm0, %ymm6
	vpermilps	$85, %ymm0, %ymm5
	vmulps	%ymm4, %ymm6, %ymm6
	vfmadd231ps	%ymm5, %ymm2, %ymm6
	vpermilps	$255, %ymm0, %ymm5
	vpermilps	$170, %ymm0, %ymm0
	vfmadd132ps	%ymm1, %ymm6, %ymm5
	vfmadd132ps	%ymm7, %ymm5, %ymm0
	vmovups	%xmm0, (%rdi)
	vextractf128	$0x1, %ymm0, 16(%rdi)
	vpermilps	$170, %ymm3, %ymm0
	vpermilps	$255, %ymm3, %ymm5
	vmulps	%ymm7, %ymm0, %ymm0
	vfmadd132ps	%ymm5, %ymm0, %ymm1
	vpermilps	$0, %ymm3, %ymm0
	vfmadd231ps	%ymm0, %ymm4, %ymm1
	vpermilps	$85, %ymm3, %ymm0
	vfmadd132ps	%ymm2, %ymm1, %ymm0
	vmovups	%xmm0, 32(%rdi)
	vextractf128	$0x1, %ymm0, 48(%rdi)
	vzeroupper
	popq	%r10
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE6934:
	.size	_Z3MutN3glm3matILi4ELi4EfLNS_9qualifierE0EEES2_, .-_Z3MutN3glm3matILi4ELi4EfLNS_9qualifierE0EEES2_
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
