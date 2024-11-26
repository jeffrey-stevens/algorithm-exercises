CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -DTESTING
LDFLAGS =
TEST_LDFLAGS = -lcriterion
VALGRIND = valgrind
VALGRIND_OPTS = --leak-check=yes


.PHONY: all build

all: build

build: sample-test

# sample-test: sample.o test.o
# 	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
# 	chmod 777 sample-test

sample-test: sample.o test-criterion.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(TEST_LDFLAGS) -o $@ $^
	chmod 777 sample-test

sample.o: sample.c sample.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

test.o: test.c sample.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

test-criterion.o: test-criterion.c sample.h
	$(CC) $(CFLAGS) $(LDFLAGS) $(TEST_LDFLAGS) -c -o $@ $<

run: sample-test
	./sample-test

check-memory: sample-test
	$(VALGRIND) $(VALGRIND_OPTS) ./$<

clean:
	rm -f ./*.o ./*.exe