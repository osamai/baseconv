#ifndef _UTILS_H
#define _UTILS_H

#include <stdbool.h>

#define streq(s1, s2) (strcmp(s1, s2) == 0)

void panic(const char *format, ...);

bool isbin(const char *input);
bool isoct(const char *input);
bool isdec(const char *input);
bool ishex(const char *input);

int basefromname(const char *name);
int basefrominput(const char *input);

char *trimnum(char *input);

void printbin(long long num);

#endif // _UTILS_H
