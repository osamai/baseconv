#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME "nbc"
#define panic(...) { fprintf(stderr, __VA_ARGS__); exit(1); }

enum numtype {
	NT_UNKNOWN,
	NT_BINARY,
	NT_OCTAL,
	NT_DECIMAL,
	NT_HEX,
};

enum numtype numtype_parse(char *s) {
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

	enum numtype fromtype = NT_UNKNOWN;
	enum numtype totype = NT_UNKNOWN;

	char *argp = NULL;
	for (int i = 0; i < argc; i++) {
		argp = argv[i];
		if (argp[0] == '-') {
			argp++;
			if (argp[0] == '-') argp++;
			if (strcmp(argp, "from") == 0) {
				if (argc <= i+1 || argv[i+1][0] == '-') {
					panic(NAME": %s expect a value\n", argv[i]);
				}
				fromtype = numtype_parse(argv[i+1]);
				i++;
			} else if (strcmp(argp, "to") == 0) {
				if (argc <= i+1 || argv[i+1][0] == '-') {
					panic(NAME": %s expect a value\n", argv[i]);
				}
				totype = numtype_parse(argv[i+1]);
				i++;
			} else {
				panic(NAME": unknown argument %s\n", argv[i]);
			}
		}
	}

	return 0;
}
