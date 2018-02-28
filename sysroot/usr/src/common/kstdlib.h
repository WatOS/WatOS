#pragma once

#include "config.h"
#include <stdint.h>
#include <stddef.h>

uint32_t fast_log10(uint32_t i);
void* malloc(size_t size);
size_t strlen(const char* str);
size_t strcpy(char* dest, const char* src);
void* memcpy(void* dest, void* src, size_t num);
int pow(int base, unsigned int exponent);
double pow(double base, unsigned int exponent);
float pow(float base, unsigned int exponent);
char* itoa_base(int num, char* buffer, int base);
char* itoa(int i, char* c);
unsigned int uatoi(const char* a);
int atoi(const char* str);

int kmsg(char* type, uint8_t type_color, char* msg);
