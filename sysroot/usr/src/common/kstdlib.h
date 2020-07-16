#pragma once

#include "config.h"
#include <stdint.h>
#include <stddef.h>
#include "drivers/Console.h"

// Linux code (GPL2 / trivial?)
inline void io_delay(void) {
    const uint16_t DELAY_PORT = 0x80;
    asm volatile("outb %%al,%0" : : "dN" (DELAY_PORT));
}

uint32_t fast_log10(uint32_t i);
void * malloc(size_t size);
void * memset(void *ptr, uint8_t value, size_t num);
void * calloc(size_t num, size_t size);
size_t strlen(const char *str);
size_t strcpy(char *dest, const char *src);
void* memcpy(void *dest, void *src, size_t num);
int pow(int base, unsigned int exponent);
double pow(double base, unsigned int exponent);
float pow(float base, unsigned int exponent);
void itoa(char *buf, int base, int d);
unsigned int uatoi(const char *a);
int atoi(const char *str);
void itoa(char *buf, int base, int d);
void kprintf(const char *format, ...);

void putchar(char);

int kmsg(char *type, uint8_t type_color, char *msg);
