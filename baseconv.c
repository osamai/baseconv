#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

static void printusage(void) {
	puts(
			"usage: baseconv [options] <input>\n"
			"  -from    base to convert from binary, octal, decimal, hexadecimal.\n"
			"  -to      base to convert to binary, octal, decimal, hexadecimal.\n"
			"  -help    show this message.\n"
			);
}

int main(int argc, char *argv[]) {
	if (argc == 1)
		panic(": at least one argument is required");

	int to = 0;
	int from = 0;
	char *input = 0;

	while (argc > 1) {
		argc--; argv++;
		if (*argv[0] != '-' || (*argv[0] == '-' && ishex(trimnum(*argv)))) {
			input = *argv;
			continue;
		}
		if (argv[0][0] == '-' && argv[0][1] == '-')
			argv[0]++;
		if (streq(*argv, "-to") || streq(*argv, "-from")) {
			if (argc == 1 || *argv[1] == '-')
				panic(": -%s expects a value", *argv);
			int b = basefromname(argv[1]);
			if (b == 0)
				panic(": %s: invalid base", argv[1]);
			if (argv[0][1] == 't')
				to = b;
			else
				from = b;
			argc--; argv++;
		} else if (streq(*argv, "-help")) {
			printusage();
			return 0;
		} else {
			printusage();
			return 1;
		}
	}

	if (!input || !*input)
		panic(": empty input");

	char* numstr = trimnum(input);
	if (!numstr || !*numstr)
		panic(": invalid input");

	if (!from) {
		from = basefrominput(input);
		if (!from)
			panic(": cannot guess input type, try to set -from");
	}

	switch (from) {
	case 2:
		if (!isbin(numstr))
			panic(": invalid binary format");
		break;
	case 8:
		if (!isoct(numstr))
			panic(": invalid octal format");
		break;
	case 10:
		if (!isdec(numstr))
			panic(": invalid decimal format");
		break;
	case 16:
		if (!ishex(numstr))
			panic(": invalid hexadecimal format");
		break;
	}

	unsigned long long num = strtoull(numstr, 0, from);

	if (num != 0 && (*input == '+' || *input == '-'))
		putchar(*input);

	switch (to) {
	case 2:
		printbin(num);
		break;
	case 8:
		printf("0o%o\n", (unsigned int)num);
		break;
	case 16:
		printf("0x%x\n", (unsigned int)num);
		break;
	default: // 10 || unknown
		printf("%llu\n", num);
		break;
	}

	return 0;
}
