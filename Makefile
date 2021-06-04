CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Os
SRC = $(wildcard *.c)

baseconv:
	$(CC) $(CFLAGS) -o $@ $(SRC)

clean:
	rm -f baseconv

.PHONY: clean
