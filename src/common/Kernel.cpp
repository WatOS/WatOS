#include <stddef.h>
#include <stdint.h>

#include "../drivers/Console.h"

using namespace Devices;

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

extern "C" /* Use C linkage for kernel_main. */
void kernel_main(void) {
	Console console;

	console.writestring("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras nec malesuada nisi, laoreet molestie ipsum. Praesent ac fermentum urna. Aliquam erat volutpat. Aenean imperdiet placerat tincidunt. Pellentesque nec convallis diam, vitae tempus est. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Etiam eu viverra diam.\n");

}
