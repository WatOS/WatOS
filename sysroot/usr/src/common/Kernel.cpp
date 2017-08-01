#include <stddef.h>
#include <stdint.h>

#include "../drivers/Console.h"
#include "../common/kstdlib.h"

using namespace Devices;

extern "C" /* Use C linkage for kernel_main. */
void kernel_main(void) {
	Console console;

	for(char i = ' '; i < '~'; i++) {
		console.write((const char*) &i, 1);
		console.writestring(" ");
	}

}
