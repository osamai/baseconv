#ifndef _NUMTYPE_H_

typedef enum numtype {
	NT_UNKNOWN = 0,
	NT_BINARY = 2,
	NT_OCTAL = 8,
	NT_DECIMAL = 10,
	NT_HEX = 16,
} numtype_t;

numtype_t parse_numtype(const char *);
numtype_t parse_numtype_input(const char *);

#endif // _NUMTYPE_H_
