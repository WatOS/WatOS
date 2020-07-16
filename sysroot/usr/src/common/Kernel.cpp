#include <stddef.h>
#include <stdint.h>

#include "drivers/console/Console.h"
#include "drivers/console/SerialConsole.h"
#include "common/kstdlib.h"
#include "arch/i386/cpuid.h"
#include "arch/i386/multiboot.h"

using namespace Devices;

void init_console(void) {
	kconsole.initialize();

	kconsole.writestring("WatOS", YELLOW);
	kconsole.writestring(", version ");
	kconsole.writestring("a0.0.1\n\n", WHITE);
}

void print_cpuid(void) {
	char vendor[13]; vendor[12] = 0;
	uint32_t max_func = cpuid_vendor(vendor);
	uint32_t max_ext = cpuid_max_ext();
	kmsg("CPU", BLUE, "vendor %s, max cpuid %d, max ext cpuid %d",
			vendor, max_func, max_ext ^ 0x80000000);
	char brand[49]; brand[48] = 0;
	cpuid_brand(brand);
	kmsg("CPU", BLUE, "brand %s", brand);

	struct cpuid_info_data i = cpuid_info();
	kmsg("CPU", BLUE, "type %d, family %d, model %d, stepping %d",
			i.ver.type, i.real_family, i.real_model, i.ver.stepping);
	kmsg("CPU", BLUE, "fpu %d, vme %d, de %d, pse %d, tsc %d, msr %d, "
			"pae %d, mce %d, cx8 %d, apic %d",
			i.flags.fpu, i.flags.vme, i.flags.de, i.flags.pse,
			i.flags.tsc, i.flags.msr, i.flags.pae, i.flags.mce,
			i.flags.cx8, i.flags.apic);
}

extern "C"
[[noreturn]] void kernel_main(void) {
	init_console();
	print_cpuid();

	serial_console.writestring("Hello, world!\n");

	while (true) ;
}

extern "C"
void not_multiboot(void) {
	Console console;
	console.initialize();

	console.writestring("Error: ", RED);
	console.set_color(LIGHT_GREY);
	console.writestring("Kernel was booted with a non-Multiboot bootloader.\n");
	console.writestring("Please boot with a compatible loader, such as GRUB.\n");
	while(true);
}
