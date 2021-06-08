#ifndef _UTILS_H
#define _UTILS_H

#define NAME "baseconv"

#define streq(s1, s2) (strcmp(s1, s2) == 0)

void panic(const char *format, ...);
char ctoupper(char);
char *trimnum(char *);
void printbin(long long);

#endif // _UTILS_H
