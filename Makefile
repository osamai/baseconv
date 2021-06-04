CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Os

baseconv:
	$(CC) $(CFLAGS) -o $@ $@.c
