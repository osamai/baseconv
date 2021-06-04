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
			if (isdecimal(input)) {
				return NT_DECIMAL;
			}
			if (ishex(input)) {
				return NT_HEX;
			}
			return NT_UNKNOWN;
	}
}
