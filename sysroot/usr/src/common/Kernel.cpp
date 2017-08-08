#include <stddef.h>
#include <stdint.h>

#include "drivers/Console.h"
#include "common/kstdlib.h"
#include "common/cpu.h"

using namespace Devices;

extern "C" /* Use C linkage for kernel_main. */
[[noreturn]] void kernel_main(void) {
	Console console;

	char* cpuid = get_cpuid();

	char* test = (char*) malloc(13);
	memcpy(test, cpuid, 12);
	test[12] = '\0';

	console.writestring("Hello, world!\n");
	console.write(test, 12);

	while(true);
}
