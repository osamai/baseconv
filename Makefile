CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -O2
SRC = $(wildcard *.c)

DESTDIR ?= /usr/local

baseconv:
	$(CC) $(CFLAGS) -o $@ $(SRC)

clean:
	rm -f baseconv

install: baseconv
	mkdir -p $(DESTDIR)/bin
	cp -f baseconv $(DESTDIR)/bin
	chmod 755 $(DESTDIR)/bin/baseconv

uninstall:
	rm -f $(DESTDIR)/bin/baseconv

.PHONY: clean install uninstall
