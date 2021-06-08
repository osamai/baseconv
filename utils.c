#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "utils.h"

void panic(const char *fmt, ...) {
	if (fmt[0] == ':') {
		fputs(NAME, stderr);
	}

	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	fputc('\n', stderr);
	exit(1);
}

char ctoupper(char c) {
	if (c < 'a' || c > 'z') {
		return c;
	}
	return c - 'a' + 'A';
}

char *trimnum(char *input) {
	if (!input || strlen(input) < 2) {
		return input;
	}
	if (input[0] == '+' || input[0] == '-') {
		input++;
	}
	if (input[0] == '0') {
		input++;
	}
	char c = ctoupper(input[0]);
	if (c == 'B' || c == 'O' || c == 'X') {
		input++;
	}
	for (; input[0] == '0'; input++);
	return input;
}

void printbin(long long num) {
	if (num == 0) {
		puts("0b0");
		return;
	}

	if (num < 0) {
		num = ~num + 1;
		if (num > 0) {
			putchar('-');
		}
	}

	int c = 63;
	char str[65] = {0};
	for (; num != 0 && c >= 0; c--) {
		str[c] = "01"[num&1];
		num >>= 1;
	}

	printf("0b%s\n", str+c+1);
}
