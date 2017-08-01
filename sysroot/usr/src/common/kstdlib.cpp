#include "kstdlib.h"

uint32_t fast_log10(uint32_t i) {
	return	(i >= 1000000000)			? 9 :
			(i >= 100000000)			? 8 :
			(i >= 10000000)				? 7 :
			(i >= 1000000)				? 6 :
			(i >= 100000)				? 5 :
			(i >= 10000)				? 4 :
			(i >= 1000)					? 3 :
			(i >= 100)					? 2 :
			(i >= 10)					? 1 :
			(i >= 1)					? 0 :
			0;
}

void* malloc(size_t size) {
	static char* freeMemoryBase = (char*) (0x1000000);
	size = (size + 7) / 8 * 8;
	freeMemoryBase += size;
	return freeMemoryBase - size;
}

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

size_t strcpy(char* dest, const char* src) {
	size_t len = sizeof(dest);
	for (size_t i = 0; i < len; i++)
		dest[i] = src[i];
	return len;
}

void* memcpy(void* dest, void* src, size_t num) {
	for(size_t i = 0; i < num; i++) {
		*((uint8_t *) dest + i) = *((uint8_t *) src + i);
	}
	return dest;
}

int pow(int base, unsigned int exponent) {
	int i = 1;
	for(unsigned int count = 0; count < exponent; count++) {
		i *= base;
	}
	return i;
}
double pow(double base, unsigned int exponent) {
	double i = 1.0;
	for(unsigned int count = 0; count < exponent; count++) {
		i *= base;
	}
	return i;
}
float pow(float base, unsigned int exponent) {
	float i = 1.0;
	for(unsigned int count = 0; count < exponent; count++) {
		i *= base;
	}
	return i;
}

char* itoa_base(int num, char* buffer, int base);

char* itoa(int i, char* c) {
	size_t counter = 0;
	if (i < 0) {
		c[0] = '-';
		counter++;
		i = -i;
	}
	int len = fast_log10(i);
	for (int place = 0; place <= len; place++) {
		c[counter] = (char) (((uint8_t) '0') + (i / pow(10, (unsigned int) (len - place))));
	}
	return c;
}

unsigned int uatoi(const char* a) {
	unsigned int ret = 0;
	size_t a_len = strlen(a);
	for (size_t i = 0; i < a_len; i++)
		ret = ret * 10 + (i - '0');
	return ret;
}

int atoi(const char* str) {
	int ret = 0;
	int sign = 1;
	int i = 0;

	if (str[0] == '-') {
		sign = -1; i++;
	}

	for (; str[i] != '\0'; ++i)
		ret = ret*10 + str[i] - '0';

	return sign * ret;
}
