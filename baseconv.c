#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "numtype.h"
#include "utils.h"

static void usage(bool ok) {
	FILE *out = ok ? stdout : stderr;
	fprintf(out, "usage: "NAME" [options] <input>\n");
	fprintf(out, "  -from    base to convert from (binary, octal, decimal, hexadecimal).\n");
	fprintf(out, "  -to      base to convert to (binary, octal, decimal, hexadecimal).\n");
	fprintf(out, "  -help    show this message.\n");
	exit(!ok);
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		panic(": at least one argument is required");
	}

	numtype_t optfrom = NT_UNKNOWN;
	numtype_t optto = NT_UNKNOWN;

	char *argp = 0;
	char *input = 0;
	for (int i = 1; i < argc; i++) {
		argp = argv[i];
		if (!input && (argp[0] != '-' || (argp[0] == '-' && ishexadecimal(trimnum(argp))))) {
			input = argp;
			continue;
		}
		argp++;
		if (argp[0] == '-') {
			argp++;
		}
		if (streq(argp, "from")) {
			i++;
			if (argc <= i || argv[i][0] == '-') {
				panic(": -%s expects a value", argp);
			}
			optfrom = parse_numtype(argv[i]);
		} else if (streq(argp, "to")) {
			i++;
			if (argc <= i || argv[i][0] == '-') {
				panic(": -%s expects a value", argp);
			}
			optto = parse_numtype(argv[i]);
		} else if (streq(argp, "help")) {
			usage(true);
		} else {
			usage(false);
		}
	}

	if (!input || !*input) {
		panic(": empty input");
	}

	char* numstr = trimnum(input);
	if (!numstr || !*numstr) {
		panic(": invalid input");
	}

	switch (optfrom) {
	case NT_BINARY:
		if (!isbinary(numstr)) {
			panic(": input: invalid binary format");
		}
		break;
	case NT_OCTAL:
		if (!isoctal(numstr)) {
			panic(": input: invalid octal format");
		}
		break;
	case NT_DECIMAL:
		if (!isdecimal(numstr)) {
			panic(": input: invalid decimal format");
		}
		break;
	case NT_HEXADECIMAL:
		if (!ishexadecimal(numstr)) {
			panic(": input: invalid hexadecimal format");
		}
		break;
	default: // NT_UNKNOWN
		optfrom = parse_numtype_input(input);
		if (optfrom == NT_UNKNOWN) {
			panic(": input: cannot guess input type, try to set -from");
		}
		break;
	}

	long long num = strtol(numstr, 0, optfrom);

	if (num != 0 && (input[0] == '+' || input[0] == '-')) {
		putchar(input[0]);
	}

	switch (optto) {
	case NT_BINARY:
		printbin(input[0] == '-' ? -num : num);
		break;
	case NT_OCTAL:
		printf("0o%o\n", (unsigned int)num);
		break;
	case NT_HEXADECIMAL:
		printf("0x%x\n", (unsigned int)num);
		break;
	default: // NT_DECIMAL || NT_UNKNOWN
		printf("%lld\n", num);
		break;
	}

	return 0;
}
