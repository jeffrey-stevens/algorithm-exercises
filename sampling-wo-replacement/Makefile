CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -DTESTING
VALGRIND = valgrind
VALGRIND_OPTS = --leak-check=yes


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

run: sample-test
	./sample-test

check-memory: sample-test
	$(VALGRIND) $(VALGRIND_OPTS) ./$<

clean:
	rm -f ./*.o ./*.exe