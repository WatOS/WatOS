#include <stddef.h>
#include <stdint.h>

#include "drivers/Console.h"
#include "drivers/SerialConsole.h"
#include "common/kstdlib.h"
#include "common/cpu.h"
#include "arch/i386/multiboot.h"

using namespace Devices;

extern "C"
[[noreturn]] void kernel_main(void) {
	kconsole.initialize();
	kconsole.set_color((uint8_t) 0x0F);
	kconsole.write("[", 1);
	kconsole.set_color((uint8_t) 0x02);
	kconsole.write("INFO", 4);
	kconsole.set_color((uint8_t) 0x0F);
	kconsole.writestring("] Initialized early console\n");
	

	char vendor[13]; vendor[12] = 0;
	uint32_t max_func = cpuid_vendor(vendor);
	kprintf("CPU: vendor %s, max cpuid %d\n", vendor, max_func);

	struct cpuid_info_data i = cpuid_info();
	kprintf("CPU: type %d, family %d, model %d, stepping %d\n",
			i.ver.type, i.real_family, i.real_model, i.ver.stepping);
	kprintf("CPU: fpu %d, vme %d, de %d, pse %d, tsc %d, msr %d, "
			"pae %d, mce %d, cx8 %d, apic %d",
			i.flags.fpu, i.flags.vme, i.flags.de, i.flags.pse,
			i.flags.tsc, i.flags.msr, i.flags.pae, i.flags.mce,
			i.flags.cx8, i.flags.apic);

	serial_console.writestring("Hello, world!\n");

	while (true) ;
}

extern "C"
void not_multiboot(void) {
	Console console;
	console.set_color(VGA_COLOR_RED);
	console.writestring("Error: ");
	console.set_color(VGA_COLOR_LIGHT_GREY);
	console.writestring("Kernel was booted with a non-Multiboot bootloader.\n");
	console.writestring("Please boot with a compatible loader, such as GRUB.\n");
	while(true);
}
