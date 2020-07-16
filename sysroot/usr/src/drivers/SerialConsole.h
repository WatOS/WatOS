#pragma once

#include <stddef.h>
#include <stdint.h>

#include "../common/kstdlib.h"
#include "arch/i386/AsmFunctions.h"

namespace Devices {
	class SerialConsole {
		public:
			const static int port = 0x3f8;
			SerialConsole();

			static bool initialized;

			void set_color(uint8_t color);
			void putchar(unsigned char c);
			void write(const char* data, size_t size);
			void writestring(const char* data);

		private:
			void initialize(void);
			int is_transmit_empty(void);
	};
	static SerialConsole serial_console;
}
