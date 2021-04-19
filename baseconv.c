#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME "baseconv"
#define eprintf(msg, ...) fprintf(stderr, NAME": "msg, __VA_ARGS__)
#define eprintln(msg) fprintf(stderr, NAME": "msg"\n")

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
		eprintln("at least one argument is required");
		exit(EXIT_FAILURE);
	}

	enum numtype fromtype = NT_UNKNOWN;
	enum numtype totype = NT_UNKNOWN;

	for (int i = 0; i < argc; i++) {
		char *s = argv[i];
		if (argv[i][0] == '-') {
			s++;
			// skip second dash
			if (argv[i][1] == '-') s++;
			if (strcmp(s, "from") == 0) {
				fromtype = numtype_parse(argv[i+1]);
				i++;
			} else if (strcmp(s, "to") == 0) {
				totype = numtype_parse(argv[i+1]);
				i++;
			}
		}
	}

	return EXIT_SUCCESS;
}
