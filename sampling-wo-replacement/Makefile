CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -DTESTING
LDFLAGS =
TEST_LDFLAGS = -lcriterion
VALGRIND = valgrind
VALGRIND_OPTS = --leak-check=yes

BINDIR = bin/
BUILDDIR = build/

TARGET = $(BINDIR)sample-test
TEST_TARGET = $(BINDIR)tests


.PHONY: all build build-tests

all: build build-tests

build: $(BUILDDIR) $(BINDIR) $(TARGET)

build-tests: $(BUILDDIR) $(BINDIR) $(TEST_TARGET)

$(BINDIR):
	mkdir -p $@

$(BUILDDIR):
	mkdir -p $@

# sample-test: sample.o test.o
# 	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
# 	chmod 777 sample-test

$(TARGET): $(BUILDDIR)sample.o $(BUILDDIR)test-criterion.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(TEST_LDFLAGS) -o $@ $<
	 chmod 777 $@

$(BUILDDIR)sample.o: sample.c sample.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

$(BUILDDIR)test.o: test.c sample.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

$(BUILDDIR)test-criterion.o: test-criterion.c sample.h
	$(CC) $(CFLAGS) $(LDFLAGS) $(TEST_LDFLAGS) -c -o $@ $<

$(TEST_TARGET): $(BUILDDIR)test-criterion.o $(BUILDDIR)sample.o 
	$(CC) $(CFLAGS) $(LDFLAGS) $(TEST_LDFLAGS) -o $@ $^
	 chmod 777 $@

run: build
	$(TARGET)

run-tests: build-tests
	$(TEST_TARGET)

# check-memory: $(TARGET)
# 	$(VALGRIND) $(VALGRIND_OPTS) ./$<

check-memory: $(TEST_TARGET)
	$(VALGRIND) $(VALGRIND_OPTS) ./$<

clean:
	rm -f ./*.o ./*.exe $(BINDIR)* $(BUILDDIR)*