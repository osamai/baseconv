#ifndef _UTILS_H_

#include <stdbool.h>

#define streq(s1, s2) (strcmp(s1, s2) == 0)
#define panic(...) { fprintf(stderr, __VA_ARGS__); exit(1); }

int toupper(int);
char *trimnum(char *);
bool isbinary(const char *);
bool isoctal(const char *);
bool isdecimal(const char *);
bool ishex(const char *);
bool isnumber(const char *);
void printbin(long long);

#endif // _UTILS_H_
