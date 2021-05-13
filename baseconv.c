#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef NAME
#define NAME "baseconv"
#endif

#define panic(...) { fprintf(stderr, __VA_ARGS__); exit(1); }

typedef enum numtype {
	NT_UNKNOWN = 0,
	NT_BINARY = 2,
	NT_OCTAL = 8,
	NT_DECIMAL = 10,
	NT_HEX = 16,
} numtype_t;

numtype_t parse_numtype(char *s) {
	if (strcmp(s, "bin") == 0 || strcmp(s, "binary") == 0) {
		return NT_BINARY;
	} else if (strcmp(s, "octal") == 0) {
		return NT_OCTAL;
	} else if (strcmp(s, "decimal") == 0) {
		return NT_DECIMAL;
	} else if (strcmp(s, "hex") == 0 || strcmp(s, "hexadecimal") == 0) {
		return NT_HEX;
	}
	return NT_UNKNOWN;
}

bool isbinary(char *input) {
	for (size_t i = 0; i < strlen(input); i++) {
		if (input[i] != '0' && input[i] != '1') {
			return false;
		}
	}
	return true;
}

bool isoctal(char *input) {
	for (size_t i = 0; i < strlen(input); i++) {
		if (input[i] == '8' || input[i] == '9') {
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		panic(NAME": at least one argument is required\n");
	}

	numtype_t optfrom = NT_UNKNOWN;
	numtype_t optto = NT_UNKNOWN;

	char *argp = NULL;
	char *input = NULL;
	for (int i = 0; i < argc; i++) {
		argp = argv[i];
		if (argp[0] != '-') {
			input = argp;
			continue;
		}
		argp++;
		if (argp[0] == '-') argp++;
		if (strcmp(argp, "from") == 0) {
			if (argc <= i+1 || argv[i+1][0] == '-') {
				panic(NAME": %s expect a value\n", argv[i]);
			}
			optfrom = parse_numtype(argv[i+1]);
			i++;
		} else if (strcmp(argp, "to") == 0) {
			if (argc <= i+1 || argv[i+1][0] == '-') {
				panic(NAME": %s expect a value\n", argv[i]);
			}
			optto = parse_numtype(argv[i+1]);
			i++;
		} else {
			panic(NAME": unknown argument %s\n", argv[i]);
		}
	}

	if (!input || input[0] == '\0') {
		panic(NAME": empty input\n");
	}

	if (optfrom == NT_BINARY && !isbinary(input)) {
		panic(NAME": input: invalid binary format\n");
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

	long num = strtol(input, 0, optfrom);
	printf("%d\t%d\n%ld\n", optfrom, optto, num);

	switch (optto) {
		case NT_BINARY:
			break;
		case NT_OCTAL:
			printf("%o\n", (unsigned int) num);
			break;
		case NT_HEX:
			printf("%x\n", (unsigned int) num);
			break;
		default: // NT_DECIMAL, NT_UNKNOWN
			printf("%ld\n", num);
			break;
	}

	return 0;
}
