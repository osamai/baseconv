#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdbool.h>

#define NAME "baseconv"

#define streq(s1, s2) (strcmp(s1, s2) == 0)

void panic(const char *format, ...);
int toupper(int);
char *trimnum(char *);
bool isbinary(const char *);
bool isoctal(const char *);
bool isdecimal(const char *);
bool ishex(const char *);
bool isnumber(const char *);
void printbin(long long);

#endif // _UTILS_H_
