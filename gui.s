	.file	"gui.cpp"
	.text
	.section	.text._ZNKSt5ctypeIcE8do_widenEc,"axG",@progbits,_ZNKSt5ctypeIcE8do_widenEc,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZNKSt5ctypeIcE8do_widenEc
	.type	_ZNKSt5ctypeIcE8do_widenEc, @function
_ZNKSt5ctypeIcE8do_widenEc:
.LFB9309:
	.cfi_startproc
	movl	%esi, %eax
	ret
	.cfi_endproc
.LFE9309:
	.size	_ZNKSt5ctypeIcE8do_widenEc, .-_ZNKSt5ctypeIcE8do_widenEc
	.section	.text._ZN5MyGUI6UpdateEd,"axG",@progbits,_ZN5MyGUI6UpdateEd,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN5MyGUI6UpdateEd
	.type	_ZN5MyGUI6UpdateEd, @function
_ZN5MyGUI6UpdateEd:
.LFB16952:
	.cfi_startproc
	rep ret
	.cfi_endproc
.LFE16952:
	.size	_ZN5MyGUI6UpdateEd, .-_ZN5MyGUI6UpdateEd
	.section	.text._ZN5MyGUI4DrawEv,"axG",@progbits,_ZN5MyGUI4DrawEv,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN5MyGUI4DrawEv
	.type	_ZN5MyGUI4DrawEv, @function
_ZN5MyGUI4DrawEv:
.LFB16953:
	.cfi_startproc
	rep ret
	.cfi_endproc
.LFE16953:
	.size	_ZN5MyGUI4DrawEv, .-_ZN5MyGUI4DrawEv
	.text
	.align 2
	.p2align 4,,15
	.type	_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EE17_M_initialize_mapEm.constprop.73, @function
_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EE17_M_initialize_mapEm.constprop.73:
.LFB22167:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA22167
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	$8, 8(%rdi)
	movl	$64, %edi
.LEHB0:
	call	_Znwm@PLT
.LEHE0:
	movq	8(%rbx), %rcx
	movq	%rax, (%rbx)
	movl	$512, %edi
	leaq	-1(%rcx), %rdx
	shrq	%rdx
	leaq	(%rax,%rdx,8), %rbp
.LEHB1:
	call	_Znwm@PLT
.LEHE1:
	leaq	512(%rax), %rdx
	movq	%rax, 0(%rbp)
	movq	%rbp, 40(%rbx)
	movq	%rax, 24(%rbx)
	movq	%rbp, 72(%rbx)
	movq	%rdx, 32(%rbx)
	movq	%rax, 56(%rbx)
	movq	%rdx, 64(%rbx)
	movq	%rax, 16(%rbx)
	movq	%rax, 48(%rbx)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L10:
	.cfi_restore_state
	movq	%rax, %rdi
	vzeroupper
	call	__cxa_begin_catch@PLT
.LEHB2:
	call	__cxa_rethrow@PLT
.LEHE2:
.L11:
	movq	%rax, %rbp
	vzeroupper
	call	__cxa_end_catch@PLT
	movq	%rbp, %rdi
	call	__cxa_begin_catch@PLT
	movq	(%rbx), %rdi
	call	_ZdlPv@PLT
	movq	$0, (%rbx)
	movq	$0, 8(%rbx)
.LEHB3:
	call	__cxa_rethrow@PLT
.LEHE3:
.L9:
	movq	%rax, %rbx
	vzeroupper
	call	__cxa_end_catch@PLT
	movq	%rbx, %rdi
.LEHB4:
	call	_Unwind_Resume@PLT
.LEHE4:
	.cfi_endproc
.LFE22167:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
	.align 4
.LLSDA22167:
	.byte	0xff
	.byte	0x9b
	.uleb128 .LLSDATT22167-.LLSDATTD22167
.LLSDATTD22167:
	.byte	0x1
	.uleb128 .LLSDACSE22167-.LLSDACSB22167
.LLSDACSB22167:
	.uleb128 .LEHB0-.LFB22167
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB22167
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L10-.LFB22167
	.uleb128 0x1
	.uleb128 .LEHB2-.LFB22167
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L11-.LFB22167
	.uleb128 0x3
	.uleb128 .LEHB3-.LFB22167
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L9-.LFB22167
	.uleb128 0
	.uleb128 .LEHB4-.LFB22167
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
.LLSDACSE22167:
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x7d
	.align 4
	.long	0

.LLSDATT22167:
	.text
	.size	_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EE17_M_initialize_mapEm.constprop.73, .-_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EE17_M_initialize_mapEm.constprop.73
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"basic_string::_M_construct null not valid"
	.text
	.align 2
	.p2align 4,,15
	.type	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.constprop.75, @function
_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.constprop.75:
.LFB22165:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	leaq	16(%rdi), %r13
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	testq	%rsi, %rsi
	movq	%r13, (%rdi)
	je	.L16
	movq	%rdi, %rbx
	movq	%rsi, %rdi
	movq	%rsi, %r12
	call	strlen@PLT
	cmpq	$15, %rax
	movq	%rax, %rbp
	ja	.L27
	cmpq	$1, %rax
	je	.L28
	testq	%rax, %rax
	jne	.L19
.L21:
	movq	(%rbx), %rax
	movq	%rbp, 8(%rbx)
	movb	$0, (%rax,%rbp)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L28:
	.cfi_restore_state
	movzbl	(%r12), %eax
	movb	%al, 16(%rbx)
	jmp	.L21
.L27:
	leaq	1(%rax), %rdi
	call	_Znwm@PLT
	movq	%rbp, 16(%rbx)
	movq	%rax, %r13
	movq	%rax, (%rbx)
.L19:
	movq	%rbp, %rdx
	movq	%r12, %rsi
	movq	%r13, %rdi
	call	memcpy@PLT
	jmp	.L21
.L16:
	leaq	.LC0(%rip), %rdi
	call	_ZSt19__throw_logic_errorPKc@PLT
	.cfi_endproc
.LFE22165:
	.size	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.constprop.75, .-_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.constprop.75
	.section	.rodata._ZN5MyGUI14DeliverMessageEy11MessageDataP9KOK_Actor.str1.1,"aMS",@progbits,1
.LC1:
	.string	"SUBJECT: "
.LC2:
	.string	"slider value: "
	.section	.text._ZN5MyGUI14DeliverMessageEy11MessageDataP9KOK_Actor,"axG",@progbits,_ZN5MyGUI14DeliverMessageEy11MessageDataP9KOK_Actor,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN5MyGUI14DeliverMessageEy11MessageDataP9KOK_Actor
	.type	_ZN5MyGUI14DeliverMessageEy11MessageDataP9KOK_Actor, @function
_ZN5MyGUI14DeliverMessageEy11MessageDataP9KOK_Actor:
.LFB16951:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdx, %rbx
	subq	$96, %rsp
	.cfi_def_cfa_offset 128
	movq	%fs:40, %rax
	movq	%rax, 88(%rsp)
	xorl	%eax, %eax
	testq	%rsi, %rsi
	je	.L90
	cmpq	$1, %rsi
	je	.L91
	cmpq	$2, %rsi
	je	.L92
	cmpq	$10, %rsi
	jne	.L29
	leaq	.LC2(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	movl	$14, %edx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	leaq	_ZSt4cout(%rip), %rdi
	movl	%ebx, %esi
	call	_ZNSo9_M_insertImEERSoT_@PLT
.L88:
	movq	%rax, %rbp
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbp,%rax), %rbx
	testq	%rbx, %rbx
	je	.L36
	cmpb	$0, 56(%rbx)
	je	.L50
	movsbl	67(%rbx), %esi
.L51:
	movq	%rbp, %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
.L29:
	movq	88(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L93
	addq	$96, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L91:
	.cfi_restore_state
	leaq	.LC1(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	movl	$9, %edx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	leaq	_ZSt4cout(%rip), %rdi
	movl	$1, %esi
	call	_ZNSo9_M_insertIyEERSoT_@PLT
	movq	%rax, %r12
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r12,%rax), %rbp
	testq	%rbp, %rbp
	je	.L36
	cmpb	$0, 56(%rbp)
	je	.L41
	movsbl	67(%rbp), %esi
.L42:
	movq	%r12, %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	leaq	_ZSt4cout(%rip), %rdi
	movl	%ebx, %esi
	call	_ZNSolsEi@PLT
	jmp	.L88
	.p2align 4,,10
	.p2align 3
.L90:
	vmovdqu	(%rdx), %xmm0
	leaq	.LC1(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	vmovaps	%xmm0, 16(%rsp)
	vmovdqu	16(%rdx), %xmm0
	vmovaps	%xmm0, 32(%rsp)
	vmovdqu	32(%rdx), %xmm0
	vmovaps	%xmm0, 48(%rsp)
	vmovdqu	48(%rdx), %xmm0
	movl	$9, %edx
	vmovaps	%xmm0, 64(%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	leaq	_ZSt4cout(%rip), %rdi
	xorl	%esi, %esi
	call	_ZNSo9_M_insertIyEERSoT_@PLT
	movq	%rax, %rbp
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbp,%rax), %rbx
	testq	%rbx, %rbx
	je	.L36
	cmpb	$0, 56(%rbx)
	je	.L32
	movsbl	67(%rbx), %esi
.L33:
	movq	%rbp, %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	leaq	16(%rsp), %rsi
	movq	%rsi, %rdx
.L34:
	movl	(%rdx), %ecx
	addq	$4, %rdx
	leal	-16843009(%rcx), %eax
	notl	%ecx
	andl	%ecx, %eax
	andl	$-2139062144, %eax
	je	.L34
	movl	%eax, %ecx
	leaq	_ZSt4cout(%rip), %rdi
	shrl	$16, %ecx
	testl	$32896, %eax
	cmove	%ecx, %eax
	leaq	2(%rdx), %rcx
	cmove	%rcx, %rdx
	movl	%eax, %ecx
	addb	%al, %cl
	sbbq	$3, %rdx
	subq	%rsi, %rdx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	_ZSt4cout(%rip), %rax
	leaq	_ZSt4cout(%rip), %rdx
	movq	-24(%rax), %rax
	movq	240(%rdx,%rax), %rbx
	testq	%rbx, %rbx
	je	.L36
	cmpb	$0, 56(%rbx)
	je	.L37
	movsbl	67(%rbx), %esi
.L38:
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L50:
	movq	%rbx, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%rbx), %rax
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L51
	movq	%rbx, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L92:
	leaq	.LC1(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	movl	$9, %edx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	leaq	_ZSt4cout(%rip), %rdi
	movl	$2, %esi
	call	_ZNSo9_M_insertIyEERSoT_@PLT
	movq	%rax, %r12
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r12,%rax), %rbp
	testq	%rbp, %rbp
	je	.L36
	cmpb	$0, 56(%rbp)
	je	.L46
	movsbl	67(%rbp), %esi
.L47:
	movq	%r12, %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	movl	%ebx, 12(%rsp)
	leaq	_ZSt4cout(%rip), %rdi
	vmovd	12(%rsp), %xmm0
	vcvtss2sd	%xmm0, %xmm0, %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	jmp	.L88
	.p2align 4,,10
	.p2align 3
.L46:
	movq	%rbp, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	0(%rbp), %rax
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L47
	movq	%rbp, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L47
	.p2align 4,,10
	.p2align 3
.L41:
	movq	%rbp, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	0(%rbp), %rax
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L42
	movq	%rbp, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L42
	.p2align 4,,10
	.p2align 3
.L32:
	movq	%rbx, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%rbx), %rax
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L33
	movq	%rbx, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L33
	.p2align 4,,10
	.p2align 3
.L37:
	movq	%rbx, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%rbx), %rax
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L38
	movq	%rbx, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L38
.L93:
	call	__stack_chk_fail@PLT
.L36:
	call	_ZSt16__throw_bad_castv@PLT
	.cfi_endproc
.LFE16951:
	.size	_ZN5MyGUI14DeliverMessageEy11MessageDataP9KOK_Actor, .-_ZN5MyGUI14DeliverMessageEy11MessageDataP9KOK_Actor
	.section	.rodata._ZN12KOK_Graphics8SSAODataC2Eii.str1.1,"aMS",@progbits,1
.LC3:
	.string	"./Shaders/pp_ssao.fs"
.LC4:
	.string	"./Shaders/quad.vs"
	.section	.rodata._ZN12KOK_Graphics8SSAODataC2Eii.str1.8,"aMS",@progbits,1
	.align 8
.LC5:
	.string	"ERROR::FRAMEBUFFER:: Framebuffer for SSAO is not complete!"
	.section	.text._ZN12KOK_Graphics8SSAODataC2Eii,"axG",@progbits,_ZN12KOK_Graphics8SSAODataC5Eii,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN12KOK_Graphics8SSAODataC2Eii
	.type	_ZN12KOK_Graphics8SSAODataC2Eii, @function
_ZN12KOK_Graphics8SSAODataC2Eii:
.LFB10419:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA10419
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movl	%esi, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	leaq	.LC3(%rip), %rsi
	movq	%rdi, %rbx
	leaq	.LC4(%rip), %rdi
	movl	%edx, %r13d
	subq	$72, %rsp
	.cfi_def_cfa_offset 112
	leaq	16(%rsp), %rbp
	movb	$0, 15(%rsp)
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
.LEHB5:
	call	_Z11LoadShadersPKcS0_@PLT
	movl	%eax, (%rbx)
	leaq	16(%rbp), %rax
	movl	$21, %edi
	movq	%rax, 16(%rsp)
	call	_Znwm@PLT
.LEHE5:
	vmovdqa	.LC6(%rip), %xmm0
	leaq	15(%rsp), %rdx
	movl	$1735290926, 16(%rax)
	movb	$0, 20(%rax)
	xorl	%esi, %esi
	vmovups	%xmm0, (%rax)
	movq	%rbp, %rdi
	movq	%rax, 16(%rsp)
	movq	$20, 32(%rsp)
	movq	$20, 24(%rsp)
.LEHB6:
	call	_ZN10KOK_Imager7LoadPNGENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEbRb@PLT
.LEHE6:
	movq	16(%rsp), %rdi
	addq	$16, %rbp
	movl	%eax, 12(%rbx)
	cmpq	%rbp, %rdi
	je	.L95
	call	_ZdlPv@PLT
.L95:
	leaq	4(%rbx), %rsi
	movl	$1, %edi
