#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NAME "baseconv"

#define streq(s1, s2) (strcmp(s1, s2) == 0)
#define panic(...) { fprintf(stderr, __VA_ARGS__); exit(1); }

#ifndef toupper
int toupper(int c) {
  if (c < 'a' || c > 'z') {
    return c;
  }
  return c - 'a' + 'A';
}
#endif // toupper

char* skipprefix(char *input) {
	if (input[0] == '+' || input[0] == '-') {
		input++;
	}
	if (input[0] == '0') {
		input++;
	}
	char c = toupper(input[0]);
	if (c == 'B' || c == 'O' || c == 'X') {
		input++;
	}
	return input;
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

bool ishex(const char *input) {
	for (size_t i = 0; i < strlen(input); i++) {
		if (input[i] < '0' || toupper(input[i]) > 'F') {
			return false;
		}
	}
	return true;
}

bool isnumber(const char *input) {
	for (size_t i = 0; i < strlen(input); i++) {
		if (input[i] < '0' || toupper(input[i]) > 'F') {
			return false;
		}
	}
	return true;
}

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

numtype_t parse_numtype_input(const char *input) {
	if (input[0] == '+' || input[0] == '-'){
		input++;
	}
	if (input[0] == '0') {
		input++;
	}
	switch (toupper(input[0])) {
		case 'B':
			return NT_BINARY;
		case 'O':
			return NT_OCTAL;
		case 'X':
			return NT_HEX;
		default:
			if (isbinary(input)) {
				return NT_BINARY;
			}
			if (isoctal(input)) {
				return NT_OCTAL;
			}
			if (ishex(input)) {
				return NT_HEX;
			}
			return NT_DECIMAL;
	}
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

	printf("optfrom: %d\noptto: %d\n", optfrom, optto);
	printf("input: %s  %s\n", input, skipprefix(input));

	long long num = strtol(skipprefix(input), 0, optfrom);
	printf("num: %lld\n", num);

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
