#include <stddef.h>
#include <stdint.h>

#include "drivers/Console.h"
#include "common/kstdlib.h"
#include "common/cpu.h"

using namespace Devices;

extern "C" /* Use C linkage for kernel_main. */
[[noreturn]] void kernel_main(void) {
	Console console;

	console.writestring("Hello, world!");

	while(true);
}
