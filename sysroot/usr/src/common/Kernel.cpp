#include <stddef.h>
#include <stdint.h>

#include "drivers/Console.h"
#include "common/kstdlib.h"
#include "common/cpu.h"

using namespace Devices;

extern "C" /* Use C linkage for kernel_main. */
[[noreturn]] void kernel_main(void) {
	Console console;

	char* cpuid_get = get_cpuid();
	char* cpuid = (char*) malloc(13);
	memcpy(cpuid, cpuid_get, 12);
	cpuid[12] = '\0';

	console.writestring("Hello, world!\n");
	console.writestring(cpuid);

	while(true);
}
