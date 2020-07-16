#pragma once

#include <stdint.h>
#include <stddef.h>

extern "C" {
    inline uint32_t farpeekl (uint16_t sel, void* off) {
        uint32_t ret;
        asm ( "push %%fs\n\t"
              "mov  %1, %%fs\n\t"
              "mov  %%fs:(%2), %0\n\t"
              "pop  %%fs"
              : "=r"(ret) : "g"(sel), "r"(off) );
        return ret;
    }

    inline void farpokeb (uint16_t sel, void* off, uint8_t v) {
        asm ( "push %%fs\n\t"
              "mov  %0, %%fs\n\t"
              "movb %2, %%fs:(%1)\n\t"
              "pop %%fs"
              : : "g"(sel), "r"(off), "r"(v) );
        /* TODO: Should "memory" be in the clobber list here? */
    }
    inline void outb (uint16_t port, uint8_t val) {
        asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
        /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
         * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
         * The  outb  %al, %dx  encoding is the only option for all other cases.
         * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
    }
    inline uint8_t inb(uint16_t port) {
        uint8_t ret;
        asm volatile ( "inb %1, %0"
                       : "=a"(ret)
                       : "Nd"(port) );
        return ret;
    }
    inline void io_wait(void) {
        /* TODO: This is probably fragile. */
        asm volatile ( "jmp 1f\n\t"
                       "1:jmp 2f\n\t"
                       "2:" );
    }
    inline bool are_interrupts_enabled() {
        unsigned long flags;
        asm volatile ( "pushf\n\t"
                       "pop %0"
                       : "=g"(flags) );
        return flags & (1 << 9);
    }
    inline void lidt(void* base, uint16_t size) {
        // This function works in 32 and 64bit mode
        struct {
            uint16_t length;
            void*    base;
        } __attribute__((packed)) IDTR = { size, base };

        asm ( "lidt %0" : : "m"(IDTR) );  // let the compiler choose an addressing mode
    }
}
