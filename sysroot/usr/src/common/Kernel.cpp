#include <stddef.h>
#include <stdint.h>

#include "drivers/Console.h"
#include "common/kstdlib.h"
#include "common/cpu.h"

using namespace Devices;

extern "C" /* Use C linkage for kernel_main. */
void kernel_main(void) {
	Console console;

	char* cpuid = (char*) malloc(13);
	cpuid[12] = '\0';
	cpuid = get_cpuid();

	console.writestring("Hello, world!\n");
	console.writestring(cpuid);
}
