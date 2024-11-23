CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -dTESTING


.PHONY: all build

all: build

build: sample-test.exe

sample-test.exe: sample.o test.o
	$(CC) $(CFLAGS) -o $@ $<

sample.o: sample.c sample.h
	$(CC) $(CFLAGS) -c -o $@ $<

test.o: test.c sample.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm ./*.o ./*.exe