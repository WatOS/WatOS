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
	kconsole.set_color((uint8_t) 0x0F);
	kconsole.write("[", 1);
	kconsole.set_color((uint8_t) 0x02);
	kconsole.write("INFO", 4);
	kconsole.set_color((uint8_t) 0x0F);
	kconsole.writestring("] Initialized early console\n");

	kconsole.writestring("Hello, world!");

//	serial_console.writestring("Hello, world!");

	while(true);
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
