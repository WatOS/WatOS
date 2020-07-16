#pragma once

#include <stddef.h>
#include <stdint.h>

#include "../arch/i386/AsmFunctions.h"

#define VGA_ENTRY_POINT ((void *) 0xB8000)

namespace Devices {
	/* Hardware text mode color constants. */
	enum vga_color {
		BLACK = 0,
		BLUE = 1,
		GREEN = 2,
		CYAN = 3,
		RED = 4,
		MAGENTA = 5,
		BROWN = 6,
		LIGHT_GREY = 7,
		DARK_GREY = 8,
		LIGHT_BLUE = 9,
		LIGHT_GREEN = 10,
		LIGHT_CYAN = 11,
		LIGHT_RED = 12,
		LIGHT_MAGENTA = 13,
		YELLOW = 14,
		WHITE = 15,
	};
}

#include "../common/kstdlib.h"

namespace Devices {
	class Console {
		public:
			Console();

			static bool initialized;

			static const size_t VGA_WIDTH = 80;
			static const size_t VGA_HEIGHT = 25;

			size_t terminal_row;
			size_t terminal_column;
			uint8_t terminal_color;
			uint16_t* terminal_buffer;

			inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
				return fg | bg << 4;
			}

			inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
				return (uint16_t) uc | (uint16_t) color << 8;
			}

			void set_color(enum vga_color color);
			void putchar(char c);
			void putchar_buf(char c);
			void write(const char* data, size_t size);
			void writestring(const char* data);
			void writestring(const char* data, enum vga_color color);
			void initialize(void);
			void move_cursor(size_t x, size_t y);
			void flush_buffer(void);
		private:
			void putentryat(char c, uint8_t color, size_t x, size_t y);
	};

	extern Console kconsole;
}
