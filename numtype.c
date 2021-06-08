#include <string.h>
#include "numtype.h"
#include "utils.h"

numtype_t parse_numtype(const char *s) {
	if (streq(s, "bin") || streq(s, "binary")) {
		return NT_BINARY;
	} else if (streq(s, "oct") || streq(s, "octal")) {
		return NT_OCTAL;
	} else if (streq(s, "dec") || streq(s, "decimal")) {
		return NT_DECIMAL;
	} else if (streq(s, "hex") || streq(s, "hexadecimal")) {
		return NT_HEXADECIMAL;
	}
	return NT_UNKNOWN;
}

numtype_t parse_numtype_input(const char *input) {
	if (input[0] == '+' || input[0] == '-') {
		input++;
	}
	for (; input[0] == '0'; input++);
	switch (ctoupper(input[0])) {
	case 'B':
		return NT_BINARY;
	case 'O':
		return NT_OCTAL;
	case 'X':
		return NT_HEXADECIMAL;
	default:
		if (isdecimal(input)) {
			return NT_DECIMAL;
		}
		if (ishexadecimal(input)) {
			return NT_HEXADECIMAL;
		}
		return NT_UNKNOWN;
	}
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

bool isdecimal(const char *input) {
	for (size_t i = 0; i < strlen(input); i++) {
		if (input[i] < '0' || input[i] > '9') {
			return false;
		}
	}
	return true;
}

bool ishexadecimal(const char *input) {
	for (size_t i = 0; i < strlen(input); i++) {
		char c = ctoupper(input[i]);
		if (c < '0' || (c > '9' && c < 'A') || c > 'F') {
			return false;
		}
	}
	return true;
}
