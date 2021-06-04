#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "numtype.h"
#include "utils.h"

#define NAME "baseconv"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		panic(NAME": at least one argument is required\n");
	}

	numtype_t optfrom = NT_UNKNOWN;
	numtype_t optto = NT_UNKNOWN;

	char *argp = 0;
	char *input = 0;
	for (int i = 1; i < argc; i++) {
		argp = argv[i];
		if (argp[0] != '-' || (argp[0] == '-' && isnumber(skipprefix(argp)))) {
			input = argp;
			continue;
		}
		if (argp[0] == '-') {
			argp++;
		}
		if (streq(argp, "f") || streq(argp, "from")) {
			if (argc <= i+1 || argv[i+1][0] == '-') {
				panic(NAME": %s expect a value\n", argv[i]);
			}
			optfrom = parse_numtype(argv[i+1]);
			i++;
		} else if (streq(argp, "t") || streq(argp, "to")) {
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
	if (optfrom == NT_DECIMAL && !isdecimal(input)) {
		panic(NAME": input: invalid decimal format\n");
	}
	if (optfrom == NT_HEX && !ishex(input)) {
		panic(NAME": input: invalid hexadecimal format\n");
	}

	char prefix = 0;
	if (input[0] == '+' || input[0] == '-') {
		prefix = input[0];
	}

	if (optfrom == NT_UNKNOWN) {
		optfrom = parse_numtype_input(input);
	}

	long long num = strtol(skipprefix(input), 0, optfrom);

	switch (optto) {
		case NT_BINARY:
			printbin(prefix == '-' ? -num : num);
			break;
		case NT_OCTAL:
			printf("%c0o%o\n", prefix, (unsigned int)num);
			break;
		case NT_HEX:
			printf("%c0x%x\n", prefix, (unsigned int)num);
			break;
		default: // NT_DECIMAL || NT_UNKNOWN
			printf("%c%lld\n", prefix, num);
			break;
	}

	return 0;
}
