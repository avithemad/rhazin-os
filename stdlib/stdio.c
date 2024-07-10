#include "stdio.h"
#include <stdarg.h>
#include "../screen/framebuffer.h"

static void pi_rec(int value) {
	// if we have reached the end, the keep popping the stack and print
	if (value == 0) return;
	pi_rec(value/10);
	putchar(value%10 + '0');
}
static void printInt(int value) {
	if (value == 0) putchar('0');
	else if (value < 0) {
		putchar('-');
		pi_rec(-value);
	}

	else pi_rec(value);
}
static void printHex(int value) {
	char hex[] = "0x00000000";
	int i=0;
	while(value!=0) {
		int single = value & 0xF;
		if (single < 10) hex[9-i] = single + '0';
		else hex[9-i] = single - 10 + 'A';
		i++;
		value = value >> 4;
	}
	print(hex);
}

void printf(const char* s, ...) {
	va_list arg_ptr;
	int n;
	va_start(arg_ptr, n);

	for (int i=0; s[i]!='\0'; i++) {
		if (s[i] == '%'){
			// not valid format
			if (s[i+1] == '\0') {
				return;
			}
			// read the integer and print it as formatted
			if (s[i+1] == 'd') {
				int value = va_arg(arg_ptr, int);
				printInt(value);
				i++;
				continue;
			}else if (s[i+1] == 'x') {
				int value = va_arg(arg_ptr, int);
				printHex(value);
				i++;
			} else {
				putchar('%');
			}
		} else {
			putchar(s[i]);
		}
	}
}
