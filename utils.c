#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void panic(const char *fmt, ...) {
	if (fmt[0] == ':')
		fputs("baseconv", stderr);

	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	fputc('\n', stderr);
	exit(1);
}

bool isbin(const char *input) {
	for (; *input; input++)
		if (*input != '0' && *input != '1')
			return false;
	return true;
}

bool isoct(const char *input) {
	for (; *input; input++)
		if (*input < '0' || *input > '7')
			return false;
	return true;
}

bool isdec(const char *input) {
	for (; *input; input++)
		if (*input < '0' || *input > '9')
			return false;
	return true;
}

bool ishex(const char *input) {
	for (char c = toupper(*input); *input; c = toupper(*(++input)))
		if (c < '0' || (c > '9' && c < 'A') || c > 'F')
			return false;
	return true;
}

int basefromname(const char *name) {
	if (streq(name, "bin") || streq(name, "binary"))
		return 2;
	if (streq(name, "oct") || streq(name, "octal"))
		return 8;
	if (streq(name, "dec") || streq(name, "decimal"))
		return 10;
	if (streq(name, "hex") || streq(name, "hexadecimal"))
		return 16;
	return strtol(name, 0, 10);
}

int basefrominput(const char *input) {
	if (*input == '+' || *input == '-')
		input++;
	for (; *input == '0'; input++);
	switch (tolower(*input)) {
	case 'b':
		return 2;
	case 'o':
		return 8;
	case 'x':
		return 16;
	default:
		if (isdec(input))
			return 10;
		if (ishex(input))
			return 16;
		return 0;
	}
}

char *trimnum(char *input) {
	if (!input || strlen(input) < 2)
		return input;
	if (*input == '+' || *input == '-')
		input++;
	if (*input == '0')
		input++;
	char c = tolower(*input);
	if (c == 'b' || c == 'o' || c == 'x')
		input++;
	for (; *input == '0'; input++);
	return input;
}

void printbin(long long num) {
	if (num == 0) {
		puts("0b0");
		return;
	}
	if (num < 0)
		num = -num;
	int c = 63;
	char str[65] = {0};
	for (; num != 0 && c >= 0; c--) {
		str[c] = "01"[num&1];
		num >>= 1;
	}
	printf("0b%s\n", str+c+1);
}
