	.file "cpuid.s"
	.section .data
	.globl get_cpuid
	.type get_cpuid, @function

id_str:
	.ascii "            " 			# 12 spaces

get_cpuid:
	mov 	$0x0, %eax
	cpuid
	mov		%ebx, id_str
	mov		%ecx, id_str + 4
	mov		%edx, id_str + 8
	mov		id_str, %eax
	ret

	.size	get_cpuid, .-get_cpuid
