# Utilities
CC = gcc
GDB = gdb
DEBUGGER = $(GDB)
VALGRIND = valgrind


# Directories
BIN_DIR = bin
BUILD_DIR = build
INCLUDE_DIR = include
SRC_DIR = src
TESTS_DIR = tests
TESTS_BIN_DIR = $(TESTS_DIR)/bin
TESTS_BUILD_DIR = $(TESTS_DIR)/build
TESTS_SRC_DIR = $(TESTS_DIR)/test


# Flags and options
LDFLAGS =
INCLUDE_FLAGS = -I$(INCLUDE_DIR)
WARN_FLAGS = -Wall -Wextra
DEBUG_FLAGS = -g -O0

STATE_FLAGS = -DTESTING
ifeq ($(DEBUG), 0)
STATE_FLAGS += -DNDEBUG
endif
ifeq ($(DEBUG), 1)
STATE_FLAGS += -DDEBUG
endif

CFLAGS = $(DEBUG_FLAGS) $(WARN_FLAGS) $(STATE_FLAGS) $(INCLUDE_FLAGS) $(LDFLAGS)

TESTS_LDFLAGS = -lcriterion

TESTS_OPTS = --verbose=1 --full-stats
ifeq ($(DEBUG), 1)
TESTS_OPTS += --debug=$(DEBUGGER)
endif

VALGRIND_OPTS = --leak-check=yes --trace-children=yes


# Files

OBJ_FILES = \
	$(BUILD_DIR)/sample.o \
	$(BUILD_DIR)/sample-tree.o \
	$(BUILD_DIR)/sample-hash.o \
	$(BUILD_DIR)/utils.o

TESTS_SRC_FILES := $(wildcard $(TESTS_SRC_DIR)*.c)
TESTS_OBJ_FILES = \
	$(TESTS_BUILD_DIR)/test-criterion.o \
	$(TESTS_BUILD_DIR)/test-utils.o \
	$(TESTS_BUILD_DIR)/test-sample.o


# Targets
TESTS_TARGET = $(TESTS_BIN_DIR)/tests


# Build targets

$(BIN_DIR):
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@

$(TESTS_BUILD_DIR):
	mkdir -p $@

$(TESTS_BIN_DIR):
	mkdir -p $@


$(BUILD_DIR)/sample.o: $(SRC_DIR)/sample.c \
		$(INCLUDE_DIR)/sample.h $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/testing.h 
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

$(BUILD_DIR)/sample-tree.o: $(SRC_DIR)/sample-tree.c \
		$(INCLUDE_DIR)/sample.h $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/testing.h 
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

$(BUILD_DIR)/sample-hash.o: $(SRC_DIR)/sample-hash.c \
		$(INCLUDE_DIR)/sample.h $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/testing.h 
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

$(BUILD_DIR)/utils.o: $(SRC_DIR)/utils.c $(INCLUDE_DIR)/utils.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<


$(TESTS_BUILD_DIR)/test-criterion.o: $(TESTS_SRC_DIR)/test-criterion.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(TESTS_LDFLAGS) -c -o $@ $<

$(TESTS_BUILD_DIR)/test-utils.o: $(TESTS_SRC_DIR)/test-utils.c $(INCLUDE_DIR)/utils.h
	$(CC) $(CFLAGS) $(LDFLAGS) $(TESTS_LDFLAGS) -c -o $@ $<

$(TESTS_BUILD_DIR)/test-sample.o: $(TESTS_SRC_DIR)/test-sample.c \
	$(INCLUDE_DIR)/sample.h $(INCLUDE_DIR)/utils.h
	$(CC) $(CFLAGS) $(LDFLAGS) $(TESTS_LDFLAGS) -c -o $@ $<

$(TESTS_TARGET): $(OBJ_FILES) $(TESTS_OBJ_FILES) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(TESTS_LDFLAGS) -o $@ $^
	 chmod 777 $@


# Phony targets

.PHONY: all build-tests test debug check-memory-tests clean \

all: build-tests

build-tests: $(TESTS_DIR) $(TESTS_BUILD_DIR) $(TESTS_BIN_DIR) $(TESTS_TARGET)

test: build-tests
	$(TESTS_TARGET) $(TESTS_OPTS)

debug: build_tests
	$(GDB) -q $(TESTS_TARGET)

check-memory-tests: $(TESTS_TARGET)
	$(VALGRIND) $(VALGRIND_OPTS) ./$<

clean:
	rm -f ./*.o ./*.exe $(BIN_DIR)/* $(BUILD_DIR)/* $(TESTS_BIN_DIR)/* $(TESTS_BUILD_DIR)/*