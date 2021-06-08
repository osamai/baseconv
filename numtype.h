#ifndef _NUMTYPE_H
#define _NUMTYPE_H

#include <stdbool.h>

typedef enum numtype {
	NT_UNKNOWN = 0,
	NT_BINARY = 2,
	NT_OCTAL = 8,
	NT_DECIMAL = 10,
	NT_HEXADECIMAL = 16,
} numtype_t;

numtype_t parse_numtype(const char *);
numtype_t parse_numtype_input(const char *);

bool isbinary(const char *);
bool isoctal(const char *);
bool isdecimal(const char *);
bool ishexadecimal(const char *);

#endif // _NUMTYPE_H
