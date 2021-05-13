#include <stdio.h>
#include <stdlib.h>
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
	if (strcmp(s, "binary")) {
		return NT_BINARY;
	} else if (strcmp(s, "octal") == 0) {
		return NT_OCTAL;
	} else if (strcmp(s, "decimal") == 0) {
		return NT_DECIMAL;
	} else if (strcmp(s, "hex") == 0) {
		return NT_HEX;
	}
	return NT_UNKNOWN;
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

	return 0;
}
