#include "SerialConsole.h"

namespace Devices {
	bool SerialConsole::initialized = false;

	SerialConsole::SerialConsole() {
		if (!SerialConsole::initialized) // keep a single instance of the cursor, etc.
			initialize();
	}

	void SerialConsole::initialize(void) {
		outb(port + 1, 0x00);    // Disable all interrupts
		outb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
		outb(port + 0, 0x02);    // Set divisor to 3 (lo byte) 38400 baud
		outb(port + 1, 0x00);    //                  (hi byte)
		outb(port + 3, 0x03);    // 8 bits, no parity, one stop bit
		outb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
		outb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
	}

	int SerialConsole::is_transmit_empty() {
		return inb(port + 5) & 0x20;
	}

	void SerialConsole::putchar(unsigned char a) {
		while (is_transmit_empty() == 0);
		outb(port, a);
	}

	void SerialConsole::set_color(uint8_t color) { // Uses xterm color codes.
		bool high_color = false;
		if (color >= 8) {
			color -= 8;
			high_color = true;
		}
		putchar(0x9b); // Control Sequence Introducer
		if (!high_color) {
			putchar('9');
		} else {
			putchar('1');
			putchar('0');
		}
		putchar(color + '0');
	}

	void SerialConsole::write(const char* data, size_t size) {
		for (size_t i = 0; i < size; i++)
			putchar(data[i]);
	}

	void SerialConsole::writestring(const char* data) {
		write(data, strlen(data));
	}
}
