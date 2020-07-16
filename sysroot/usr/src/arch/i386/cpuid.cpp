#include <stdint.h>
#include "cpuid.h"

void cpuid(int op,
		uint32_t *eax, 
		uint32_t *ebx,
		uint32_t *ecx,
		uint32_t *edx) {
	__asm__ volatile (
			"cpuid"
			: "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
			: "a" (op)
			);
}

uint32_t cpuid_vendor(char *vendor) {
	uint32_t max_cpuid, name0, name1, name2;

	cpuid(0, &max_cpuid, &name0, &name2, &name1);

	uint32_t *v_ints = (uint32_t *) vendor;
	v_ints[0] = name0;
	v_ints[1] = name1;
	v_ints[2] = name2;

	return max_cpuid;
}

uint32_t cpuid_max_ext(void) {
	uint32_t eax, ebx, ecx, edx;

	cpuid(0x80000000, &eax, &ebx, &ecx, &edx);

	return eax;
}

struct cpuid_info_data cpuid_info(void) {
	uint32_t eax, ebx, ecx, edx;

	cpuid(1, &eax, &ebx, &ecx, &edx);

	struct cpuid_info_data i;
	i.ver_int = eax;
	i.extra_int = ebx;
	i.flags_int.flags_1 = edx;
	i.flags_int.flags_2 = ecx;

	if (i.ver.family == 6 || i.ver.family == 15) {
		i.real_family = i.ver.ext_family + i.ver.family;
		i.real_model = (i.ver.ext_model << 4) + i.ver.model;
	} else {
		i.real_family = i.ver.family;
		i.real_model = i.ver.model;
	}
	return i;
}

void cpuid_brand(char *brandstr) {
    uint32_t *brand = (uint32_t *) brandstr;
    cpuid(0x80000002, brand+0x0, brand+0x1, brand+0x2, brand+0x3);
    cpuid(0x80000003, brand+0x4, brand+0x5, brand+0x6, brand+0x7);
    cpuid(0x80000004, brand+0x8, brand+0x9, brand+0xa, brand+0xb);
}
