#include "Console.h"

namespace Devices {
	bool Console::initialized = false;

	Console::Console() {
		if (!Console::initialized) // keep a single instance of the cursor, etc.
			initialize();
	}

	void Console::initialize(void) {
		terminal_row = 0;
		terminal_column = 0;
		terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
		terminal_buffer = (uint16_t *) calloc(VGA_HEIGHT*VGA_WIDTH, sizeof(uint16_t));
		for (size_t y = 0; y < VGA_HEIGHT; y++) {
			for (size_t x = 0; x < VGA_WIDTH; x++) {
				const size_t index = y * VGA_WIDTH + x;
				terminal_buffer[index] = vga_entry(' ', terminal_color);
			}
		}
		flush_buffer();
	}

	void Console::move_cursor(size_t x, size_t y) {
		const size_t pos = y * VGA_WIDTH + x;

		outb(0x3D4, 0x0F);
		outb(0x3D5, (uint8_t) (pos & 0xFF));
		outb(0x3D4, 0x0E);
		outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
	}

	void Console::flush_buffer(void) {
		memcpy((void *) VGA_ENTRY_POINT, terminal_buffer, VGA_WIDTH*VGA_HEIGHT * sizeof(uint16_t));
		move_cursor(terminal_column, terminal_row);
	}

	void Console::set_color(uint8_t color) {
		terminal_color = color;
	}

	void Console::putentryat(char c, uint8_t color, size_t x, size_t y) {
		const size_t index = y * VGA_WIDTH + x;
		terminal_buffer[index] = vga_entry(c, color);
	}

	void Console::putchar_buf(char c) {
		if (c == '\n') {
			if (terminal_row + 1 >= VGA_HEIGHT) {
				memcpy(terminal_buffer,
						terminal_buffer + VGA_WIDTH,
						VGA_WIDTH * VGA_HEIGHT * sizeof(uint16_t));
			} else {
				terminal_row++;
			}
			terminal_column = 0;
			return;
		}
		putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			putchar('\n');
		}
	}

	void Console::putchar(char c) {
		putchar_buf(c);
		flush_buffer();
	}

	void Console::write(const char* data, size_t size) {
		for (size_t i = 0; i < size; i++)
			putchar_buf(data[i]);
		flush_buffer();
	}

	void Console::writestring(const char* data) {
		write(data, strlen(data));
	}


	Console kconsole;
}
