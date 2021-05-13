CC ?= cc
CFLAGS = -Wall -Wextra

baseconv:
	$(CC) $(CFLAGS) -o $@ $@.c
