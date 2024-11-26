CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -DTESTING
LDFLAGS =
TEST_LDFLAGS = -lcriterion
VALGRIND = valgrind
VALGRIND_OPTS = --leak-check=yes

BINDIR = bin/
BUILDDIR = build/

TARGET = $(BINDIR)sample-test


.PHONY: all build

all: build

build: $(BUILDDIR) $(BINDIR) $(TARGET)

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

run: build
	$(TARGET)

check-memory: $(TARGET)
	$(VALGRIND) $(VALGRIND_OPTS) ./$<

clean:
	rm -f ./*.o ./*.exe $(BINDIR)* $(BUILDDIR)*