.LEHB7:
	call	*__glewGenFramebuffers(%rip)
	movl	4(%rbx), %esi
	movl	$36160, %edi
	call	*__glewBindFramebuffer(%rip)
	leaq	8(%rbx), %rsi
	movl	$1, %edi
	call	glGenTextures@PLT
	movl	8(%rbx), %esi
	movl	$3553, %edi
	call	glBindTexture@PLT
	subq	$8, %rsp
	.cfi_def_cfa_offset 120
	xorl	%r9d, %r9d
	movl	%r13d, %r8d
	pushq	$0
	.cfi_def_cfa_offset 128
	pushq	$5121
	.cfi_def_cfa_offset 136
	movl	%r12d, %ecx
	pushq	$6403
	.cfi_def_cfa_offset 144
	xorl	%esi, %esi
	movl	$33321, %edx
	movl	$3553, %edi
	call	glTexImage2D@PLT
	addq	$32, %rsp
	.cfi_def_cfa_offset 112
	movl	$9728, %edx
	movl	$10241, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	$9728, %edx
	movl	$10240, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	xorl	%r8d, %r8d
	movl	8(%rbx), %ecx
	movl	$3553, %edx
	movl	$36064, %esi
	movl	$36160, %edi
	call	*__glewFramebufferTexture2D(%rip)
	movl	$36160, %edi
	call	*__glewCheckFramebufferStatus(%rip)
	cmpl	$36053, %eax
	je	.L96
	leaq	.LC5(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	movl	$58, %edx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	_ZSt4cout(%rip), %rax
	leaq	_ZSt4cout(%rip), %rdx
	movq	-24(%rax), %rax
	movq	240(%rdx,%rax), %rbx
	testq	%rbx, %rbx
	je	.L112
	cmpb	$0, 56(%rbx)
	je	.L98
	movsbl	67(%rbx), %esi
.L99:
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
.L96:
	xorl	%esi, %esi
	movl	$36160, %edi
	call	*__glewBindFramebuffer(%rip)
	movq	56(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L113
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L98:
	.cfi_restore_state
	movq	%rbx, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%rbx), %rax
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L99
	movq	%rbx, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L99
.L113:
	call	__stack_chk_fail@PLT
.L112:
	call	_ZSt16__throw_bad_castv@PLT
.L104:
	movq	16(%rsp), %rdi
	addq	$16, %rbp
	movq	%rax, %rbx
	cmpq	%rbp, %rdi
	je	.L109
	vzeroupper
	call	_ZdlPv@PLT
.L101:
	movq	%rbx, %rdi
	call	_Unwind_Resume@PLT
.LEHE7:
.L109:
	vzeroupper
	jmp	.L101
	.cfi_endproc
.LFE10419:
	.section	.gcc_except_table
.LLSDA10419:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE10419-.LLSDACSB10419
.LLSDACSB10419:
	.uleb128 .LEHB5-.LFB10419
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB6-.LFB10419
	.uleb128 .LEHE6-.LEHB6
	.uleb128 .L104-.LFB10419
	.uleb128 0
	.uleb128 .LEHB7-.LFB10419
	.uleb128 .LEHE7-.LEHB7
	.uleb128 0
	.uleb128 0
.LLSDACSE10419:
	.section	.text._ZN12KOK_Graphics8SSAODataC2Eii,"axG",@progbits,_ZN12KOK_Graphics8SSAODataC5Eii,comdat
	.size	_ZN12KOK_Graphics8SSAODataC2Eii, .-_ZN12KOK_Graphics8SSAODataC2Eii
	.weak	_ZN12KOK_Graphics8SSAODataC1Eii
	.set	_ZN12KOK_Graphics8SSAODataC1Eii,_ZN12KOK_Graphics8SSAODataC2Eii
	.section	.rodata._ZN12KOK_Graphics16LightProcessDataC2Eii.str1.1,"aMS",@progbits,1
.LC7:
	.string	"./Shaders/pp_lights.fs"
	.section	.rodata._ZN12KOK_Graphics16LightProcessDataC2Eii.str1.8,"aMS",@progbits,1
	.align 8
.LC8:
	.string	"ERROR::FRAMEBUFFER:: Framebuffer for lights is not complete!"
	.section	.rodata._ZN12KOK_Graphics16LightProcessDataC2Eii.str1.1
.LC9:
	.string	"lightData"
	.section	.text._ZN12KOK_Graphics16LightProcessDataC2Eii,"axG",@progbits,_ZN12KOK_Graphics16LightProcessDataC5Eii,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN12KOK_Graphics16LightProcessDataC2Eii
	.type	_ZN12KOK_Graphics16LightProcessDataC2Eii, @function
_ZN12KOK_Graphics16LightProcessDataC2Eii:
.LFB10422:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA10422
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r12
	pushq	%rbx
	.cfi_offset 14, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	movl	%esi, %r14d
	movl	%edx, %r12d
	subq	$24, %rsp
	movq	$0, 32(%rdi)
	movq	$0, 40(%rdi)
	movq	$0, 48(%rdi)
	movl	%esi, 20(%rbx)
	leaq	.LC4(%rip), %rdi
	leaq	.LC7(%rip), %rsi
	movl	%edx, 24(%rbx)
	movq	%fs:40, %rax
	movq	%rax, -40(%rbp)
	xorl	%eax, %eax
.LEHB8:
	call	_Z11LoadShadersPKcS0_@PLT
	movl	%eax, (%rbx)
	leaq	4(%rbx), %rsi
	movl	$1, %edi
	call	*__glewGenFramebuffers(%rip)
	movl	4(%rbx), %esi
	movl	$36160, %edi
	call	*__glewBindFramebuffer(%rip)
	leaq	8(%rbx), %rsi
	movl	$1, %edi
	call	glGenTextures@PLT
	movl	8(%rbx), %esi
	movl	$3553, %edi
	call	glBindTexture@PLT
	subq	$8, %rsp
	xorl	%r9d, %r9d
	movl	%r12d, %r8d
	pushq	$0
	pushq	$5126
	movl	%r14d, %ecx
	pushq	$6408
	movl	$34842, %edx
	xorl	%esi, %esi
	movl	$3553, %edi
	.cfi_escape 0x2e,0x20
	call	glTexImage2D@PLT
	addq	$32, %rsp
	movl	$9728, %edx
	movl	$10241, %esi
	movl	$3553, %edi
	.cfi_escape 0x2e,0
	call	glTexParameteri@PLT
	movl	$9728, %edx
	movl	$10240, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	8(%rbx), %ecx
	xorl	%r8d, %r8d
	movl	$3553, %edx
	movl	$36064, %esi
	movl	$36160, %edi
	call	*__glewFramebufferTexture2D(%rip)
	leaq	12(%rbx), %rsi
	movl	$1, %edi
	call	glGenTextures@PLT
	movl	12(%rbx), %esi
	movl	$3553, %edi
	call	glBindTexture@PLT
	subq	$8, %rsp
	xorl	%r9d, %r9d
	movl	%r12d, %r8d
	pushq	$0
	pushq	$5126
	movl	%r14d, %ecx
	pushq	$6407
	movl	$32849, %edx
	xorl	%esi, %esi
	movl	$3553, %edi
	.cfi_escape 0x2e,0x20
	call	glTexImage2D@PLT
	addq	$32, %rsp
	movl	$9728, %edx
	movl	$10241, %esi
	movl	$3553, %edi
	.cfi_escape 0x2e,0
	call	glTexParameteri@PLT
	movl	$9728, %edx
	movl	$10240, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	12(%rbx), %ecx
	xorl	%r8d, %r8d
	movl	$3553, %edx
	movl	$36065, %esi
	movl	$36160, %edi
	call	*__glewFramebufferTexture2D(%rip)
	movabsq	$154897995566304, %rax
	leaq	-48(%rbp), %rsi
	movl	$2, %edi
	movq	%rax, -48(%rbp)
	call	*__glewDrawBuffers(%rip)
	movl	$36160, %edi
	call	*__glewCheckFramebufferStatus(%rip)
	cmpl	$36053, %eax
	jne	.L115
.L120:
	xorl	%esi, %esi
	movl	$36160, %edi
	call	*__glewBindFramebuffer(%rip)
	leaq	16(%rbx), %rsi
	movl	$1, %edi
	call	*__glewGenBuffers(%rip)
	movl	16(%rbx), %esi
	movl	$35345, %edi
	call	*__glewBindBuffer(%rip)
	movl	$35044, %ecx
	xorl	%edx, %edx
	movl	$480, %esi
	movl	$35345, %edi
	call	*__glewBufferData(%rip)
	xorl	%esi, %esi
	movl	$35345, %edi
	call	*__glewBindBuffer(%rip)
	movl	16(%rbx), %edx
	movl	$2, %esi
	movl	$35345, %edi
	call	*__glewBindBufferBase(%rip)
	movl	(%rbx), %edi
	call	*__glewUseProgram(%rip)
	leaq	.LC9(%rip), %rsi
	movl	(%rbx), %edi
	call	*__glewGetUniformBlockIndex(%rip)
	movl	$2, %edx
	movl	%eax, %esi
	movl	(%rbx), %edi
	call	*__glewUniformBlockBinding(%rip)
	movq	-40(%rbp), %rax
	xorq	%fs:40, %rax
	jne	.L134
	leaq	-24(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r14
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
	.p2align 4,,10
	.p2align 3
.L115:
	.cfi_restore_state
	leaq	.LC8(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	movl	$60, %edx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	_ZSt4cout(%rip), %rax
	leaq	_ZSt4cout(%rip), %rdx
	movq	-24(%rax), %rax
	movq	240(%rdx,%rax), %rax
	testq	%rax, %rax
	movq	%rax, %r14
	je	.L135
	cmpb	$0, 56(%rax)
	je	.L118
	movsbl	67(%rax), %esi
.L119:
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	jmp	.L120
	.p2align 4,,10
	.p2align 3
.L118:
	movq	%rax, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%r14), %rax
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L119
	movq	%r14, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L119
.L134:
	call	__stack_chk_fail@PLT
.L135:
	call	_ZSt16__throw_bad_castv@PLT
.LEHE8:
.L125:
	movq	32(%rbx), %rdi
	movq	%rax, %r14
	testq	%rdi, %rdi
	je	.L131
	vzeroupper
	call	_ZdlPv@PLT
.L122:
	movq	%r14, %rdi
.LEHB9:
	call	_Unwind_Resume@PLT
.LEHE9:
.L131:
	vzeroupper
	jmp	.L122
	.cfi_endproc
.LFE10422:
	.section	.gcc_except_table
.LLSDA10422:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE10422-.LLSDACSB10422
.LLSDACSB10422:
	.uleb128 .LEHB8-.LFB10422
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L125-.LFB10422
	.uleb128 0
	.uleb128 .LEHB9-.LFB10422
	.uleb128 .LEHE9-.LEHB9
	.uleb128 0
	.uleb128 0
.LLSDACSE10422:
	.section	.text._ZN12KOK_Graphics16LightProcessDataC2Eii,"axG",@progbits,_ZN12KOK_Graphics16LightProcessDataC5Eii,comdat
	.size	_ZN12KOK_Graphics16LightProcessDataC2Eii, .-_ZN12KOK_Graphics16LightProcessDataC2Eii
	.weak	_ZN12KOK_Graphics16LightProcessDataC1Eii
	.set	_ZN12KOK_Graphics16LightProcessDataC1Eii,_ZN12KOK_Graphics16LightProcessDataC2Eii
	.section	.text._ZN12KOK_Graphics15TextProcessDataC2Eii,"axG",@progbits,_ZN12KOK_Graphics15TextProcessDataC5Eii,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN12KOK_Graphics15TextProcessDataC2Eii
	.type	_ZN12KOK_Graphics15TextProcessDataC2Eii, @function
_ZN12KOK_Graphics15TextProcessDataC2Eii:
.LFB10427:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movl	%edx, %r12d
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	movl	%esi, %ebp
	movq	%rdi, %rsi
	movl	$1, %edi
	call	*__glewGenFramebuffers(%rip)
	movl	(%rbx), %esi
	movl	$36160, %edi
	call	*__glewBindFramebuffer(%rip)
	leaq	4(%rbx), %rsi
	movl	$1, %edi
	call	glGenTextures@PLT
	movl	4(%rbx), %esi
	movl	$3553, %edi
	call	glBindTexture@PLT
	subq	$8, %rsp
	.cfi_def_cfa_offset 40
	movl	%r12d, %r8d
	movl	%ebp, %ecx
	pushq	$0
	.cfi_def_cfa_offset 48
	pushq	$5121
	.cfi_def_cfa_offset 56
	xorl	%r9d, %r9d
	pushq	$6407
	.cfi_def_cfa_offset 64
	movl	$6407, %edx
	xorl	%esi, %esi
	movl	$3553, %edi
	call	glTexImage2D@PLT
	addq	$32, %rsp
	.cfi_def_cfa_offset 32
	movl	$9728, %edx
	movl	$10240, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	$10241, %esi
	movl	$3553, %edi
	movl	$9728, %edx
	call	glTexParameteri@PLT
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	xorl	%esi, %esi
	movl	$36160, %edi
	jmp	*__glewBindFramebuffer(%rip)
	.cfi_endproc
.LFE10427:
	.size	_ZN12KOK_Graphics15TextProcessDataC2Eii, .-_ZN12KOK_Graphics15TextProcessDataC2Eii
	.weak	_ZN12KOK_Graphics15TextProcessDataC1Eii
	.set	_ZN12KOK_Graphics15TextProcessDataC1Eii,_ZN12KOK_Graphics15TextProcessDataC2Eii
	.section	.rodata._ZN12KOK_Graphics20DeferredLightingDataC2Eii.str1.1,"aMS",@progbits,1
.LC10:
	.string	"./Shaders/deferredShader.fs"
.LC11:
	.string	"./Shaders/deferredShader.vs"
	.section	.rodata._ZN12KOK_Graphics20DeferredLightingDataC2Eii.str1.8,"aMS",@progbits,1
	.align 8
.LC13:
	.string	"ERROR::FRAMEBUFFER:: Framebuffer is not complete!"
	.section	.text._ZN12KOK_Graphics20DeferredLightingDataC2Eii,"axG",@progbits,_ZN12KOK_Graphics20DeferredLightingDataC5Eii,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN12KOK_Graphics20DeferredLightingDataC2Eii
	.type	_ZN12KOK_Graphics20DeferredLightingDataC2Eii, @function
_ZN12KOK_Graphics20DeferredLightingDataC2Eii:
.LFB10433:
	.cfi_startproc
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-32, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r13
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x68,0x6
	.cfi_escape 0x10,0xd,0x2,0x76,0x78
	.cfi_escape 0x10,0xc,0x2,0x76,0x70
	pushq	%rbx
	movl	%esi, %r12d
	.cfi_escape 0x10,0x3,0x2,0x76,0x60
	movq	%rdi, %rbx
	leaq	.LC10(%rip), %rsi
	leaq	.LC11(%rip), %rdi
	subq	$80, %rsp
	movl	%edx, %r13d
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	call	_Z11LoadShadersPKcS0_@PLT
	leaq	4(%rbx), %rsi
	movl	%eax, (%rbx)
	movl	$1, %edi
	call	*__glewGenFramebuffers(%rip)
	movl	4(%rbx), %esi
	movl	$36160, %edi
	call	*__glewBindFramebuffer(%rip)
	leaq	8(%rbx), %rsi
	movl	$1, %edi
	call	glGenTextures@PLT
	movl	8(%rbx), %esi
	movl	$3553, %edi
	call	glBindTexture@PLT
	subq	$8, %rsp
	xorl	%r9d, %r9d
	movl	%r13d, %r8d
	pushq	$0
	pushq	$5126
	movl	%r12d, %ecx
	pushq	$6407
	xorl	%esi, %esi
	movl	$34843, %edx
	movl	$3553, %edi
	call	glTexImage2D@PLT
	addq	$32, %rsp
	movl	$9728, %edx
	movl	$10241, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	$9728, %edx
	movl	$10240, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	8(%rbx), %ecx
	xorl	%r8d, %r8d
	movl	$3553, %edx
	movl	$36064, %esi
	movl	$36160, %edi
	call	*__glewFramebufferTexture2D(%rip)
	leaq	12(%rbx), %rsi
	movl	$1, %edi
	call	glGenTextures@PLT
	movl	12(%rbx), %esi
	movl	$3553, %edi
	call	glBindTexture@PLT
	subq	$8, %rsp
	xorl	%r9d, %r9d
	movl	%r13d, %r8d
	pushq	$0
	pushq	$5126
	movl	%r12d, %ecx
	pushq	$6407
	xorl	%esi, %esi
	movl	$34843, %edx
	movl	$3553, %edi
	call	glTexImage2D@PLT
	addq	$32, %rsp
	movl	$9728, %edx
	movl	$10241, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	$9728, %edx
	movl	$10240, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	12(%rbx), %ecx
	xorl	%r8d, %r8d
	movl	$3553, %edx
	movl	$36065, %esi
	movl	$36160, %edi
	call	*__glewFramebufferTexture2D(%rip)
	leaq	16(%rbx), %rsi
	movl	$1, %edi
	call	glGenTextures@PLT
	movl	16(%rbx), %esi
	movl	$3553, %edi
	call	glBindTexture@PLT
	subq	$8, %rsp
	xorl	%r9d, %r9d
	movl	%r13d, %r8d
	pushq	$0
	pushq	$5121
	xorl	%esi, %esi
	pushq	$6408
	movl	%r12d, %ecx
	movl	$32856, %edx
	movl	$3553, %edi
	call	glTexImage2D@PLT
	addq	$32, %rsp
	movl	$9728, %edx
	movl	$10241, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	$9728, %edx
	movl	$10240, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	16(%rbx), %ecx
	xorl	%r8d, %r8d
	movl	$3553, %edx
	movl	$36066, %esi
	movl	$36160, %edi
	call	*__glewFramebufferTexture2D(%rip)
	leaq	20(%rbx), %rsi
	movl	$1, %edi
	call	glGenTextures@PLT
	movl	20(%rbx), %esi
	movl	$3553, %edi
	call	glBindTexture@PLT
	subq	$8, %rsp
	xorl	%r9d, %r9d
	movl	%r13d, %r8d
	pushq	$0
	pushq	$5121
	movl	%r12d, %ecx
	pushq	$6408
	xorl	%esi, %esi
	movl	$32856, %edx
	movl	$3553, %edi
	call	glTexImage2D@PLT
	addq	$32, %rsp
	movl	$9728, %edx
	movl	$10241, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	$9728, %edx
	movl	$10240, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	20(%rbx), %ecx
	xorl	%r8d, %r8d
	movl	$3553, %edx
	movl	$36067, %esi
	movl	$36160, %edi
	call	*__glewFramebufferTexture2D(%rip)
	leaq	36(%rbx), %rsi
	movl	$1, %edi
	call	glGenTextures@PLT
	movl	36(%rbx), %esi
	movl	$3553, %edi
	call	glBindTexture@PLT
	subq	$8, %rsp
	xorl	%r9d, %r9d
	movl	%r13d, %r8d
	pushq	$0
	pushq	$5126
	movl	%r12d, %ecx
	pushq	$6407
	xorl	%esi, %esi
	movl	$34837, %edx
	movl	$3553, %edi
	call	glTexImage2D@PLT
	addq	$32, %rsp
	movl	$9728, %edx
	movl	$10241, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	$9728, %edx
	movl	$10240, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	36(%rbx), %ecx
	xorl	%r8d, %r8d
	movl	$3553, %edx
	movl	$36068, %esi
	movl	$36160, %edi
	call	*__glewFramebufferTexture2D(%rip)
	leaq	32(%rbx), %rsi
	movl	$1, %edi
	call	glGenTextures@PLT
	movl	32(%rbx), %esi
	movl	$3553, %edi
	call	glBindTexture@PLT
	subq	$8, %rsp
	movl	%r13d, %r8d
	xorl	%r9d, %r9d
	pushq	$0
	pushq	$5126
	movl	%r12d, %ecx
	pushq	$6407
	xorl	%esi, %esi
	movl	$34843, %edx
	movl	$3553, %edi
	call	glTexImage2D@PLT
	addq	$32, %rsp
	movl	$9728, %edx
	movl	$10241, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	$9728, %edx
	movl	$10240, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	32(%rbx), %ecx
	xorl	%r8d, %r8d
	movl	$3553, %edx
	movl	$36069, %esi
	movl	$36160, %edi
	call	*__glewFramebufferTexture2D(%rip)
	leaq	28(%rbx), %rsi
	movl	$1, %edi
	call	glGenTextures@PLT
	movl	28(%rbx), %esi
	movl	$3553, %edi
	call	glBindTexture@PLT
	subq	$8, %rsp
	xorl	%r9d, %r9d
	movl	%r13d, %r8d
	pushq	$0
	pushq	$5126
	movl	%r12d, %ecx
	pushq	$6403
	xorl	%esi, %esi
	movl	$33326, %edx
	movl	$3553, %edi
	call	glTexImage2D@PLT
	addq	$32, %rsp
	movl	$9728, %edx
	movl	$10241, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	$9728, %edx
	movl	$10240, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	28(%rbx), %ecx
	xorl	%r8d, %r8d
	movl	$3553, %edx
	movl	$36070, %esi
	movl	$36160, %edi
	call	*__glewFramebufferTexture2D(%rip)
	leaq	24(%rbx), %rsi
	movl	$1, %edi
	call	glGenTextures@PLT
	movl	24(%rbx), %esi
	movl	$3553, %edi
	call	glBindTexture@PLT
	subq	$8, %rsp
	xorl	%r9d, %r9d
	movl	%r13d, %r8d
	pushq	$0
	pushq	$5121
	movl	%r12d, %ecx
	pushq	$6408
	xorl	%esi, %esi
	movl	$32856, %edx
	movl	$3553, %edi
	call	glTexImage2D@PLT
	addq	$32, %rsp
	movl	$9728, %edx
	movl	$10241, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	$9728, %edx
	movl	$10240, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	xorl	%r8d, %r8d
	movl	24(%rbx), %ecx
	movl	$3553, %edx
	movl	$36071, %esi
	movl	$36160, %edi
	call	*__glewFramebufferTexture2D(%rip)
	leaq	40(%rbx), %rsi
	movl	$1, %edi
	call	*__glewGenRenderbuffers(%rip)
	movl	40(%rbx), %esi
	movl	$36161, %edi
	call	*__glewBindRenderbuffer(%rip)
	movl	%r13d, %ecx
	movl	%r12d, %edx
	movl	$35056, %esi
	movl	$36161, %edi
	call	*__glewRenderbufferStorage(%rip)
	xorl	%esi, %esi
	movl	$36161, %edi
	call	*__glewBindRenderbuffer(%rip)
	movl	40(%rbx), %ecx
	movl	$36161, %edx
	movl	$33306, %esi
	movl	$36160, %edi
	call	*__glewFramebufferRenderbuffer(%rip)
	vmovdqa	.LC12(%rip), %ymm0
	leaq	-112(%rbp), %rsi
	movl	$8, %edi
	vmovdqa	%ymm0, -112(%rbp)
	vzeroupper
	call	*__glewDrawBuffers(%rip)
	movl	$36160, %edi
	call	*__glewCheckFramebufferStatus(%rip)
	cmpl	$36053, %eax
	je	.L139
	leaq	.LC13(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	movl	$49, %edx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	_ZSt4cout(%rip), %rax
	leaq	_ZSt4cout(%rip), %rdx
	movq	-24(%rax), %rax
	movq	240(%rdx,%rax), %rbx
	testq	%rbx, %rbx
	je	.L150
	cmpb	$0, 56(%rbx)
	je	.L141
	movsbl	67(%rbx), %esi
.L142:
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
.L139:
	xorl	%esi, %esi
	movl	$36160, %edi
	call	*__glewBindFramebuffer(%rip)
	movq	-56(%rbp), %rax
	xorq	%fs:40, %rax
	jne	.L151
	leaq	-32(%rbp), %rsp
	popq	%rbx
	popq	%r10
	.cfi_remember_state
	.cfi_def_cfa 10, 0
	popq	%r12
	popq	%r13
	popq	%rbp
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.p2align 4,,10
	.p2align 3
.L141:
	.cfi_restore_state
	movq	%rbx, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%rbx), %rax
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L142
	movq	%rbx, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L142
.L150:
	call	_ZSt16__throw_bad_castv@PLT
.L151:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE10433:
	.size	_ZN12KOK_Graphics20DeferredLightingDataC2Eii, .-_ZN12KOK_Graphics20DeferredLightingDataC2Eii
	.weak	_ZN12KOK_Graphics20DeferredLightingDataC1Eii
	.set	_ZN12KOK_Graphics20DeferredLightingDataC1Eii,_ZN12KOK_Graphics20DeferredLightingDataC2Eii
	.section	.rodata._ZN12KOK_Graphics10ShadowDataC2Eii.str1.1,"aMS",@progbits,1
.LC14:
	.string	"./Shaders/shadowDraw.fs"
.LC15:
	.string	"./Shaders/shadowDraw.vs"
	.section	.text._ZN12KOK_Graphics10ShadowDataC2Eii,"axG",@progbits,_ZN12KOK_Graphics10ShadowDataC5Eii,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN12KOK_Graphics10ShadowDataC2Eii
	.type	_ZN12KOK_Graphics10ShadowDataC2Eii, @function
_ZN12KOK_Graphics10ShadowDataC2Eii:
.LFB10436:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r13
	.cfi_offset 13, -24
	movl	%esi, %r13d
	pushq	%r12
	leaq	.LC14(%rip), %rsi
	pushq	%r10
	pushq	%rbx
	.cfi_offset 12, -32
	.cfi_offset 10, -40
	.cfi_offset 3, -48
	movq	%rdi, %rbx
	leaq	.LC15(%rip), %rdi
	movl	%edx, %r12d
	call	_Z11LoadShadersPKcS0_@PLT
	leaq	8(%rbx), %rsi
	movl	%eax, 16(%rbx)
	movl	$1, %edi
	call	*__glewGenFramebuffers(%rip)
	leaq	12(%rbx), %rsi
	movl	$1, %edi
	call	glGenTextures@PLT
	movl	12(%rbx), %esi
	movl	$3553, %edi
	call	glBindTexture@PLT
	subq	$8, %rsp
	xorl	%r9d, %r9d
	movl	%r12d, %r8d
	pushq	$0
	pushq	$5126
	movl	%r13d, %ecx
	pushq	$6402
	xorl	%esi, %esi
	movl	$6402, %edx
	movl	$3553, %edi
	call	glTexImage2D@PLT
	addq	$32, %rsp
	movl	$9728, %edx
	movl	$10241, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	$9728, %edx
	movl	$10240, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	$10497, %edx
	movl	$10242, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	$10497, %edx
	movl	$10243, %esi
	movl	$3553, %edi
	call	glTexParameteri@PLT
	movl	8(%rbx), %esi
	movl	$36160, %edi
	call	*__glewBindFramebuffer(%rip)
	movl	12(%rbx), %ecx
	xorl	%r8d, %r8d
	movl	$3553, %edx
	movl	$36096, %esi
	movl	$36160, %edi
	call	*__glewFramebufferTexture2D(%rip)
	xorl	%edi, %edi
	call	glDrawBuffer@PLT
	xorl	%edi, %edi
	call	glReadBuffer@PLT
	xorl	%esi, %esi
	movl	$36160, %edi
	call	*__glewBindFramebuffer(%rip)
	vmovaps	.LC16(%rip), %ymm0
	movl	%r13d, (%rbx)
	movl	%r12d, 4(%rbx)
	movl	$0x3f800000, 84(%rbx)
	vmovups	%xmm0, 20(%rbx)
	vextractf128	$0x1, %ymm0, 36(%rbx)
	vmovaps	.LC17(%rip), %ymm0
	vmovups	%xmm0, 52(%rbx)
	vextractf128	$0x1, %ymm0, 68(%rbx)
	vzeroupper
	leaq	-32(%rbp), %rsp
	popq	%rbx
	popq	%r10
	popq	%r12
	popq	%r13
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10436:
	.size	_ZN12KOK_Graphics10ShadowDataC2Eii, .-_ZN12KOK_Graphics10ShadowDataC2Eii
	.weak	_ZN12KOK_Graphics10ShadowDataC1Eii
	.set	_ZN12KOK_Graphics10ShadowDataC1Eii,_ZN12KOK_Graphics10ShadowDataC2Eii
	.section	.text._Z18InitWindowTexturesv,"axG",@progbits,_Z18InitWindowTexturesv,comdat
	.p2align 4,,15
	.weak	_Z18InitWindowTexturesv
	.type	_Z18InitWindowTexturesv, @function
_Z18InitWindowTexturesv:
.LFB16944:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA16944
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movl	$27, %edi
	subq	$72, %rsp
	.cfi_def_cfa_offset 96
	leaq	16(%rsp), %rbx
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	leaq	16(%rbx), %rax
	movq	%rax, 16(%rsp)
.LEHB10:
	call	_Znwm@PLT
.LEHE10:
	vmovdqa	.LC19(%rip), %xmm0
	movl	$26478, %edx
	movabsq	$8083457966959518578, %rcx
	movw	%dx, 24(%rax)
	leaq	15(%rsp), %rdx
	vmovups	%xmm0, (%rax)
	movq	%rcx, 16(%rax)
	movb	$0, 26(%rax)
	xorl	%esi, %esi
	movq	%rbx, %rdi
	movq	%rax, 16(%rsp)
	movq	$26, 32(%rsp)
	movq	$26, 24(%rsp)
.LEHB11:
	call	_ZN10KOK_Imager7LoadPNGENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEbRb@PLT
.LEHE11:
	movq	16(%rsp), %rdi
	addq	$16, %rbx
	movl	%eax, _ZN17KOK_WindowManager8Textures8circle16E(%rip)
	cmpq	%rbx, %rdi
	je	.L154
	call	_ZdlPv@PLT
.L154:
	movq	56(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L163
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L163:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
.L159:
	movq	16(%rsp), %rdi
	addq	$16, %rbx
	movq	%rax, %rbp
	cmpq	%rbx, %rdi
	je	.L160
	vzeroupper
	call	_ZdlPv@PLT
.L157:
	movq	%rbp, %rdi
.LEHB12:
	call	_Unwind_Resume@PLT
.LEHE12:
.L160:
	vzeroupper
	jmp	.L157
	.cfi_endproc
.LFE16944:
	.section	.gcc_except_table
.LLSDA16944:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE16944-.LLSDACSB16944
.LLSDACSB16944:
	.uleb128 .LEHB10-.LFB16944
	.uleb128 .LEHE10-.LEHB10
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB11-.LFB16944
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L159-.LFB16944
	.uleb128 0
	.uleb128 .LEHB12-.LFB16944
	.uleb128 .LEHE12-.LEHB12
	.uleb128 0
	.uleb128 0
.LLSDACSE16944:
	.section	.text._Z18InitWindowTexturesv,"axG",@progbits,_Z18InitWindowTexturesv,comdat
	.size	_Z18InitWindowTexturesv, .-_Z18InitWindowTexturesv
	.section	.text._ZN14KOK_PostOfficeD2Ev,"axG",@progbits,_ZN14KOK_PostOfficeD5Ev,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN14KOK_PostOfficeD2Ev
	.type	_ZN14KOK_PostOfficeD2Ev, @function
_ZN14KOK_PostOfficeD2Ev:
.LFB16959:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	248(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L165
	movq	320(%rbp), %rax
	movq	288(%rbp), %rbx
	leaq	8(%rax), %r12
	cmpq	%rbx, %r12
	jbe	.L166
	.p2align 4,,10
	.p2align 3
.L167:
	movq	(%rbx), %rdi
	addq	$8, %rbx
	call	_ZdlPv@PLT
	cmpq	%rbx, %r12
	ja	.L167
	movq	248(%rbp), %rdi
.L166:
	call	_ZdlPv@PLT
.L165:
	movq	168(%rbp), %rdi
	testq	%rdi, %rdi
	je	.L168
	movq	240(%rbp), %rax
	movq	208(%rbp), %rbx
	leaq	8(%rax), %r12
	cmpq	%rbx, %r12
	jbe	.L169
	.p2align 4,,10
	.p2align 3
.L170:
	movq	(%rbx), %rdi
	addq	$8, %rbx
	call	_ZdlPv@PLT
	cmpq	%rbx, %r12
	ja	.L170
	movq	168(%rbp), %rdi
.L169:
	call	_ZdlPv@PLT
.L168:
	movq	88(%rbp), %rdi
	testq	%rdi, %rdi
	je	.L171
	movq	160(%rbp), %rax
	movq	128(%rbp), %rbx
	leaq	8(%rax), %r12
	cmpq	%rbx, %r12
	jbe	.L172
	.p2align 4,,10
	.p2align 3
.L173:
	movq	(%rbx), %rdi
	addq	$8, %rbx
	call	_ZdlPv@PLT
	cmpq	%rbx, %r12
	ja	.L173
	movq	88(%rbp), %rdi
.L172:
	call	_ZdlPv@PLT
.L171:
	movq	8(%rbp), %rdi
	testq	%rdi, %rdi
	je	.L190
	movq	80(%rbp), %rax
	movq	48(%rbp), %rbx
	leaq	8(%rax), %r12
	cmpq	%rbx, %r12
	jbe	.L175
	.p2align 4,,10
	.p2align 3
.L176:
	movq	(%rbx), %rdi
	addq	$8, %rbx
	call	_ZdlPv@PLT
	cmpq	%rbx, %r12
	ja	.L176
	movq	8(%rbp), %rdi
.L175:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZdlPv@PLT
	.p2align 4,,10
	.p2align 3
.L190:
	.cfi_restore_state
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE16959:
	.size	_ZN14KOK_PostOfficeD2Ev, .-_ZN14KOK_PostOfficeD2Ev
	.weak	_ZN14KOK_PostOfficeD1Ev
	.set	_ZN14KOK_PostOfficeD1Ev,_ZN14KOK_PostOfficeD2Ev
	.section	.text._ZN8KOK_MeshD2Ev,"axG",@progbits,_ZN8KOK_MeshD5Ev,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN8KOK_MeshD2Ev
	.type	_ZN8KOK_MeshD2Ev, @function
_ZN8KOK_MeshD2Ev:
.LFB16966:
	.cfi_startproc
	leaq	16+_ZTV8KOK_Mesh(%rip), %rax
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movq	%rax, (%rdi)
	movq	200(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L193
	call	_ZdlPv@PLT
.L193:
	movq	176(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L194
	call	_ZdlPv@PLT
.L194:
	movq	8(%rbx), %rdi
	leaq	16+_ZTV9KOK_Actor(%rip), %rax
	addq	$24, %rbx
	movq	%rax, -24(%rbx)
	cmpq	%rbx, %rdi
	je	.L202
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	jmp	_ZdlPv@PLT
	.p2align 4,,10
	.p2align 3
.L202:
	.cfi_restore_state
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE16966:
	.size	_ZN8KOK_MeshD2Ev, .-_ZN8KOK_MeshD2Ev
	.weak	_ZN8KOK_MeshD1Ev
	.set	_ZN8KOK_MeshD1Ev,_ZN8KOK_MeshD2Ev
	.section	.text._ZNSt11_Deque_baseI11KOK_MessageSaIS0_EED2Ev,"axG",@progbits,_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EED5Ev,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EED2Ev
	.type	_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EED2Ev, @function
_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EED2Ev:
.LFB18754:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L209
	movq	72(%r12), %rax
	movq	40(%r12), %rbx
	leaq	8(%rax), %rbp
	cmpq	%rbx, %rbp
	jbe	.L206
	.p2align 4,,10
	.p2align 3
.L207:
	movq	(%rbx), %rdi
	addq	$8, %rbx
	call	_ZdlPv@PLT
	cmpq	%rbx, %rbp
	ja	.L207
	movq	(%r12), %rdi
.L206:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZdlPv@PLT
	.p2align 4,,10
	.p2align 3
.L209:
	.cfi_restore_state
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE18754:
	.size	_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EED2Ev, .-_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EED2Ev
	.weak	_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EED1Ev
	.set	_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EED1Ev,_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EED2Ev
	.section	.rodata._ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm.str1.1,"aMS",@progbits,1
.LC20:
	.string	"basic_string::_M_replace"
.LC21:
	.string	"basic_string::_M_create"
	.section	.text._ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm,"axG",@progbits,_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm
	.type	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm, @function
_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm:
.LFB18889:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movabsq	$9223372036854775807, %rax
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	addq	%r12, %rax
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	8(%rdi), %rdx
	subq	%rdx, %rax
	cmpq	%rax, %r8
	ja	.L274
	movq	(%rdi), %rax
	leaq	16(%rdi), %r10
	movq	%rdx, %r9
	subq	%rsi, %r9
	movq	%r8, %r15
	movq	%rdi, %rbx
	subq	%r12, %r15
	subq	%r12, %r9
	movq	%rsi, %r13
	cmpq	%rax, %r10
	movq	%r8, %rbp
	leaq	(%rdx,%r15), %r14
	je	.L213
	movq	16(%rdi), %rsi
	cmpq	%rsi, %r14
	ja	.L214
.L249:
	addq	%rax, %r13
	testq	%r9, %r9
	setne	%r10b
	cmpq	%rbp, %r12
	setne	%sil
	andl	%esi, %r10d
	cmpq	%rax, %rcx
	jnb	.L275
.L215:
	testb	%r10b, %r10b
	je	.L219
	cmpq	$1, %r9
	leaq	0(%r13,%r12), %rsi
	leaq	0(%r13,%rbp), %rdi
	je	.L276
	movq	%r9, %rdx
	movq	%rcx, (%rsp)
	call	memmove@PLT
	movq	(%rsp), %rcx
	.p2align 4,,10
	.p2align 3
.L219:
	testq	%rbp, %rbp
	je	.L272
	cmpq	$1, %rbp
	jne	.L223
.L273:
	movzbl	(%rcx), %eax
	movb	%al, 0(%r13)
	movq	(%rbx), %r11
	jmp	.L222
	.p2align 4,,10
	.p2align 3
.L275:
	addq	%rdx, %rax
	cmpq	%rax, %rcx
	ja	.L215
	testq	%rbp, %rbp
	je	.L218
	cmpq	%rbp, %r12
	jb	.L218
	cmpq	$1, %rbp
	je	.L277
	movq	%rcx, %rsi
	movq	%rbp, %rdx
	movq	%r13, %rdi
	movq	%r9, 16(%rsp)
	movb	%r10b, 8(%rsp)
	movq	%rcx, (%rsp)
	call	memmove@PLT
	movzbl	8(%rsp), %r10d
	movq	(%rsp), %rcx
	movq	16(%rsp), %r9
	testb	%r10b, %r10b
	je	.L272
	.p2align 4,,10
	.p2align 3
.L225:
	cmpq	$1, %r9
	leaq	0(%r13,%r12), %rsi
	leaq	0(%r13,%rbp), %rdi
	je	.L278
	movq	%r9, %rdx
	movq	%rcx, (%rsp)
	call	memmove@PLT
	movq	(%rsp), %rcx
	.p2align 4,,10
	.p2align 3
.L228:
	cmpq	%rbp, %r12
	jnb	.L272
	leaq	(%rcx,%rbp), %rax
	addq	%r13, %r12
	cmpq	%rax, %r12
	jnb	.L279
	cmpq	%rcx, %r12
	ja	.L232
	cmpq	$1, %rbp
	leaq	(%rcx,%r15), %rsi
	je	.L280
	movq	%rbp, %rdx
	movq	%r13, %rdi
	call	memcpy@PLT
	movq	(%rbx), %r11
	jmp	.L222
	.p2align 4,,10
	.p2align 3
.L232:
	subq	%rcx, %r12
	cmpq	$1, %r12
	je	.L281
	testq	%r12, %r12
	jne	.L282
.L235:
	movq	%rbp, %rdx
	leaq	0(%r13,%rbp), %rsi
	leaq	0(%r13,%r12), %rdi
	subq	%r12, %rdx
	cmpq	$1, %rdx
	je	.L283
	testq	%rdx, %rdx
	je	.L272
	call	memcpy@PLT
	.p2align 4,,10
	.p2align 3
.L272:
	movq	(%rbx), %r11
.L222:
	movq	%r14, 8(%rbx)
	movb	$0, (%r11,%r14)
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L213:
	.cfi_restore_state
	cmpq	$15, %r14
	movl	$15, %esi
	jbe	.L249
.L214:
	testq	%r14, %r14
	js	.L284
	leaq	(%rsi,%rsi), %r15
	cmpq	%r15, %r14
	jnb	.L285
	testq	%r15, %r15
	leaq	1(%r15), %rdi
	jns	.L240
	movabsq	$-9223372036854775808, %rdi
	movabsq	$9223372036854775807, %r15
	jmp	.L240
	.p2align 4,,10
	.p2align 3
.L223:
	movq	%rbp, %rdx
	movq	%rcx, %rsi
	movq	%r13, %rdi
	call	memcpy@PLT
	movq	(%rbx), %r11
	jmp	.L222
	.p2align 4,,10
	.p2align 3
.L276:
	movzbl	(%rsi), %eax
	movb	%al, (%rdi)
	jmp	.L219
	.p2align 4,,10
	.p2align 3
.L285:
	leaq	1(%r14), %rdi
	movq	%r14, %r15
.L240:
	movq	%rcx, 16(%rsp)
	movq	%r9, 8(%rsp)
	movq	%r10, (%rsp)
	call	_Znwm@PLT
	testq	%r13, %r13
	movq	%rax, %r11
	movq	(%rbx), %r8
	movq	(%rsp), %r10
	movq	8(%rsp), %r9
	movq	16(%rsp), %rcx
	je	.L242
	cmpq	$1, %r13
	jne	.L243
	movzbl	(%r8), %eax
	movb	%al, (%r11)
.L242:
	testq	%rcx, %rcx
	je	.L244
	testq	%rbp, %rbp
	je	.L244
	cmpq	$1, %rbp
	leaq	(%r11,%r13), %rdi
	je	.L286
	movq	%rbp, %rdx
	movq	%rcx, %rsi
	movq	%r9, 24(%rsp)
	movq	%r8, 16(%rsp)
	movq	%r11, 8(%rsp)
	movq	%r10, (%rsp)
	call	memcpy@PLT
	movq	24(%rsp), %r9
	movq	16(%rsp), %r8
	movq	8(%rsp), %r11
	movq	(%rsp), %r10
	.p2align 4,,10
	.p2align 3
.L244:
	testq	%r9, %r9
	je	.L246
	leaq	(%r12,%r13), %rsi
	addq	%r13, %rbp
	leaq	(%r11,%rbp), %rdi
	addq	%r8, %rsi
	cmpq	$1, %r9
	jne	.L247
	movzbl	(%rsi), %eax
	movb	%al, (%rdi)
.L246:
	cmpq	%r8, %r10
	je	.L248
	movq	%r8, %rdi
	movq	%r11, (%rsp)
	call	_ZdlPv@PLT
	movq	(%rsp), %r11
.L248:
	movq	%r11, (%rbx)
	movq	%r15, 16(%rbx)
	jmp	.L222
	.p2align 4,,10
	.p2align 3
.L277:
	movzbl	(%rcx), %eax
	movb	%al, 0(%r13)
.L218:
	testb	%r10b, %r10b
	jne	.L225
	jmp	.L228
	.p2align 4,,10
	.p2align 3
.L247:
	movq	%r9, %rdx
	movq	%r8, 16(%rsp)
	movq	%r11, 8(%rsp)
	movq	%r10, (%rsp)
	call	memcpy@PLT
	movq	16(%rsp), %r8
	movq	8(%rsp), %r11
	movq	(%rsp), %r10
	jmp	.L246
	.p2align 4,,10
	.p2align 3
.L243:
	movq	%r8, %rsi
	movq	%r13, %rdx
	movq	%rax, %rdi
	movq	%rcx, 24(%rsp)
	movq	%r9, 16(%rsp)
	movq	%r10, 8(%rsp)
	movq	%r8, (%rsp)
	call	memcpy@PLT
	movq	24(%rsp), %rcx
	movq	16(%rsp), %r9
	movq	%rax, %r11
	movq	8(%rsp), %r10
	movq	(%rsp), %r8
	jmp	.L242
	.p2align 4,,10
	.p2align 3
.L286:
	movzbl	(%rcx), %eax
	movb	%al, (%rdi)
	jmp	.L244
	.p2align 4,,10
	.p2align 3
.L279:
	cmpq	$1, %rbp
	je	.L273
	movq	%rbp, %rdx
	movq	%rcx, %rsi
	movq	%r13, %rdi
	call	memmove@PLT
	movq	(%rbx), %r11
	jmp	.L222
	.p2align 4,,10
	.p2align 3
.L278:
	movzbl	(%rsi), %eax
	movb	%al, (%rdi)
	jmp	.L228
.L281:
	movzbl	(%rcx), %eax
	movb	%al, 0(%r13)
	jmp	.L235
.L280:
	movzbl	(%rsi), %eax
	movb	%al, 0(%r13)
	movq	(%rbx), %r11
	jmp	.L222
.L283:
	movzbl	(%rsi), %eax
	movb	%al, (%rdi)
	movq	(%rbx), %r11
	jmp	.L222
.L282:
	movq	%r12, %rdx
	movq	%rcx, %rsi
	movq	%r13, %rdi
	call	memmove@PLT
	jmp	.L235
.L274:
	leaq	.LC20(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
.L284:
	leaq	.LC21(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
	.cfi_endproc
.LFE18889:
	.size	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm, .-_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm
	.section	.text._ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm,"axG",@progbits,_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
	.type	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm, @function
_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm:
.LFB18953:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	leaq	16(%rdi), %r14
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdx, %r15
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%r8, %rbx
	subq	%rdx, %rbx
	movq	%rdi, %rbp
	movq	%rsi, %r12
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	8(%rdi), %rax
	movq	%rax, %r13
	addq	%rax, %rbx
	movl	$15, %eax
	subq	%rsi, %r13
	subq	%rdx, %r13
	cmpq	(%rdi), %r14
	je	.L288
	movq	16(%rdi), %rax
.L288:
	testq	%rbx, %rbx
	js	.L315
	cmpq	%rax, %rbx
	jbe	.L314
	addq	%rax, %rax
	cmpq	%rax, %rbx
	jnb	.L314
	testq	%rax, %rax
	movabsq	$-9223372036854775808, %rdi
	movabsq	$9223372036854775807, %rbx
	js	.L291
	leaq	1(%rax), %rdi
	movq	%rax, %rbx
	jmp	.L291
	.p2align 4,,10
	.p2align 3
.L314:
	leaq	1(%rbx), %rdi
.L291:
	movq	%r8, 16(%rsp)
	movq	%rcx, 8(%rsp)
	call	_Znwm@PLT
	testq	%r12, %r12
	movq	%rax, %r10
	movq	0(%rbp), %r9
	movq	8(%rsp), %rcx
	movq	16(%rsp), %r8
	je	.L294
	cmpq	$1, %r12
	jne	.L295
	movzbl	(%r9), %eax
	movb	%al, (%r10)
.L294:
	testq	%rcx, %rcx
	je	.L296
	testq	%r8, %r8
	je	.L296
	cmpq	$1, %r8
	leaq	(%r10,%r12), %rdi
	je	.L316
	movq	%r8, %rdx
	movq	%rcx, %rsi
	movq	%r9, 24(%rsp)
	movq	%r10, 16(%rsp)
	movq	%r8, 8(%rsp)
	call	memcpy@PLT
	movq	24(%rsp), %r9
	movq	16(%rsp), %r10
	movq	8(%rsp), %r8
	.p2align 4,,10
	.p2align 3
.L296:
	testq	%r13, %r13
	jne	.L317
.L298:
	cmpq	%r9, %r14
	je	.L300
	movq	%r9, %rdi
	movq	%r10, 8(%rsp)
	call	_ZdlPv@PLT
	movq	8(%rsp), %r10
.L300:
	movq	%r10, 0(%rbp)
	movq	%rbx, 16(%rbp)
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L317:
	.cfi_restore_state
	leaq	(%r12,%r15), %rsi
	leaq	(%r12,%r8), %rdi
	addq	%r9, %rsi
	addq	%r10, %rdi
	cmpq	$1, %r13
	jne	.L299
	movzbl	(%rsi), %eax
	movb	%al, (%rdi)
	jmp	.L298
	.p2align 4,,10
	.p2align 3
.L299:
	movq	%r13, %rdx
	movq	%r9, 16(%rsp)
	movq	%r10, 8(%rsp)
	call	memcpy@PLT
	movq	16(%rsp), %r9
	movq	8(%rsp), %r10
	jmp	.L298
	.p2align 4,,10
	.p2align 3
.L295:
	movq	%r9, %rsi
	movq	%r12, %rdx
	movq	%rax, %rdi
	movq	%r8, 24(%rsp)
	movq	%rcx, 16(%rsp)
	movq	%r9, 8(%rsp)
	call	memcpy@PLT
	movq	24(%rsp), %r8
	movq	16(%rsp), %rcx
	movq	%rax, %r10
	movq	8(%rsp), %r9
	jmp	.L294
	.p2align 4,,10
	.p2align 3
.L316:
	movzbl	(%rcx), %eax
	testq	%r13, %r13
	movb	%al, (%rdi)
	je	.L298
	jmp	.L317
.L315:
	leaq	.LC21(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
	.cfi_endproc
.LFE18953:
	.size	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm, .-_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC23:
	.string	"0.0 (test)"
.LC26:
	.string	"KOK Animation Viewer"
.LC27:
	.string	"./Shaders/cubeFragment.fs"
.LC28:
	.string	"./Shaders/cubeVertex.vs"
.LC29:
	.string	"./Shaders/quad.fs"
.LC30:
	.string	"Shader Tester"
.LC34:
	.string	"MOUSE POSITION:"
.LC37:
	.string	"Gloss"
.LC38:
	.string	"MySlider"
.LC39:
	.string	"./Shaders/particleShader.fs"
.LC40:
	.string	"./Shaders/particleShader.vs"
.LC41:
	.string	"./Textures/CubeMaps/Field/"
.LC42:
	.string	"spider0"
.LC46:
	.string	"Fonts/DejaVuSans.ttf"
.LC49:
	.string	"stoi"
.LC50:
	.string	"Current MS per frame: "
.LC51:
	.string	"basic_string::append"
.LC52:
	.string	"KOK ENGINE\nVERSION: "
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB16954:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA16954
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-32, %rsp
	leaq	.LC23(%rip), %rsi
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x58,0x6
	.cfi_escape 0x10,0xf,0x2,0x76,0x78
	.cfi_escape 0x10,0xe,0x2,0x76,0x70
	.cfi_escape 0x10,0xd,0x2,0x76,0x68
	.cfi_escape 0x10,0xc,0x2,0x76,0x60
	pushq	%rbx
	subq	$1696, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x50
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	leaq	-1072(%rbp), %rax
	movq	%rax, %rdi
	movq	%rax, -1736(%rbp)
.LEHB13:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.constprop.75
.LEHE13:
	movabsq	$4539628425463201792, %rax
	movl	$100, %edi
	movl	$1084227584, -1448(%rbp)
	movq	%rax, -1456(%rbp)
	movq	$1000593162, -1408(%rbp)
	movl	$-1138501878, -1400(%rbp)
.LEHB14:
	call	_Znwm@PLT
.LEHE14:
	vmovq	-1408(%rbp), %xmm2
	movq	%rax, %rdi
	vmovss	-1400(%rbp), %xmm3
	movq	%rax, -1536(%rbp)
	vmovq	-1456(%rbp), %xmm0
	vmovss	-1448(%rbp), %xmm1
.LEHB15:
	call	_ZN12KOK_Graphics10KOK_CameraC1EN3glm3vecILi3EfLNS1_9qualifierE0EEES4_@PLT
.LEHE15:
	movl	$40, %edi
.LEHB16:
	call	_Znwm@PLT
.LEHE16:
	movq	%rax, %rbx
	leaq	16+_ZTV9KOK_Actor(%rip), %rax
	movl	$19541, %edx
	leaq	24(%rbx), %r13
	leaq	8(%rbx), %rdi
	movl	$1095124292, 24(%rbx)
	movq	%rax, (%rbx)
	movl	$25, %r8d
	xorl	%ecx, %ecx
	movq	%r13, 8(%rbx)
	movl	$7, %esi
	movw	%dx, 4(%r13)
	movb	$84, 6(%r13)
	xorl	%edx, %edx
	movq	$7, 16(%rbx)
	movb	$0, 31(%rbx)
.LEHB17:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.LEHE17:
	movq	8(%rbx), %rdx
	leaq	-128(%rbp), %rdi
	leaq	-176(%rbp), %rsi
	vmovdqa	.LC57(%rip), %xmm0
	leaq	7(%rdx), %rax
	vmovups	%xmm0, 7(%rdx)
	movabsq	$2314885530818453536, %rdx
	movb	$32, 24(%rax)
	movq	%rdx, 16(%rax)
	movq	8(%rbx), %rax
	movl	$64, %edx
	vmovdqa	.LC58(%rip), %xmm0
	movq	$32, 16(%rbx)
	movb	$0, 32(%rax)
	leaq	16+_ZTV5MyGUI(%rip), %rax
	movl	$1953722985, -144(%rbp)
	vmovaps	%xmm0, -176(%rbp)
	movq	%rax, (%rbx)
	movl	$46, %eax
	vmovdqa	.LC59(%rip), %xmm0
	movw	%ax, -140(%rbp)
	vmovaps	%xmm0, -160(%rbp)
	call	strncpy@PLT
	leaq	-1408(%rbp), %rax
	leaq	8(%rax), %rdi
	movl	$1024, -1408(%rbp)
	movq	$0, -1400(%rbp)
	movq	$0, -1392(%rbp)
	movq	$0, -1384(%rbp)
	movq	$0, -1376(%rbp)
	movq	$0, -1368(%rbp)
	movq	$0, -1360(%rbp)
	movq	$0, -1352(%rbp)
	movq	$0, -1344(%rbp)
	movq	$0, -1336(%rbp)
	movq	$0, -1328(%rbp)
	movq	%rax, -1600(%rbp)
.LEHB18:
	call	_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EE17_M_initialize_mapEm.constprop.73
.LEHE18:
	movq	-1600(%rbp), %rbx
	movq	$0, -1320(%rbp)
	movq	$0, -1312(%rbp)
	movq	$0, -1304(%rbp)
	movq	$0, -1296(%rbp)
	movq	$0, -1288(%rbp)
	leaq	88(%rbx), %rdi
	movq	$0, -1280(%rbp)
	movq	$0, -1272(%rbp)
	movq	$0, -1264(%rbp)
	movq	$0, -1256(%rbp)
	movq	$0, -1248(%rbp)
.LEHB19:
	call	_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EE17_M_initialize_mapEm.constprop.73
.LEHE19:
	leaq	168(%rbx), %rdi
	movq	$0, -1240(%rbp)
	movq	$0, -1232(%rbp)
	movq	$0, -1224(%rbp)
	movq	$0, -1216(%rbp)
	movq	$0, -1208(%rbp)
	movq	$0, -1200(%rbp)
	movq	$0, -1192(%rbp)
	movq	$0, -1184(%rbp)
	movq	$0, -1176(%rbp)
	movq	$0, -1168(%rbp)
.LEHB20:
	call	_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EE17_M_initialize_mapEm.constprop.73
.LEHE20:
	leaq	248(%rbx), %rdi
	movq	$0, -1160(%rbp)
	movq	$0, -1152(%rbp)
	movq	$0, -1144(%rbp)
	movq	$0, -1136(%rbp)
	movq	$0, -1128(%rbp)
	movq	$0, -1120(%rbp)
	movq	$0, -1112(%rbp)
	movq	$0, -1104(%rbp)
	movq	$0, -1096(%rbp)
	movq	$0, -1088(%rbp)
.LEHB21:
	call	_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EE17_M_initialize_mapEm.constprop.73
.LEHE21:
	vmovaps	.LC24(%rip), %ymm0
	leaq	-1456(%rbp), %rbx
	leaq	-1472(%rbp), %rdi
	leaq	.LC26(%rip), %rdx
	xorl	%ecx, %ecx
	movl	$720, -1456(%rbp)
	vmovaps	%ymm0, -912(%rbp)
	movq	%rbx, %r14
	movq	%rbx, %rsi
	vmovaps	.LC25(%rip), %ymm0
	movl	$1280, -1472(%rbp)
	movq	%rbx, -1528(%rbp)
	vmovaps	%ymm0, -880(%rbp)
	movq	%rdi, -1616(%rbp)
	vzeroupper
.LEHB22:
	call	_ZN12KOK_Graphics10InitWindowERKiS1_PKcb@PLT
	movq	%rax, %r15
	movq	%rax, -1504(%rbp)
	call	_ZN12KOK_Graphics6InitGLEv@PLT
	leaq	.LC27(%rip), %rsi
	leaq	.LC28(%rip), %rdi
	call	_Z11LoadShadersPKcS0_@PLT
	leaq	.LC29(%rip), %rsi
	leaq	.LC4(%rip), %rdi
	call	_Z11LoadShadersPKcS0_@PLT
	movq	%rbx, %rdi
	movl	%eax, -1560(%rbp)
	call	_ZN17KOK_WindowManagerC1Ev@PLT
.LEHE22:
	movl	$720, %ecx
	movl	$1280, %edx
	movq	%r15, %rsi
	movq	%rbx, %rdi
.LEHB23:
	call	_ZN17KOK_WindowManager7InitGUIEP10GLFWwindowii@PLT
	call	_Z18InitWindowTexturesv
	leaq	-592(%rbp), %rbx
	leaq	.LC30(%rip), %rsi
	movq	%rbx, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.constprop.75
.LEHE23:
	vmovss	.LC31(%rip), %xmm3
	movq	%rbx, %rdx
	vmovaps	%xmm3, %xmm1
	movl	$1, %esi
	vmovss	.LC32(%rip), %xmm2
	movq	%r14, %rdi
	vmovss	.LC33(%rip), %xmm0
.LEHB24:
	call	_ZN17KOK_WindowManager12CreateWindowEffffbNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE@PLT
.LEHE24:
	movq	-592(%rbp), %rdi
	leaq	16(%rbx), %rax
	cmpq	%rax, %rdi
	je	.L327
	call	_ZdlPv@PLT
.L327:
	leaq	.LC34(%rip), %rsi
	movq	%rbx, %rdi
.LEHB25:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.constprop.75
.LEHE25:
	leaq	-848(%rbp), %rax
	leaq	.LC30(%rip), %rsi
	movq	%rax, %rdi
	movq	%rax, %r15
	movq	%rax, -1568(%rbp)
.LEHB26:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.constprop.75
.LEHE26:
	vxorps	%xmm1, %xmm1, %xmm1
	movq	-1528(%rbp), %rdi
	movl	$1, %r8d
	vmovss	.LC36(%rip), %xmm0
	movl	$1, %ecx
	movq	%rbx, %rdx
	movq	%r15, %rsi
.LEHB27:
	call	_ZN17KOK_WindowManager9AddWidgetENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_10WidgetTypeffb@PLT
.LEHE27:
	movq	-848(%rbp), %rdi
	movq	%rax, -1664(%rbp)
	movq	%r15, %rax
	addq	$16, %rax
	cmpq	%rax, %rdi
	je	.L328
	call	_ZdlPv@PLT
.L328:
	movq	-592(%rbp), %rdi
	leaq	16(%rbx), %rax
	cmpq	%rax, %rdi
	je	.L329
	call	_ZdlPv@PLT
.L329:
	leaq	.LC37(%rip), %rsi
	movq	%rbx, %rdi
.LEHB28:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.constprop.75
.LEHE28:
	movq	-1568(%rbp), %r14
	leaq	.LC30(%rip), %rsi
	movq	%r14, %rdi
.LEHB29:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.constprop.75
.LEHE29:
	vxorps	%xmm1, %xmm1, %xmm1
	movq	-1528(%rbp), %rdi
	vxorps	%xmm0, %xmm0, %xmm0
	movl	$1, %r8d
	movl	$1, %ecx
	movq	%rbx, %rdx
	movq	%r14, %rsi
.LEHB30:
	call	_ZN17KOK_WindowManager9AddWidgetENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_10WidgetTypeffb@PLT
.LEHE30:
	movq	-848(%rbp), %rdi
	movq	%r14, %rax
	addq	$16, %rax
	cmpq	%rax, %rdi
	je	.L330
	call	_ZdlPv@PLT
.L330:
	movq	-592(%rbp), %rdi
	leaq	16(%rbx), %rax
	cmpq	%rax, %rdi
	je	.L331
	call	_ZdlPv@PLT
.L331:
	leaq	.LC38(%rip), %rsi
	movq	%rbx, %rdi
.LEHB31:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.constprop.75
.LEHE31:
	movq	-1568(%rbp), %r14
	leaq	.LC30(%rip), %rsi
	movq	%r14, %rdi
.LEHB32:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.constprop.75
.LEHE32:
	vxorps	%xmm1, %xmm1, %xmm1
	movq	-1528(%rbp), %rdi
	movl	$1, %r8d
	vmovss	.LC18(%rip), %xmm0
	movl	$3, %ecx
	movq	%rbx, %rdx
	movq	%r14, %rsi
.LEHB33:
	call	_ZN17KOK_WindowManager9AddWidgetENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_10WidgetTypeffb@PLT
.LEHE33:
	movq	-848(%rbp), %rdi
	movq	%rax, -1672(%rbp)
	movq	%r14, %rax
	addq	$16, %rax
	cmpq	%rax, %rdi
	je	.L332
	call	_ZdlPv@PLT
.L332:
	movq	-592(%rbp), %rdi
	leaq	16(%rbx), %rax
	cmpq	%rax, %rdi
	je	.L333
	call	_ZdlPv@PLT
.L333:
	movl	$56, %edi
.LEHB34:
	call	_Znwm@PLT
.LEHE34:
	movl	$720, %edx
	movl	$1280, %esi
	movq	%rax, %rdi
	movq	%rax, -1624(%rbp)
.LEHB35:
	call	_ZN12KOK_Graphics16LightProcessDataC1Eii
.LEHE35:
	movl	$8, %edi
.LEHB36:
	call	_Znwm@PLT
.LEHE36:
	movl	$720, %edx
	movl	$1280, %esi
	movq	%rax, %rdi
	movq	%rax, %r12
.LEHB37:
	call	_ZN12KOK_Graphics15TextProcessDataC1Eii
.LEHE37:
	movl	$4, %edi
.LEHB38:
	call	_Znwm@PLT
.LEHE38:
	leaq	.LC39(%rip), %rsi
	leaq	.LC40(%rip), %rdi
	movq	%rax, %r15
	movq	%rax, -1632(%rbp)
.LEHB39:
	call	_Z11LoadShadersPKcS0_@PLT
.LEHE39:
	movl	%eax, (%r15)
	movl	$44, %edi
.LEHB40:
	call	_Znwm@PLT
.LEHE40:
	movl	$720, %edx
	movl	$1280, %esi
	movq	%rax, %rdi
	movq	%rax, -1544(%rbp)
.LEHB41:
	call	_ZN12KOK_Graphics20DeferredLightingDataC1Eii
.LEHE41:
	movl	$16, %edi
.LEHB42:
	call	_Znwm@PLT
.LEHE42:
	movl	$720, %edx
	movl	$1280, %esi
	movq	%rax, %rdi
	movq	%rax, -1640(%rbp)
.LEHB43:
	call	_ZN12KOK_Graphics8SSAODataC1Eii
.LEHE43:
	movl	$216, %edi
.LEHB44:
	call	_Znwm@PLT
.LEHE44:
	movl	$720, %edx
	movl	$1280, %esi
	movq	%rax, %rdi
	movq	%rax, -1648(%rbp)
.LEHB45:
	call	_ZN12KOK_Graphics10ShadowDataC1Eii
.LEHE45:
.LEHB46:
	call	glfwGetTime@PLT
	vxorps	%xmm2, %xmm2, %xmm2
	leaq	.LC41(%rip), %rsi
	movq	%rbx, %rdi
	vcvtsd2ss	%xmm0, %xmm2, %xmm2
	vmovss	%xmm2, -1676(%rbp)
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.constprop.75
.LEHE46:
	movl	$600, %edi
.LEHB47:
	call	_Znwm@PLT
.LEHE47:
	movq	%rbx, %rsi
	movq	%rax, %rdi
	movq	%rax, -1656(%rbp)
.LEHB48:
	call	_ZN10KOK_SkyBoxC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE@PLT
.LEHE48:
	movq	-592(%rbp), %rdi
	leaq	16(%rbx), %rax
	cmpq	%rax, %rdi
	je	.L334
	call	_ZdlPv@PLT
.L334:
	movl	$720, %esi
	movl	$1280, %edi
.LEHB49:
	call	_ZN10KOK_Imager8BlankPNGEjj@PLT
	movl	$720, %esi
	movl	$1280, %edi
	call	_ZN10KOK_Imager8BlankPNGEjj@PLT
	movq	-1568(%rbp), %rdi
	call	_ZN9KOK_Model12GenerateQuadEv@PLT
.LEHE49:
	leaq	.LC42(%rip), %rsi
	movq	%rbx, %rdi
.LEHB50:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2EPKcRKS3_.constprop.75
.LEHE50:
	movl	$152, %edi
.LEHB51:
	call	_Znwm@PLT
.LEHE51:
	movq	%rbx, %rsi
	movq	%rax, %rdi
	movq	%rax, -1608(%rbp)
.LEHB52:
	call	_ZN9KOK_ModelC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE@PLT
.LEHE52:
	movq	-592(%rbp), %rdi
	leaq	16(%rbx), %rax
	cmpq	%rax, %rdi
	je	.L335
	call	_ZdlPv@PLT
.L335:
	movq	-1616(%rbp), %r15
	movq	-1608(%rbp), %r14
	movabsq	$-4698155129335132979, %rax
	movq	%rax, -1472(%rbp)
	movl	$-1082130432, -1464(%rbp)
	movq	%r15, %rsi
	movq	%r14, %rdi
.LEHB53:
	call	_ZN9KOK_Model11SetPositionERKN3glm3vecILi3EfLNS0_9qualifierE0EEE@PLT
	movabsq	$4568451461350319718, %rax
	movq	%r15, %rsi
	movq	%r14, %rdi
	movq	%rax, -1472(%rbp)
	movl	$1063675494, -1464(%rbp)
	call	_ZN9KOK_Model8SetScaleERKN3glm3vecILi3EfLNS0_9qualifierE0EEE@PLT
	leaq	-1480(%rbp), %r12
	leaq	-1488(%rbp), %rsi
	movq	%r15, %rcx
	movq	%r14, %rdi
	movl	$0xbf000000, -1472(%rbp)
	movl	$0xbe19999a, -1480(%rbp)
	movq	%r12, %rdx
	movl	$0x3dcccccd, -1488(%rbp)
	movq	%r12, -1696(%rbp)
	movq	%rsi, -1688(%rbp)
	call	_ZN9KOK_Model19SetEulerOrientationERKfS1_S1_@PLT
	movl	$1, %esi
	movq	%r14, %rdi
	call	_ZN9KOK_Model9SetStaticEb@PLT
	movl	$168, %edi
	movl	$1280, -1480(%rbp)
	movl	$720, -1472(%rbp)
	call	_Znwm@PLT
.LEHE53:
	leaq	.LC46(%rip), %rsi
	movq	%r15, %rcx
	movq	%r12, %rdx
	movq	%rax, %rdi
	movq	%rax, -1520(%rbp)
.LEHB54:
	call	_ZN15KOK_TextManagerC1EPKcRKiS3_@PLT
.LEHE54:
.LEHB55:
	call	glfwGetTime@PLT
.LEHE55:
	leaq	-912(%rbp), %rax
	vxorpd	%xmm3, %xmm3, %xmm3
	vmovsd	%xmm0, -1584(%rbp)
	movl	$0, -1556(%rbp)
	movq	16+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %r12
	movq	%rax, -1704(%rbp)
	leaq	-1008(%rbp), %rax
	vmovsd	%xmm3, -1592(%rbp)
	movq	%rax, -1512(%rbp)
	leaq	-976(%rbp), %rax
	vmovq	.LC61(%rip), %xmm3
	movq	%rax, -1576(%rbp)
	leaq	-944(%rbp), %rax
	movq	%rax, -1496(%rbp)
	leaq	-1040(%rbp), %rax
	movq	%rax, -1552(%rbp)
	leaq	16+_ZTVNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEEE(%rip), %rax
	vpinsrq	$1, %rax, %xmm3, %xmm2
	vmovaps	%xmm2, -1728(%rbp)
	jmp	.L413
	.p2align 4,,10
	.p2align 3
.L573:
	movq	-1496(%rbp), %rcx
	testq	%r14, %r14
	leaq	16(%rcx), %rdx
	movq	%rdx, -944(%rbp)
	je	.L565
	subq	%r14, %rax
	cmpq	$15, %rax
	movq	%rax, %r13
	ja	.L566
	cmpq	$1, %rax
	je	.L567
	testq	%rax, %rax
	jne	.L568
.L362:
	movq	%r13, -936(%rbp)
	movb	$0, (%rdx,%r13)
	movq	-1496(%rbp), %rdx
	movq	-944(%rbp), %rsi
	movq	-1008(%rbp), %rdi
	addq	$16, %rdx
	cmpq	%rdx, %rsi
	movq	%rdi, %rax
	je	.L569
	movq	-1512(%rbp), %rdi
	movq	-936(%rbp), %rcx
	movq	-928(%rbp), %rdx
	addq	$16, %rdi
	cmpq	%rdi, %rax
	je	.L570
	testq	%rax, %rax
	movq	-992(%rbp), %rdi
	movq	%rsi, -1008(%rbp)
	movq	%rcx, -1000(%rbp)
	movq	%rdx, -992(%rbp)
	je	.L368
	movq	%rax, -944(%rbp)
	movq	%rdi, -928(%rbp)
.L366:
	movq	$0, -936(%rbp)
	movb	$0, (%rax)
	movq	-1496(%rbp), %rax
	movq	-944(%rbp), %rdi
	addq	$16, %rax
	cmpq	%rax, %rdi
	je	.L370
.L546:
	call	_ZdlPv@PLT
.L370:
	movq	-1512(%rbp), %rdi
	leaq	.LC50(%rip), %rcx
	movl	$22, %r8d
	xorl	%edx, %edx
	xorl	%esi, %esi
.LEHB56:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm
.LEHE56:
	movq	-1552(%rbp), %rcx
	leaq	16(%rcx), %rdx
	movq	%rdx, -1040(%rbp)
	movq	(%rax), %rcx
	leaq	16(%rax), %rdx
	cmpq	%rdx, %rcx
	je	.L571
	movq	%rcx, -1040(%rbp)
	movq	16(%rax), %rcx
	movq	%rcx, -1024(%rbp)
.L393:
	movq	8(%rax), %rcx
	movb	$0, 16(%rax)
	movq	%rcx, -1032(%rbp)
	movq	%rdx, (%rax)
	movq	$0, 8(%rax)
	movq	-1512(%rbp), %rax
	movq	-1008(%rbp), %rdi
	addq	$16, %rax
	cmpq	%rax, %rdi
	je	.L394
	call	_ZdlPv@PLT
.L394:
	movq	-1496(%rbp), %rax
	movq	$0, -936(%rbp)
	movb	$0, -928(%rbp)
	addq	$16, %rax
	movq	%rax, -944(%rbp)
	movq	-1064(%rbp), %rax
	leaq	20(%rax), %r13
	cmpq	$15, %r13
	ja	.L395
	movl	$20, %r14d
	xorl	%r15d, %r15d
.L396:
	movq	-1496(%rbp), %rdi
	leaq	.LC52(%rip), %rcx
	movl	$20, %r8d
	xorl	%edx, %edx
	movq	%r15, %rsi
.LEHB57:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.LEHE57:
.L401:
	movq	-944(%rbp), %rax
	movq	%r14, -936(%rbp)
	movb	$0, (%rax,%r14)
	movq	-1496(%rbp), %rax
	movq	-944(%rbp), %rdi
	movq	-1064(%rbp), %r8
	movq	-936(%rbp), %rsi
	movq	-1072(%rbp), %rcx
	leaq	16(%rax), %rdx
	movl	$15, %eax
	cmpq	%rdx, %rdi
	leaq	(%r8,%rsi), %r13
	je	.L402
	movq	-928(%rbp), %rax
.L402:
	cmpq	%rax, %r13
	ja	.L403
	testq	%r8, %r8
	je	.L404
	addq	%rsi, %rdi
	cmpq	$1, %r8
	jne	.L405
	movzbl	(%rcx), %eax
	movb	%al, (%rdi)
	movq	-944(%rbp), %rdi
	.p2align 4,,10
	.p2align 3
.L404:
	movq	%r13, -936(%rbp)
	movq	-1496(%rbp), %rsi
	movb	$0, (%rdi,%r13)
	movq	-1520(%rbp), %rdi
	vmovq	_ZL13K_COLOR_WHITE(%rip), %xmm3
	vmovss	8+_ZL13K_COLOR_WHITE(%rip), %xmm4
	vmovss	.LC53(%rip), %xmm2
	vmovss	.LC54(%rip), %xmm1
	vmovss	.LC55(%rip), %xmm0
.LEHB58:
	call	_ZN15KOK_TextManager8DrawTextERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEfffN3glm3vecILi3EfLNS8_9qualifierE0EEE@PLT
.LEHE58:
	movq	-1496(%rbp), %rax
	movq	-944(%rbp), %rdi
	addq	$16, %rax
	cmpq	%rax, %rdi
	je	.L410
	call	_ZdlPv@PLT
.L410:
	movq	-1552(%rbp), %r14
	movq	-1520(%rbp), %rdi
	vmovq	_ZL13K_COLOR_WHITE(%rip), %xmm3
	vmovss	8+_ZL13K_COLOR_WHITE(%rip), %xmm4
	vmovss	.LC53(%rip), %xmm2
	movq	%r14, %rsi
	vmovss	.LC56(%rip), %xmm1
	vmovss	.LC55(%rip), %xmm0
.LEHB59:
	call	_ZN15KOK_TextManager8DrawTextERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEfffN3glm3vecILi3EfLNS8_9qualifierE0EEE@PLT
	movq	-1528(%rbp), %rdi
	call	_ZN17KOK_WindowManager7DrawGUIEv@PLT
	movq	-1504(%rbp), %rdi
	call	glfwSwapBuffers@PLT
.LEHE59:
	movq	-1040(%rbp), %rdi
	movq	%r14, %rax
	addq	$16, %rax
	cmpq	%rax, %rdi
	je	.L411
	call	_ZdlPv@PLT
.L411:
	leaq	24+_ZTVNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	-496(%rbp), %rdi
	vmovdqa	-1728(%rbp), %xmm4
	movq	%rax, -592(%rbp)
	addq	$80, %rax
	movq	%rax, -464(%rbp)
	leaq	112(%rbx), %rax
	vmovaps	%xmm4, -576(%rbp)
	cmpq	%rax, %rdi
	je	.L412
	call	_ZdlPv@PLT
.L412:
	leaq	16+_ZTVSt15basic_streambufIcSt11char_traitsIcEE(%rip), %rax
	leaq	80(%rbx), %rdi
	movq	%rax, -568(%rbp)
	call	_ZNSt6localeD1Ev@PLT
	movq	8+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	48+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rdx
	leaq	128(%rbx), %rdi
	movq	40+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	-24(%rax), %rax
	movq	%rdx, -592(%rbp,%rax)
	movq	32+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rdx
	movq	%rax, -576(%rbp)
	movq	-24(%rax), %rax
	movq	%rcx, -576(%rbp,%rax)
	movq	-24(%r12), %rax
	movq	%r12, -592(%rbp)
	movq	%rdx, -592(%rbp,%rax)
	leaq	16+_ZTVSt9basic_iosIcSt11char_traitsIcEE(%rip), %rax
	movq	$0, -584(%rbp)
	movq	%rax, -464(%rbp)
	call	_ZNSt8ios_baseD2Ev@PLT
.L413:
	movq	-1504(%rbp), %rdi
.LEHB60:
	call	glfwWindowShouldClose@PLT
	testl	%eax, %eax
	jne	.L336
	call	glfwGetTime@PLT
	vmovsd	-1584(%rbp), %xmm6
	addl	$1, -1556(%rbp)
	vsubsd	%xmm6, %xmm0, %xmm0
	vcomisd	.LC47(%rip), %xmm0
	jb	.L337
	vxorpd	%xmm0, %xmm0, %xmm0
	vmovsd	.LC48(%rip), %xmm2
	vcvtsi2sd	-1556(%rbp), %xmm0, %xmm0
	vdivsd	%xmm0, %xmm2, %xmm7
	movl	$0, -1556(%rbp)
	vmovsd	%xmm7, -1592(%rbp)
	vmovsd	.LC47(%rip), %xmm7
	vaddsd	%xmm6, %xmm7, %xmm3
	vmovsd	%xmm3, -1584(%rbp)
.L337:
	call	glfwGetTime@PLT
	vxorpd	%xmm1, %xmm1, %xmm1
	movq	-1696(%rbp), %rdx
	movq	-1688(%rbp), %rsi
	movq	-1504(%rbp), %rdi
	vcvtss2sd	-1676(%rbp), %xmm1, %xmm1
	vsubsd	%xmm1, %xmm0, %xmm0
	vmovsd	%xmm0, runTime(%rip)
	call	glfwGetCursorPos@PLT
	movq	-1664(%rbp), %r14
	movl	$2, %r9d
	xorl	%edx, %edx
	movq	-1600(%rbp), %r15
	movq	-1672(%rbp), %rcx
	movl	$5, %esi
	movq	%r14, %r8
	movq	%r15, %rdi
	call	_ZN14KOK_PostOffice12QueueMessageEyiP9KOK_ActorS1_11MessageFlag@PLT
	call	glfwPollEvents@PLT
	xorl	%esi, %esi
	movq	%r15, %rdi
	call	_ZN14KOK_PostOffice6UpdateE11DeliverFlag@PLT
	movq	-1528(%rbp), %rdi
	call	_ZN17KOK_WindowManager9UpdateGUIEv@PLT
	movq	-1544(%rbp), %r15
	movl	$36160, %edi
	movl	4(%r15), %esi
	call	*__glewBindFramebuffer(%rip)
	movl	$16640, %edi
	call	glClear@PLT
	movl	$720, %ecx
	movl	$1280, %edx
	xorl	%esi, %esi
	xorl	%edi, %edi
	call	glViewport@PLT
	movl	$3553, %edi
	call	glEnable@PLT
	movl	$3042, %edi
	call	glDisable@PLT
	movl	$2929, %edi
	call	glEnable@PLT
	movl	$513, %edi
	call	glDepthFunc@PLT
	movl	$2884, %edi
	call	glEnable@PLT
	movl	$1029, %edi
	call	glCullFace@PLT
	movl	$2305, %edi
	call	glCullFace@PLT
	movl	$6914, %esi
	movl	$1028, %edi
	call	glPolygonMode@PLT
	movl	(%r15), %edi
	call	*__glewUseProgram(%rip)
	movq	-1536(%rbp), %rax
	movq	-1704(%rbp), %rdx
	movq	%r15, %rsi
	movq	-1608(%rbp), %rdi
	leaq	36(%rax), %rcx
	call	_ZN9KOK_Model4DrawERKjRKN3glm3matILi4ELi4EfLNS2_9qualifierE0EEES7_@PLT
	movq	8(%r14), %r14
	call	__errno_location@PLT
	movq	-1616(%rbp), %rsi
	movl	(%rax), %r15d
	movl	$10, %edx
	movl	$0, (%rax)
	movq	%r14, %rdi
	movq	%rax, %r13
	call	strtol@PLT
	cmpq	-1472(%rbp), %r14
	je	.L572
	movl	0(%r13), %edx
	cmpl	$34, %edx
	je	.L340
	movl	$2147483648, %ecx
	addq	%rcx, %rax
	addq	$2147483647, %rcx
	cmpq	%rcx, %rax
	ja	.L340
	testl	%edx, %edx
	jne	.L342
	movl	%r15d, 0(%r13)
.L342:
	movl	-1560(%rbp), %eax
	subq	$8, %rsp
	movq	-1656(%rbp), %r9
	movq	-1648(%rbp), %r8
	movq	-1640(%rbp), %rcx
	movq	-1544(%rbp), %rdx
	movq	-1624(%rbp), %rsi
	movq	-1568(%rbp), %rdi
	pushq	%rax
	pushq	-1520(%rbp)
	pushq	-1536(%rbp)
	pushq	-856(%rbp)
	pushq	-864(%rbp)
	pushq	-872(%rbp)
	pushq	-880(%rbp)
	pushq	-888(%rbp)
	pushq	-896(%rbp)
	pushq	-904(%rbp)
	pushq	-912(%rbp)
	.cfi_escape 0x2e,0x60
	call	_ZN12KOK_Graphics14DrawScreenQuadEP8KOK_MeshPNS_16LightProcessDataEPNS_20DeferredLightingDataEPNS_8SSAODataEPNS_10ShadowDataEP10KOK_SkyBoxN3glm3matILi4ELi4EfLNSC_9qualifierE0EEEPNS_10KOK_CameraEP15KOK_TextManagerj@PLT
	movq	-1632(%rbp), %rax
	addq	$96, %rsp
	movl	(%rax), %edi
	.cfi_escape 0x2e,0
	call	*__glewUseProgram(%rip)
	movl	$2929, %edi
	call	glEnable@PLT
	xorl	%edi, %edi
	call	glDepthMask@PLT
	movl	$3042, %edi
	call	glEnable@PLT
	movl	$771, %esi
	movl	$770, %edi
	call	glBlendFunc@PLT
	movl	$515, %edi
	call	glDepthFunc@PLT
	movq	-1504(%rbp), %rdi
	movl	$256, %esi
	call	glfwGetKey@PLT
	cmpl	$1, %eax
	je	.L347
.L349:
	movl	$519, %edi
	call	glDepthFunc@PLT
	movl	$1, %edi
	call	glDepthMask@PLT
	movl	$2884, %edi
	call	glDisable@PLT
.LEHE60:
	leaq	128(%rbx), %rdi
	call	_ZNSt8ios_baseC2Ev@PLT
	vpxor	%xmm5, %xmm5, %xmm5
	leaq	16+_ZTVSt9basic_iosIcSt11char_traitsIcEE(%rip), %rax
	movb	$0, -240(%rbp)
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	xorl	%esi, %esi
	movq	%rax, -464(%rbp)
	movq	$0, -248(%rbp)
	vmovups	%xmm5, -232(%rbp)
	movb	$0, -239(%rbp)
	movq	%r12, -592(%rbp)
	vmovups	%xmm5, -216(%rbp)
	movq	-24(%r12), %rax
	movq	%rcx, -592(%rbp,%rax)
	movq	$0, -584(%rbp)
	movq	-24(%r12), %rdi
	addq	%rbx, %rdi
.LEHB61:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E@PLT
.LEHE61:
	movq	32+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	xorl	%esi, %esi
	movq	%rax, -576(%rbp)
	movq	-24(%rax), %rax
	leaq	16(%rbx,%rax), %rdi
	movq	40+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	%rax, (%rdi)
.LEHB62:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E@PLT
.LEHE62:
	movq	8+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	48+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	leaq	80(%rbx), %rdi
	vpxor	%xmm0, %xmm0, %xmm0
	movq	-24(%rax), %rax
	movq	%rcx, -592(%rbp,%rax)
	leaq	24+_ZTVNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	vmovaps	%xmm0, -560(%rbp)
	movq	%rax, -592(%rbp)
	addq	$80, %rax
	vmovaps	%xmm0, -544(%rbp)
	vmovaps	%xmm0, -528(%rbp)
	movq	%rax, -464(%rbp)
	subq	$40, %rax
	movq	%rax, -576(%rbp)
	leaq	16+_ZTVSt15basic_streambufIcSt11char_traitsIcEE(%rip), %rax
	movq	%rax, -568(%rbp)
	call	_ZNSt6localeC1Ev@PLT
	leaq	16+_ZTVNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEEE(%rip), %rax
	leaq	24(%rbx), %rsi
	leaq	128(%rbx), %rdi
	movl	$24, -504(%rbp)
	movq	$0, -488(%rbp)
	movq	%rax, -568(%rbp)
	leaq	112(%rbx), %rax
	movb	$0, -480(%rbp)
	movq	%rax, -496(%rbp)
.LEHB63:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E@PLT
.LEHE63:
	leaq	16(%rbx), %rdi
	vmovsd	-1592(%rbp), %xmm0
.LEHB64:
	call	_ZNSo9_M_insertIdEERSoT_@PLT
.LEHE64:
	movq	-1512(%rbp), %rax
	movq	$0, -1000(%rbp)
	movb	$0, -992(%rbp)
	leaq	16(%rax), %rdi
	movq	-528(%rbp), %rax
	movq	%rdi, -1008(%rbp)
	testq	%rax, %rax
	je	.L355
	movq	-544(%rbp), %r13
	movq	-536(%rbp), %r14
	cmpq	%r13, %rax
	ja	.L573
	movq	-1576(%rbp), %rax
	addq	$16, %rax
	testq	%r13, %r13
	movq	%rax, -976(%rbp)
	je	.L371
	testq	%r14, %r14
	je	.L574
.L371:
	subq	%r14, %r13
	cmpq	$15, %r13
	ja	.L575
	cmpq	$1, %r13
	je	.L576
	movq	-1576(%rbp), %rax
	addq	$16, %rax
	testq	%r13, %r13
	jne	.L374
.L376:
	movq	-1576(%rbp), %rcx
	movq	%r13, -968(%rbp)
	movb	$0, (%rax,%r13)
	movq	-976(%rbp), %rsi
	movq	-1008(%rbp), %rdi
	leaq	16(%rcx), %rdx
	cmpq	%rdx, %rsi
	movq	%rdi, %rax
	je	.L577
	movq	-1512(%rbp), %rdi
	movq	-960(%rbp), %rdx
	movq	-968(%rbp), %rcx
	addq	$16, %rdi
	cmpq	%rdi, %rax
	je	.L578
	testq	%rax, %rax
	movq	-992(%rbp), %rdi
	movq	%rsi, -1008(%rbp)
	movq	%rcx, -1000(%rbp)
	movq	%rdx, -992(%rbp)
	je	.L382
	movq	%rax, -976(%rbp)
	movq	%rdi, -960(%rbp)
.L380:
	movq	$0, -968(%rbp)
	movb	$0, (%rax)
	movq	-1576(%rbp), %rax
	movq	-976(%rbp), %rdi
	addq	$16, %rax
	cmpq	%rax, %rdi
	jne	.L546
	jmp	.L370
	.p2align 4,,10
	.p2align 3
.L395:
	testq	%r13, %r13
	js	.L579
	cmpq	$30, %r13
	movl	$30, %eax
	cmovb	%rax, %r13
	leaq	1(%r13), %rdi
.LEHB65:
	call	_Znwm@PLT
.LEHE65:
	movq	-936(%rbp), %r15
	movq	%rax, %rcx
	movq	-944(%rbp), %r14
	leaq	1(%r15), %rdx
	cmpq	$1, %rdx
	je	.L580
	testq	%rdx, %rdx
	jne	.L581
.L398:
	movq	-1496(%rbp), %rax
	addq	$16, %rax
	cmpq	%rax, %r14
	je	.L399
	movq	%r14, %rdi
	movq	%rcx, -1712(%rbp)
	call	_ZdlPv@PLT
	movq	-936(%rbp), %r15
	movq	-1712(%rbp), %rcx
.L399:
	movabsq	$9223372036854775807, %rax
	movq	%rcx, -944(%rbp)
	movq	%r13, -928(%rbp)
	subq	%r15, %rax
	cmpq	$19, %rax
	jbe	.L582
	leaq	20(%r15), %r14
	cmpq	%r13, %r14
	ja	.L396
	vmovdqa	.LC60(%rip), %xmm0
	addq	%rcx, %r15
	movl	$540692047, 16(%r15)
	vmovups	%xmm0, (%r15)
	jmp	.L401
	.p2align 4,,10
	.p2align 3
.L347:
	movq	-1504(%rbp), %rdi
	movl	$1, %esi
.LEHB66:
	call	glfwSetWindowShouldClose@PLT
.LEHE66:
	jmp	.L349
	.p2align 4,,10
	.p2align 3
.L403:
	movq	-1496(%rbp), %rdi
	xorl	%edx, %edx
.LEHB67:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.LEHE67:
	movq	-944(%rbp), %rdi
	jmp	.L404
	.p2align 4,,10
	.p2align 3
.L571:
	vmovdqu	16(%rax), %xmm0
	vmovaps	%xmm0, -1024(%rbp)
	jmp	.L393
	.p2align 4,,10
	.p2align 3
.L336:
.LEHB68:
	call	_ZN12KOK_Graphics6KillGLEv@PLT
.LEHE68:
	movq	-1568(%rbp), %rdi
	call	_ZN8KOK_MeshD1Ev
	movq	-1528(%rbp), %rdi
	call	_ZN17KOK_WindowManagerD1Ev@PLT
	movq	-1600(%rbp), %rdi
	call	_ZN14KOK_PostOfficeD1Ev
	movq	-1736(%rbp), %rax
	movq	-1072(%rbp), %rdi
	addq	$16, %rax
	cmpq	%rax, %rdi
	je	.L414
	call	_ZdlPv@PLT
.L414:
	xorl	%eax, %eax
	movq	-56(%rbp), %rbx
	xorq	%fs:40, %rbx
	jne	.L583
	leaq	-48(%rbp), %rsp
	popq	%rbx
	popq	%r10
	.cfi_remember_state
	.cfi_def_cfa 10, 0
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.p2align 4,,10
	.p2align 3
.L405:
	.cfi_restore_state
	movq	%r8, %rdx
	movq	%rcx, %rsi
	call	memcpy@PLT
	movq	-944(%rbp), %rdi
	jmp	.L404
	.p2align 4,,10
	.p2align 3
.L580:
	movzbl	(%r14), %eax
	movb	%al, (%rcx)
	jmp	.L398
	.p2align 4,,10
	.p2align 3
.L575:
	testq	%r13, %r13
	js	.L584
	leaq	1(%r13), %rdi
.LEHB69:
	call	_Znwm@PLT
	movq	%rax, -976(%rbp)
	movq	%r13, -960(%rbp)
.L374:
	movq	%r13, %rdx
	movq	%r14, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	movq	-976(%rbp), %rax
	jmp	.L376
	.p2align 4,,10
	.p2align 3
.L566:
	testq	%rax, %rax
	js	.L585
	leaq	1(%rax), %rdi
	call	_Znwm@PLT
	movq	%rax, -944(%rbp)
	movq	%r13, -928(%rbp)
.L360:
	movq	%r13, %rdx
	movq	%r14, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	movq	-944(%rbp), %rdx
	jmp	.L362
	.p2align 4,,10
	.p2align 3
.L355:
	movq	-488(%rbp), %r13
	cmpq	$15, %r13
	ja	.L586
	testq	%r13, %r13
	jne	.L587
.L388:
	movq	-1008(%rbp), %rax
	movq	%r13, -1000(%rbp)
	movb	$0, (%rax,%r13)
	jmp	.L370
	.p2align 4,,10
	.p2align 3
.L567:
	movzbl	(%r14), %eax
	movb	%al, -928(%rbp)
	jmp	.L362
	.p2align 4,,10
	.p2align 3
.L576:
	movzbl	(%r14), %eax
	movb	%al, -960(%rbp)
	movq	-1576(%rbp), %rax
	addq	$16, %rax
	jmp	.L376
	.p2align 4,,10
	.p2align 3
.L577:
	movq	-968(%rbp), %rdx
	testq	%rdx, %rdx
	je	.L378
	cmpq	$1, %rdx
	jne	.L379
	movzbl	-960(%rbp), %eax
	movb	%al, (%rdi)
	movq	-1008(%rbp), %rdi
	movq	-968(%rbp), %rdx
.L378:
	movq	%rdx, -1000(%rbp)
	movb	$0, (%rdi,%rdx)
	movq	-976(%rbp), %rax
	jmp	.L380
	.p2align 4,,10
	.p2align 3
.L569:
	movq	-936(%rbp), %rdx
	testq	%rdx, %rdx
	je	.L364
	cmpq	$1, %rdx
	jne	.L365
	movzbl	-928(%rbp), %eax
	movb	%al, (%rdi)
	movq	-1008(%rbp), %rdi
	movq	-936(%rbp), %rdx
.L364:
	movq	%rdx, -1000(%rbp)
	movb	$0, (%rdi,%rdx)
	movq	-944(%rbp), %rax
	jmp	.L366
.L581:
	movq	%r14, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	movq	%rax, %rcx
	jmp	.L398
.L578:
	movq	%rsi, -1008(%rbp)
	movq	%rcx, -1000(%rbp)
	movq	%rdx, -992(%rbp)
.L382:
	movq	-1576(%rbp), %rax
	addq	$16, %rax
	movq	%rax, -976(%rbp)
	jmp	.L380
.L570:
	movq	%rsi, -1008(%rbp)
	movq	%rcx, -1000(%rbp)
	movq	%rdx, -992(%rbp)
.L368:
	movq	-1496(%rbp), %rax
	addq	$16, %rax
	movq	%rax, -944(%rbp)
	jmp	.L366
.L586:
	testq	%r13, %r13
	js	.L588
	cmpq	$30, %r13
	movl	$30, %r14d
	cmovnb	%r13, %r14
	leaq	1(%r14), %rdi
	call	_Znwm@PLT
.LEHE69:
	movq	%rax, %r15
	movq	-1512(%rbp), %rax
	movq	-1008(%rbp), %rdi
	addq	$16, %rax
	cmpq	%rax, %rdi
	je	.L386
	call	_ZdlPv@PLT
.L386:
	movq	-496(%rbp), %rsi
	movq	%r15, -1008(%rbp)
	movq	%r15, %rdi
	movq	%r14, -992(%rbp)
.L387:
	movq	%r13, %rdx
	call	memcpy@PLT
	jmp	.L388
.L365:
	call	memcpy@PLT
	movq	-1008(%rbp), %rdi
	movq	-936(%rbp), %rdx
	jmp	.L364
.L379:
	call	memcpy@PLT
	movq	-1008(%rbp), %rdi
	movq	-968(%rbp), %rdx
	jmp	.L378
.L587:
	cmpq	$1, %r13
	movq	-496(%rbp), %rsi
	jne	.L387
	movzbl	(%rsi), %eax
	movq	-1512(%rbp), %rcx
	movb	%al, 16(%rcx)
	jmp	.L388
.L582:
	leaq	.LC51(%rip), %rdi
.LEHB70:
	call	_ZSt20__throw_length_errorPKc@PLT
.LEHE70:
.L494:
.L555:
	movq	%rax, %r12
	movq	-1496(%rbp), %rax
	movq	-944(%rbp), %rdi
	addq	$16, %rax
	cmpq	%rax, %rdi
	je	.L543
	vzeroupper
	call	_ZdlPv@PLT
.L409:
	movq	-1552(%rbp), %rax
	movq	-1040(%rbp), %rdi
	addq	$16, %rax
	cmpq	%rax, %rdi
	je	.L391
	call	_ZdlPv@PLT
.L391:
	movq	%rbx, %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
.L550:
	movq	%r12, %rbx
.L346:
	movq	-1568(%rbp), %rdi
	call	_ZN8KOK_MeshD1Ev
.L418:
	movq	-1528(%rbp), %rdi
	call	_ZN17KOK_WindowManagerD1Ev@PLT
.L449:
	movq	-1600(%rbp), %rdi
	call	_ZN14KOK_PostOfficeD1Ev
.L322:
	movq	-1736(%rbp), %rax
	movq	-1072(%rbp), %rdi
	addq	$16, %rax
	cmpq	%rax, %rdi
	je	.L450
	call	_ZdlPv@PLT
.L450:
	movq	%rbx, %rdi
.LEHB71:
	call	_Unwind_Resume@PLT
.LEHE71:
.L340:
	leaq	.LC49(%rip), %rdi
.LEHB72:
	call	_ZSt20__throw_out_of_rangePKc@PLT
.L489:
	cmpl	$0, 0(%r13)
	jne	.L549
	movl	%r15d, 0(%r13)
.L549:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L346
.L572:
	leaq	.LC49(%rip), %rdi
	call	_ZSt24__throw_invalid_argumentPKc@PLT
.LEHE72:
.L483:
	movq	%rax, %r12
	vzeroupper
	jmp	.L409
.L484:
	jmp	.L555
.L490:
	movq	%rax, %r13
	vzeroupper
.L352:
	leaq	16+_ZTVSt9basic_iosIcSt11char_traitsIcEE(%rip), %rax
	leaq	128(%rbx), %rdi
	movq	%r13, %rbx
	movq	%rax, -464(%rbp)
	call	_ZNSt8ios_baseD2Ev@PLT
	jmp	.L346
.L574:
	leaq	.LC0(%rip), %rdi
.LEHB73:
	call	_ZSt19__throw_logic_errorPKc@PLT
.L479:
	jmp	.L549
.L476:
	movq	-1656(%rbp), %rdi
	movq	%rax, %r12
	movl	$600, %esi
	vzeroupper
	call	_ZdlPvm@PLT
.L438:
	movq	-592(%rbp), %rdi
	addq	$16, %rbx
	cmpq	%rbx, %rdi
	je	.L439
	call	_ZdlPv@PLT
.L439:
	movq	%r12, %rbx
	jmp	.L418
.L475:
.L560:
	movq	%rax, %r12
.L559:
	vzeroupper
	jmp	.L438
.L474:
	movq	-1648(%rbp), %rdi
	movq	%rax, %rbx
	movl	$216, %esi
	vzeroupper
	call	_ZdlPvm@PLT
	jmp	.L418
.L473:
	movq	-1640(%rbp), %rdi
	movq	%rax, %rbx
	movl	$16, %esi
	vzeroupper
	call	_ZdlPvm@PLT
	jmp	.L418
.L472:
	movq	-1544(%rbp), %rdi
	movq	%rax, %rbx
	movl	$44, %esi
	vzeroupper
	call	_ZdlPvm@PLT
	jmp	.L418
.L471:
	movq	-1632(%rbp), %rdi
	movq	%rax, %rbx
	movl	$4, %esi
	vzeroupper
	call	_ZdlPvm@PLT
	jmp	.L418
.L470:
	movq	%rax, %rbx
	movl	$8, %esi
	movq	%r12, %rdi
	vzeroupper
	call	_ZdlPvm@PLT
	jmp	.L418
.L543:
	vzeroupper
	jmp	.L409
.L477:
	movq	%rax, %r12
	vzeroupper
.L441:
	movq	-592(%rbp), %rdi
	addq	$16, %rbx
	cmpq	%rbx, %rdi
	je	.L550
	call	_ZdlPv@PLT
	jmp	.L550
.L588:
	leaq	.LC21(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
.L488:
	movq	%rax, %rbx
	movq	-1600(%rbp), %rax
	leaq	168(%rax), %rdi
	vzeroupper
	call	_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EED2Ev
.L325:
	movq	-1600(%rbp), %rax
	leaq	88(%rax), %rdi
	call	_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EED2Ev
.L326:
	movq	-1600(%rbp), %rdi
	addq	$8, %rdi
	call	_ZNSt11_Deque_baseI11KOK_MessageSaIS0_EED2Ev
	jmp	.L322
.L491:
	movq	%rax, %r13
	leaq	16+_ZTVNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	-496(%rbp), %rdi
	movq	%rax, -568(%rbp)
	leaq	112(%rbx), %rax
	cmpq	%rax, %rdi
	je	.L535
	vzeroupper
	call	_ZdlPv@PLT
.L354:
	leaq	16+_ZTVSt15basic_streambufIcSt11char_traitsIcEE(%rip), %rax
	leaq	80(%rbx), %rdi
	movq	%rax, -568(%rbp)
	call	_ZNSt6localeD1Ev@PLT
	movq	8+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	48+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	-24(%rax), %rax
	movq	%rcx, -592(%rbp,%rax)
	movq	32+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	40+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%rax, -576(%rbp)
	movq	-24(%rax), %rax
	movq	%rcx, -576(%rbp,%rax)
	movq	-24(%r12), %rax
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%r12, -592(%rbp)
	movq	%rcx, -592(%rbp,%rax)
	movq	$0, -584(%rbp)
	jmp	.L352
.L492:
	movq	%rax, %r13
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	-24(%r12), %rax
	movq	%r12, -592(%rbp)
	movq	%rcx, -592(%rbp,%rax)
	movq	$0, -584(%rbp)
	vzeroupper
	jmp	.L352
.L535:
	vzeroupper
	jmp	.L354
.L482:
.L553:
	movq	%rax, %r12
	movq	-1512(%rbp), %rax
	movq	-1008(%rbp), %rdi
	addq	$16, %rax
	cmpq	%rax, %rdi
	je	.L542
	vzeroupper
	call	_ZdlPv@PLT
	jmp	.L391
.L480:
	movq	-1520(%rbp), %rdi
	movq	%rax, %rbx
	movl	$168, %esi
	vzeroupper
	call	_ZdlPvm@PLT
	jmp	.L346
.L542:
	vzeroupper
	jmp	.L391
.L461:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L418
.L460:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L449
.L478:
	movq	-1608(%rbp), %rdi
	movq	%rax, %r12
	movl	$152, %esi
	vzeroupper
	call	_ZdlPvm@PLT
	jmp	.L441
.L584:
	leaq	.LC21(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
.L583:
	call	__stack_chk_fail@PLT
.L568:
	movq	%rdx, %rax
	jmp	.L360
.L565:
	leaq	.LC0(%rip), %rdi
	call	_ZSt19__throw_logic_errorPKc@PLT
.L481:
	movq	%rax, %r12
	vzeroupper
	jmp	.L391
.L469:
	movq	-1624(%rbp), %rdi
	movq	%rax, %rbx
	movl	$56, %esi
	vzeroupper
	call	_ZdlPvm@PLT
	jmp	.L418
.L468:
.L563:
	movq	%rax, %r12
	movq	-1568(%rbp), %rax
	movq	-848(%rbp), %rdi
	addq	$16, %rax
	cmpq	%rax, %rdi
	je	.L559
	vzeroupper
	call	_ZdlPv@PLT
	jmp	.L438
.L467:
	jmp	.L560
.L585:
	leaq	.LC21(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
.LEHE73:
.L493:
	jmp	.L553
.L459:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L322
.L579:
	leaq	.LC21(%rip), %rdi
.LEHB74:
	call	_ZSt20__throw_length_errorPKc@PLT
.LEHE74:
.L487:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L325
.L486:
	movq	%rax, %rbx
	vzeroupper
	jmp	.L326
.L485:
	movq	8(%rbx), %rdi
	movq	%rax, %r12
	cmpq	%r13, %rdi
	je	.L534
	vzeroupper
	call	_ZdlPv@PLT
.L321:
	movq	%rbx, %rdi
	movl	$40, %esi
	movq	%r12, %rbx
	call	_ZdlPvm@PLT
	jmp	.L322
.L458:
	movq	-1536(%rbp), %rdi
	movq	%rax, %rbx
	movl	$100, %esi
	vzeroupper
	call	_ZdlPvm@PLT
	jmp	.L322
.L466:
	jmp	.L563
.L534:
	vzeroupper
	jmp	.L321
.L465:
	jmp	.L560
.L464:
	jmp	.L563
.L463:
	jmp	.L560
.L462:
	movq	-592(%rbp), %rdi
	addq	$16, %rbx
	movq	%rax, %r12
	cmpq	%rbx, %rdi
	je	.L538
	vzeroupper
	call	_ZdlPv@PLT
	jmp	.L439
.L538:
	vzeroupper
	jmp	.L439
	.cfi_endproc
.LFE16954:
	.section	.gcc_except_table
.LLSDA16954:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE16954-.LLSDACSB16954
.LLSDACSB16954:
	.uleb128 .LEHB13-.LFB16954
	.uleb128 .LEHE13-.LEHB13
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB14-.LFB16954
	.uleb128 .LEHE14-.LEHB14
	.uleb128 .L459-.LFB16954
	.uleb128 0
	.uleb128 .LEHB15-.LFB16954
	.uleb128 .LEHE15-.LEHB15
	.uleb128 .L458-.LFB16954
	.uleb128 0
	.uleb128 .LEHB16-.LFB16954
	.uleb128 .LEHE16-.LEHB16
	.uleb128 .L459-.LFB16954
	.uleb128 0
	.uleb128 .LEHB17-.LFB16954
	.uleb128 .LEHE17-.LEHB17
	.uleb128 .L485-.LFB16954
	.uleb128 0
	.uleb128 .LEHB18-.LFB16954
	.uleb128 .LEHE18-.LEHB18
	.uleb128 .L459-.LFB16954
	.uleb128 0
	.uleb128 .LEHB19-.LFB16954
	.uleb128 .LEHE19-.LEHB19
	.uleb128 .L486-.LFB16954
	.uleb128 0
	.uleb128 .LEHB20-.LFB16954
	.uleb128 .LEHE20-.LEHB20
	.uleb128 .L487-.LFB16954
	.uleb128 0
	.uleb128 .LEHB21-.LFB16954
	.uleb128 .LEHE21-.LEHB21
	.uleb128 .L488-.LFB16954
	.uleb128 0
	.uleb128 .LEHB22-.LFB16954
	.uleb128 .LEHE22-.LEHB22
	.uleb128 .L460-.LFB16954
	.uleb128 0
	.uleb128 .LEHB23-.LFB16954
	.uleb128 .LEHE23-.LEHB23
	.uleb128 .L461-.LFB16954
	.uleb128 0
	.uleb128 .LEHB24-.LFB16954
	.uleb128 .LEHE24-.LEHB24
	.uleb128 .L462-.LFB16954
	.uleb128 0
	.uleb128 .LEHB25-.LFB16954
	.uleb128 .LEHE25-.LEHB25
	.uleb128 .L461-.LFB16954
	.uleb128 0
	.uleb128 .LEHB26-.LFB16954
	.uleb128 .LEHE26-.LEHB26
	.uleb128 .L463-.LFB16954
	.uleb128 0
	.uleb128 .LEHB27-.LFB16954
	.uleb128 .LEHE27-.LEHB27
	.uleb128 .L464-.LFB16954
	.uleb128 0
	.uleb128 .LEHB28-.LFB16954
	.uleb128 .LEHE28-.LEHB28
	.uleb128 .L461-.LFB16954
	.uleb128 0
	.uleb128 .LEHB29-.LFB16954
	.uleb128 .LEHE29-.LEHB29
	.uleb128 .L465-.LFB16954
	.uleb128 0
	.uleb128 .LEHB30-.LFB16954
	.uleb128 .LEHE30-.LEHB30
	.uleb128 .L466-.LFB16954
	.uleb128 0
	.uleb128 .LEHB31-.LFB16954
	.uleb128 .LEHE31-.LEHB31
	.uleb128 .L461-.LFB16954
	.uleb128 0
	.uleb128 .LEHB32-.LFB16954
	.uleb128 .LEHE32-.LEHB32
	.uleb128 .L467-.LFB16954
	.uleb128 0
	.uleb128 .LEHB33-.LFB16954
	.uleb128 .LEHE33-.LEHB33
	.uleb128 .L468-.LFB16954
	.uleb128 0
	.uleb128 .LEHB34-.LFB16954
	.uleb128 .LEHE34-.LEHB34
	.uleb128 .L461-.LFB16954
	.uleb128 0
	.uleb128 .LEHB35-.LFB16954
	.uleb128 .LEHE35-.LEHB35
	.uleb128 .L469-.LFB16954
	.uleb128 0
	.uleb128 .LEHB36-.LFB16954
	.uleb128 .LEHE36-.LEHB36
	.uleb128 .L461-.LFB16954
	.uleb128 0
	.uleb128 .LEHB37-.LFB16954
	.uleb128 .LEHE37-.LEHB37
	.uleb128 .L470-.LFB16954
	.uleb128 0
	.uleb128 .LEHB38-.LFB16954
	.uleb128 .LEHE38-.LEHB38
	.uleb128 .L461-.LFB16954
	.uleb128 0
	.uleb128 .LEHB39-.LFB16954
	.uleb128 .LEHE39-.LEHB39
	.uleb128 .L471-.LFB16954
	.uleb128 0
	.uleb128 .LEHB40-.LFB16954
	.uleb128 .LEHE40-.LEHB40
	.uleb128 .L461-.LFB16954
	.uleb128 0
	.uleb128 .LEHB41-.LFB16954
	.uleb128 .LEHE41-.LEHB41
	.uleb128 .L472-.LFB16954
	.uleb128 0
	.uleb128 .LEHB42-.LFB16954
	.uleb128 .LEHE42-.LEHB42
	.uleb128 .L461-.LFB16954
	.uleb128 0
	.uleb128 .LEHB43-.LFB16954
	.uleb128 .LEHE43-.LEHB43
	.uleb128 .L473-.LFB16954
	.uleb128 0
	.uleb128 .LEHB44-.LFB16954
	.uleb128 .LEHE44-.LEHB44
	.uleb128 .L461-.LFB16954
	.uleb128 0
	.uleb128 .LEHB45-.LFB16954
	.uleb128 .LEHE45-.LEHB45
	.uleb128 .L474-.LFB16954
	.uleb128 0
	.uleb128 .LEHB46-.LFB16954
	.uleb128 .LEHE46-.LEHB46
	.uleb128 .L461-.LFB16954
	.uleb128 0
	.uleb128 .LEHB47-.LFB16954
	.uleb128 .LEHE47-.LEHB47
	.uleb128 .L475-.LFB16954
	.uleb128 0
	.uleb128 .LEHB48-.LFB16954
	.uleb128 .LEHE48-.LEHB48
	.uleb128 .L476-.LFB16954
	.uleb128 0
	.uleb128 .LEHB49-.LFB16954
	.uleb128 .LEHE49-.LEHB49
	.uleb128 .L461-.LFB16954
	.uleb128 0
	.uleb128 .LEHB50-.LFB16954
	.uleb128 .LEHE50-.LEHB50
	.uleb128 .L479-.LFB16954
	.uleb128 0
	.uleb128 .LEHB51-.LFB16954
	.uleb128 .LEHE51-.LEHB51
	.uleb128 .L477-.LFB16954
	.uleb128 0
	.uleb128 .LEHB52-.LFB16954
	.uleb128 .LEHE52-.LEHB52
	.uleb128 .L478-.LFB16954
	.uleb128 0
	.uleb128 .LEHB53-.LFB16954
	.uleb128 .LEHE53-.LEHB53
	.uleb128 .L479-.LFB16954
	.uleb128 0
	.uleb128 .LEHB54-.LFB16954
	.uleb128 .LEHE54-.LEHB54
	.uleb128 .L480-.LFB16954
	.uleb128 0
	.uleb128 .LEHB55-.LFB16954
	.uleb128 .LEHE55-.LEHB55
	.uleb128 .L479-.LFB16954
	.uleb128 0
	.uleb128 .LEHB56-.LFB16954
	.uleb128 .LEHE56-.LEHB56
	.uleb128 .L482-.LFB16954
	.uleb128 0
	.uleb128 .LEHB57-.LFB16954
	.uleb128 .LEHE57-.LEHB57
	.uleb128 .L494-.LFB16954
	.uleb128 0
	.uleb128 .LEHB58-.LFB16954
	.uleb128 .LEHE58-.LEHB58
	.uleb128 .L484-.LFB16954
	.uleb128 0
	.uleb128 .LEHB59-.LFB16954
	.uleb128 .LEHE59-.LEHB59
	.uleb128 .L483-.LFB16954
	.uleb128 0
	.uleb128 .LEHB60-.LFB16954
	.uleb128 .LEHE60-.LEHB60
	.uleb128 .L479-.LFB16954
	.uleb128 0
	.uleb128 .LEHB61-.LFB16954
	.uleb128 .LEHE61-.LEHB61
	.uleb128 .L490-.LFB16954
	.uleb128 0
	.uleb128 .LEHB62-.LFB16954
	.uleb128 .LEHE62-.LEHB62
	.uleb128 .L492-.LFB16954
	.uleb128 0
	.uleb128 .LEHB63-.LFB16954
	.uleb128 .LEHE63-.LEHB63
	.uleb128 .L491-.LFB16954
	.uleb128 0
	.uleb128 .LEHB64-.LFB16954
	.uleb128 .LEHE64-.LEHB64
	.uleb128 .L481-.LFB16954
	.uleb128 0
	.uleb128 .LEHB65-.LFB16954
	.uleb128 .LEHE65-.LEHB65
	.uleb128 .L494-.LFB16954
	.uleb128 0
	.uleb128 .LEHB66-.LFB16954
	.uleb128 .LEHE66-.LEHB66
	.uleb128 .L479-.LFB16954
	.uleb128 0
	.uleb128 .LEHB67-.LFB16954
	.uleb128 .LEHE67-.LEHB67
	.uleb128 .L494-.LFB16954
	.uleb128 0
	.uleb128 .LEHB68-.LFB16954
	.uleb128 .LEHE68-.LEHB68
	.uleb128 .L479-.LFB16954
	.uleb128 0
	.uleb128 .LEHB69-.LFB16954
	.uleb128 .LEHE69-.LEHB69
	.uleb128 .L493-.LFB16954
	.uleb128 0
	.uleb128 .LEHB70-.LFB16954
	.uleb128 .LEHE70-.LEHB70
	.uleb128 .L494-.LFB16954
	.uleb128 0
	.uleb128 .LEHB71-.LFB16954
	.uleb128 .LEHE71-.LEHB71
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB72-.LFB16954
	.uleb128 .LEHE72-.LEHB72
	.uleb128 .L489-.LFB16954
	.uleb128 0
	.uleb128 .LEHB73-.LFB16954
	.uleb128 .LEHE73-.LEHB73
	.uleb128 .L493-.LFB16954
	.uleb128 0
	.uleb128 .LEHB74-.LFB16954
	.uleb128 .LEHE74-.LEHB74
	.uleb128 .L494-.LFB16954
	.uleb128 0
.LLSDACSE16954:
	.section	.text.startup
	.size	main, .-main
	.p2align 4,,15
	.type	_GLOBAL__sub_I__ZN17KOK_WindowManager9MouseData6mouseXE, @function
_GLOBAL__sub_I__ZN17KOK_WindowManager9MouseData6mouseXE:
.LFB22092:
	.cfi_startproc
	leaq	_ZStL8__ioinit(%rip), %rdi
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	_ZNSt8ios_base4InitC1Ev@PLT
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi
	leaq	__dso_handle(%rip), %rdx
	leaq	_ZStL8__ioinit(%rip), %rsi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit@PLT
	.cfi_endproc
.LFE22092:
	.size	_GLOBAL__sub_I__ZN17KOK_WindowManager9MouseData6mouseXE, .-_GLOBAL__sub_I__ZN17KOK_WindowManager9MouseData6mouseXE
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZN17KOK_WindowManager9MouseData6mouseXE
	.weak	_ZTS9KOK_Actor
	.section	.rodata._ZTS9KOK_Actor,"aG",@progbits,_ZTS9KOK_Actor,comdat
	.align 8
	.type	_ZTS9KOK_Actor, @object
	.size	_ZTS9KOK_Actor, 11
_ZTS9KOK_Actor:
	.string	"9KOK_Actor"
	.weak	_ZTI9KOK_Actor
	.section	.data.rel.ro._ZTI9KOK_Actor,"awG",@progbits,_ZTI9KOK_Actor,comdat
	.align 8
	.type	_ZTI9KOK_Actor, @object
	.size	_ZTI9KOK_Actor, 16
_ZTI9KOK_Actor:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS9KOK_Actor
	.weak	_ZTS5MyGUI
	.section	.rodata._ZTS5MyGUI,"aG",@progbits,_ZTS5MyGUI,comdat
	.type	_ZTS5MyGUI, @object
	.size	_ZTS5MyGUI, 7
_ZTS5MyGUI:
	.string	"5MyGUI"
	.weak	_ZTI5MyGUI
	.section	.data.rel.ro._ZTI5MyGUI,"awG",@progbits,_ZTI5MyGUI,comdat
	.align 8
	.type	_ZTI5MyGUI, @object
	.size	_ZTI5MyGUI, 24
_ZTI5MyGUI:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS5MyGUI
	.quad	_ZTI9KOK_Actor
	.weak	_ZTV9KOK_Actor
	.section	.data.rel.ro._ZTV9KOK_Actor,"awG",@progbits,_ZTV9KOK_Actor,comdat
	.align 8
	.type	_ZTV9KOK_Actor, @object
	.size	_ZTV9KOK_Actor, 40
_ZTV9KOK_Actor:
	.quad	0
	.quad	_ZTI9KOK_Actor
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.weak	_ZTV5MyGUI
	.section	.data.rel.ro.local._ZTV5MyGUI,"awG",@progbits,_ZTV5MyGUI,comdat
	.align 8
	.type	_ZTV5MyGUI, @object
	.size	_ZTV5MyGUI, 40
_ZTV5MyGUI:
	.quad	0
	.quad	_ZTI5MyGUI
	.quad	_ZN5MyGUI6UpdateEd
	.quad	_ZN5MyGUI14DeliverMessageEy11MessageDataP9KOK_Actor
	.quad	_ZN5MyGUI4DrawEv
	.globl	runTime
	.bss
	.align 8
	.type	runTime, @object
	.size	runTime, 8
runTime:
	.zero	8
	.section	.rodata
	.align 8
	.type	_ZL13K_COLOR_WHITE, @object
	.size	_ZL13K_COLOR_WHITE, 12
_ZL13K_COLOR_WHITE:
	.long	1065353216
	.long	1065353216
	.long	1065353216
	.globl	_ZN17KOK_WindowManager8Textures8circle16E
	.bss
	.align 4
	.type	_ZN17KOK_WindowManager8Textures8circle16E, @object
	.size	_ZN17KOK_WindowManager8Textures8circle16E, 4
_ZN17KOK_WindowManager8Textures8circle16E:
	.zero	4
	.globl	_ZN17KOK_WindowManager9MouseData12rightPressedE
	.type	_ZN17KOK_WindowManager9MouseData12rightPressedE, @object
	.size	_ZN17KOK_WindowManager9MouseData12rightPressedE, 1
_ZN17KOK_WindowManager9MouseData12rightPressedE:
	.zero	1
	.globl	_ZN17KOK_WindowManager9MouseData11leftPressedE
	.type	_ZN17KOK_WindowManager9MouseData11leftPressedE, @object
	.size	_ZN17KOK_WindowManager9MouseData11leftPressedE, 1
_ZN17KOK_WindowManager9MouseData11leftPressedE:
	.zero	1
	.globl	_ZN17KOK_WindowManager9MouseData6mouseYE
	.align 8
	.type	_ZN17KOK_WindowManager9MouseData6mouseYE, @object
	.size	_ZN17KOK_WindowManager9MouseData6mouseYE, 8
_ZN17KOK_WindowManager9MouseData6mouseYE:
	.zero	8
	.globl	_ZN17KOK_WindowManager9MouseData6mouseXE
	.align 8
	.type	_ZN17KOK_WindowManager9MouseData6mouseXE, @object
	.size	_ZN17KOK_WindowManager9MouseData6mouseXE, 8
_ZN17KOK_WindowManager9MouseData6mouseXE:
	.zero	8
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC6:
	.quad	8247626353043844910
	.quad	7310302547463336805
	.section	.rodata.cst32,"aM",@progbits,32
	.align 32
.LC12:
	.long	36064
	.long	36065
	.long	36066
	.long	36067
	.long	36068
	.long	36069
	.long	36070
	.long	36071
	.align 32
.LC16:
	.long	1092616192
	.long	1036831949
	.long	0
	.long	0
	.long	0
	.long	0
	.long	1036831949
	.long	0
	.align 32
.LC17:
	.long	0
	.long	0
	.long	0
	.long	3184315597
	.long	0
	.long	2147483648
	.long	2147483648
	.long	2147483648
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC18:
	.long	1065353216
	.section	.rodata.cst16
	.align 16
.LC19:
	.quad	8247626353043844910
	.quad	7593965388685079397
	.section	.rodata.cst32
	.align 32
.LC24:
	.long	1068356297
	.long	0
	.long	0
	.long	0
	.long	0
	.long	1075479161
	.long	0
	.long	0
	.align 32
.LC25:
	.long	0
	.long	0
	.long	3212838542
	.long	3212836864
	.long	0
	.long	0
	.long	3164855100
	.long	0
	.section	.rodata.cst4
	.align 4
.LC31:
	.long	1135869952
	.align 4
.LC32:
	.long	1140850688
	.align 4
.LC33:
	.long	1151336448
	.align 4
.LC36:
	.long	1073741824
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC47:
	.long	2576980378
	.long	1069128089
	.align 8
.LC48:
	.long	0
	.long	1079574528
	.section	.rodata.cst4
	.align 4
.LC53:
	.long	1056964608
	.align 4
.LC54:
	.long	1143767040
	.align 4
.LC55:
	.long	1103626240
	.align 4
.LC56:
	.long	1142620160
	.section	.rodata.cst16
	.align 16
.LC57:
	.quad	2314885530818453536
	.quad	2314885530818453536
	.align 16
.LC58:
	.quad	7954878058108841537
	.quad	7449362198107594868
	.align 16
.LC59:
	.quad	7815275222233263717
	.quad	7358993311817998436
	.align 16
.LC60:
	.quad	5280275146916712267
	.quad	5283657245585458510
	.section	.data.rel.ro,"aw",@progbits
	.align 8
.LC61:
	.quad	_ZTVNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE+64
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
