#include "Console.h"

namespace Devices {
	bool Console::initialized = false;
	size_t Console::strlen(const char* str) {
		size_t len = 0;
		while (str[len])
			len++;
		return len;
	}

	Console::Console() {
		if (!Console::initialized)
			initialize();
	}

	void Console::initialize(void) {
		terminal_row = 0;
		terminal_column = 0;
		terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
		terminal_buffer = (uint16_t*) 0xB8000;
		for (size_t y = 0; y < VGA_HEIGHT; y++) {
			for (size_t x = 0; x < VGA_WIDTH; x++) {
				const size_t index = y * VGA_WIDTH + x;
				terminal_buffer[index] = vga_entry(' ', terminal_color);
			}
		}
	}

	void Console::set_color(uint8_t color) {
		terminal_color = color;
	}

	void Console::putentryat(char c, uint8_t color, size_t x, size_t y) {
		const size_t index = y * VGA_WIDTH + x;
		terminal_buffer[index] = vga_entry(c, color);
	}

	void Console::putchar(char c) {
		if (c == '\n') {
			if (++terminal_row == VGA_HEIGHT) {
				terminal_row = 0;
			}
			terminal_column = 0;
			return;
		}
		putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				terminal_row = 0;
		}
	}

	void Console::write(const char* data, size_t size) {
		for (size_t i = 0; i < size; i++)
			putchar(data[i]);
	}

	void Console::writestring(const char* data) {
		write(data, strlen(data));
	}
}
