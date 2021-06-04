#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef NAME
#define NAME "baseconv"
#endif

#define streq(s1, s2) (strcmp(s1, s2) == 0)
#define panic(...) { fprintf(stderr, __VA_ARGS__); exit(1); }

typedef enum numtype {
	NT_UNKNOWN = 0,
	NT_BINARY = 2,
	NT_OCTAL = 8,
	NT_DECIMAL = 10,
	NT_HEX = 16,
} numtype_t;

numtype_t parse_numtype(const char *s) {
	if (streq(s, "bin") || streq(s, "binary")) {
		return NT_BINARY;
	} else if (streq(s, "oct") || streq(s, "octal")) {
		return NT_OCTAL;
	} else if (streq(s, "dec") || streq(s, "decimal")) {
		return NT_DECIMAL;
	} else if (streq(s, "hex") || streq(s, "hexadecimal")) {
		return NT_HEX;
	}
	return NT_UNKNOWN;
}

bool isbinary(const char *input) {
	for (size_t i = 0; i < strlen(input); i++) {
		if (input[i] != '0' && input[i] != '1') {
			return false;
		}
	}
	return true;
}

bool isoctal(const char *input) {
	for (size_t i = 0; i < strlen(input); i++) {
		if (input[i] < '0' || input[i] > '7') {
			return false;
		}
	}
	return true;
}

void printbin(long long num) {
	if (num == 0) {
		puts("0");
		return;
	}

	int c = 63;
	char str[65] = {0};
	for (; num != 0 && c >= 0; c--) {
		str[c] = "01"[num&1];
		num >>= 1;
	}

	printf("%s\n", str+c+1);
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		panic(NAME": at least one argument is required\n");
	}

	numtype_t optfrom = NT_UNKNOWN;
	numtype_t optto = NT_UNKNOWN;

	char *argp = 0;
	char *input = 0;
	for (int i = 0; i < argc; i++) {
		argp = argv[i];
		if (argp[0] != '-') {
			input = argp;
			continue;
		}
		argp++;
		if (argp[0] == '-') argp++;
		if (streq(argp, "from")) {
			if (argc <= i+1 || argv[i+1][0] == '-') {
				panic(NAME": %s expect a value\n", argv[i]);
			}
			optfrom = parse_numtype(argv[i+1]);
			i++;
		} else if (streq(argp, "to")) {
			if (argc <= i+1 || argv[i+1][0] == '-') {
				panic(NAME": %s expect a value\n", argv[i]);
			}
			optto = parse_numtype(argv[i+1]);
			i++;
		} else {
			panic(NAME": unknown argument %s\n", argv[i]);
		}
	}

	if (!input || input[0] == 0) {
		panic(NAME": empty input\n");
	}
	if (optfrom == NT_BINARY && !isbinary(input)) {
		panic(NAME": input: invalid binary format\n");
	}
	if (optfrom == NT_OCTAL && !isoctal(input)){
		panic(NAME": input: invalid octal format\n");
	}

	if (optfrom == NT_UNKNOWN) {
		if (input[0] == 'x' || (input[0] == '0' && (input[1] == 'x' || input[1] == 'X'))) {
			optfrom = NT_HEX;
		} else if (input[0] == '0') {
			if (isbinary(input)) {
				optfrom = NT_BINARY;
			} else if (isoctal(input)) {
				optfrom = NT_OCTAL;
			} else {
				optfrom = NT_DECIMAL;
				input++;
			}
		} else {
			optfrom = isbinary(input) ? NT_BINARY : NT_DECIMAL;
		}
	}

	long long num = strtol(input, 0, optfrom);

	switch (optto) {
		case NT_BINARY:
			printbin(num);
			break;
		case NT_OCTAL:
			printf("%o\n", (unsigned int)num);
			break;
		case NT_HEX:
			printf("%x\n", (unsigned int)num);
			break;
		default: // NT_DECIMAL || NT_UNKNOWN
			printf("%lld\n", num);
			break;
	}

	return 0;
}
