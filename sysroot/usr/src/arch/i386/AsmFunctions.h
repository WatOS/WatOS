#include <stdint.h>
#include <stddef.h>

extern "C" {
	static inline uint32_t farpeekl (uint16_t sel, void* off);
	static inline void farpokeb (uint16_t sel, void* off, uint8_t v);
	static inline void outb (uint16_t port, uint8_t val);
	static inline uint8_t inb(uint16_t port);
	static inline void io_wait(void);
	static inline bool are_interrupts_enabled();
	static inline void lidt(void* base, uint16_t size);
}
