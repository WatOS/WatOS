#include "kstdlib.h"

void putchar(char c) {
    Devices::kconsole.putchar(c);
}

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

void * malloc(size_t size) {
    static char *freeMemoryBase = (char *) (0x1000000);
    size = (size + 7) / 8 * 8;
    freeMemoryBase += size;
    return freeMemoryBase - size;
}

void * memset(void *ptr, uint8_t value, size_t num) {
    for (size_t i = 0; i < num; i++) ((uint8_t *) ptr)[i] = value;
    return ptr;
}

void * calloc(size_t num, size_t size) {
    size_t bytecount = num * size;
    void *mem = malloc(bytecount);
    return memset(mem, 0, bytecount);
}

size_t strlen(const char *str) {
    size_t len = 0;
    while (str[len])
	len++;
    return len;
}

size_t strcpy(char *dest, const char *src) {
    size_t len = sizeof(dest);
    for (size_t i = 0; i < len; i++)
	dest[i] = src[i];
    return len;
}

void* memcpy(void *dest, void *src, size_t num) {
    for(size_t i = 0; i < num; i++) {
	*((uint8_t *) dest + i) = *((uint8_t *) src + i);
    }
    return dest;
}

int pow(int base, unsigned int exponent) {
    int i = 1;
    for (unsigned int count = 0; count < exponent; count++) {
	i *= base;
    }
    return i;
}
double pow(double base, unsigned int exponent) {
    double i = 1.0;
    for (unsigned int count = 0; count < exponent; count++) {
	i *= base;
    }
    return i;
}
float pow(float base, unsigned int exponent) {
    float i = 1.0;
    for (unsigned int count = 0; count < exponent; count++) {
	i *= base;
    }
    return i;
}

// A simple atoi() function
int myAtoi(char *str)
{
    int res = 0;  // Initialize result
    int sign = 1;  // Initialize sign as positive
    int i = 0;  // Initialize index of first digit

    // If number is negative, then update sign
    if (str[0] == '-')
    {
	sign = -1;
	i++;  // Also update index of first digit
    }

    // Iterate through all digits and update the result
    for (; str[i] != '\0'; ++i)
	res = res*10 + str[i] - '0';

    // Return result with sign
    return sign*res;
}

/* Convert the integer D to a string and save the string in BUF. If
   BASE is equal to 'd', interpret that D is decimal, and if BASE is
   equal to 'x', interpret that D is hexadecimal. */
void itoa (char *buf, int base, int d) {
    char *p = buf;
    char *p1, *p2;
    unsigned long ud = d;
    int divisor = 10;

    /* If %d is specified and D is minus, put `-' in the head. */
    if (base == 'd' && d < 0) {
	*p++ = '-';
	buf++;
	ud = -d;
    }
    else if (base == 'x')
	divisor = 16;

    /* Divide UD by DIVISOR until UD == 0. */
    do {
	int remainder = ud % divisor;
	*p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    } while (ud /= divisor);

    /* Terminate BUF. */
    *p = 0;

    /* Reverse BUF. */
    p1 = buf;
    p2 = p - 1;
    while (p1 < p2) {
	char tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
	p1++;
	p2--;
    }
}

void kvprintf(const char *format, va_list args) {
    int c;
    char buf[20];

    while ((c = *format++) != 0) {
	if (c != '%')
	    Devices::kconsole.putchar_buf(c);
	else {
	    char *p, *p2;
	    int pad0 = 0, pad = 0;

	    c = *format++;
	    if (c == '0') {
		pad0 = 1;
		c = *format++;
	    }

	    if (c >= '0' && c <= '9') {
		pad = c - '0';
		c = *format++;
	    }

	    switch (c) {
		case 'd':
		case 'u':
		case 'x':
		    itoa(buf, c, va_arg(args, int));
		    p = buf;
		    goto string;
		    break;
		case 's':
		    p = va_arg(args, char *);
		    if (! p)
			p = "(null)";
string:
		    for (p2 = p; *p2; p2++);
		    for (; p2 < p + pad; p2++)
			Devices::kconsole.putchar_buf(pad0 ? '0' : ' ');
		    while (*p)
			Devices::kconsole.putchar_buf(*p++);
		    break;

		default:
		    Devices::kconsole.putchar_buf(va_arg(args, int));
		    break;
	    }
	}
    }
    Devices::kconsole.flush_buffer();
}

void kprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    kvprintf(format, args);
    va_end(args);
}

void kmsg(const char *type, enum Devices::vga_color color,
	const char *msg, ...) {
    using namespace Devices;
    kconsole.set_color(WHITE);
    kconsole.putchar('[');
    kconsole.writestring(type, color);
    kconsole.putchar(']');
    kconsole.putchar(' ');
    kconsole.set_color(LIGHT_GREY);

    char **arg = (char **) &msg;
    arg++;

    va_list args;
    va_start(args, msg);
    kvprintf(msg, args);
    va_end(args);

    kconsole.putchar('\n');
}
