	.file "cpuid.s"
	.section .data
	.globl get_cpuid
	.type get_cpuid, @function

id_str:
	.ascii "            " 			# 12 spaces

get_cpuid:
	pusha
	mov 	$0, %eax
	cpuid
	movl	%ebx, id_str
	movl	%ecx, id_str + 4
	movl	%edx, id_str + 8
	popa
	mov		id_str, %eax
	ret

	.size	get_cpuid, .-get_cpuid
