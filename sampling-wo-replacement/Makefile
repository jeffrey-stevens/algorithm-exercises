CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -DTESTING


.PHONY: all build

all: build

build: sample-test

sample-test: sample.o test.o
	$(CC) $(CFLAGS) -o $@ $^
	chmod 777 sample-test

sample.o: sample.c sample.h
	$(CC) $(CFLAGS) -c -o $@ $<

test.o: test.c sample.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm ./*.o ./*.exe