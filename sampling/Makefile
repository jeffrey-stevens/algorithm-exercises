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


# Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS = $(wildcard $(TESTS_SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:$(TESTS_SRC_DIR)/%.c=$(TESTS_BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)
TEST_DEPS = $(TEST_OBJS:.o=.d)


# Flags and options
DEBUG_FLAGS = -g -O0
WARN_FLAGS = -Wall -Wextra
DEP_FLAGS = -MMD -MP
LDFLAGS = 
LDLIBS =
INCLUDE_FLAGS = -I$(INCLUDE_DIR)

STATE_FLAGS = 
ifeq ($(DEBUG), 0)
STATE_FLAGS += -DNDEBUG
endif
ifeq ($(DEBUG), 1)
STATE_FLAGS += -DDEBUG
endif

CFLAGS = $(DEBUG_FLAGS) $(WARN_FLAGS) $(DEP_FLAGS)
CPPFLAGS =  $(STATE_FLAGS) $(INCLUDE_FLAGS)

TESTING_CPPFLAGS = -DTESTING
TESTING_LDLIBS = -lcriterion

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
	$(BUILD_DIR)/sample-replace.o \
	$(BUILD_DIR)/permute.o \
	$(BUILD_DIR)/utils.o \
	$(BUILD_DIR)/error.o

TESTS_SRC_FILES := $(wildcard $(TESTS_SRC_DIR)*.c)
TESTS_OBJ_FILES = \
	$(TESTS_BUILD_DIR)/test-criterion.o \
	$(TESTS_BUILD_DIR)/test-utils.o \
	$(TESTS_BUILD_DIR)/test-sample.o \
	$(TESTS_BUILD_DIR)/test-sample-replace.o \
	$(TESTS_BUILD_DIR)/test-permute.o \
	$(TESTS_BUILD_DIR)/test-validate.o


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


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -MF $(BUILD_DIR)/$*.d -o $@ $<


# $(BUILD_DIR)/sample.o: $(SRC_DIR)/sample.c \
# 		$(INCLUDE_DIR)/sample.h $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/testing.h 
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -c -o $@ $<

# $(BUILD_DIR)/sample-tree.o: $(SRC_DIR)/sample-tree.c \
# 		$(INCLUDE_DIR)/sample.h $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/testing.h 
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -c -o $@ $<

# $(BUILD_DIR)/sample-hash.o: $(SRC_DIR)/sample-hash.c \
# 		$(INCLUDE_DIR)/sample.h $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/testing.h 
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -c -o $@ $<

# $(BUILD_DIR)/sample-replace.o: $(SRC_DIR)/sample-replace.c \
# 		$(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/validate.h $(INCLUDE_DIR)/error.h 
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -c -o $@ $<

# $(BUILD_DIR)/permute.o: $(SRC_DIR)/permute.c \
# 		$(INCLUDE_DIR)/permute.h
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -c -o $@ $<

# $(BUILD_DIR)/utils.o: $(SRC_DIR)/utils.c $(INCLUDE_DIR)/utils.h
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -c -o $@ $<

# $(BUILD_DIR)/error.o: $(SRC_DIR)/error.c $(INCLUDE_DIR)/error.h
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -c -o $@ $<


$(TESTS_BUILD_DIR)/%.o: $(TESTS_SRC_DIR)/%.c | $(TESTS_BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -MF $(TESTS_BUILD_DIR)/$*.d \
		$(TESTING_CPPFLAGS) -o $@ $<

# $(TESTS_BUILD_DIR)/test-criterion.o: $(TESTS_SRC_DIR)/test-criterion.c
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $(TESTING_CPPFLAGS) $(LDFLAGS) -c -o $@ $<

# $(TESTS_BUILD_DIR)/test-utils.o: $(TESTS_SRC_DIR)/test-utils.c $(INCLUDE_DIR)/utils.h
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $(TESTING_CPPFLAGS) $(LDFLAGS) -c -o $@ $<

# $(TESTS_BUILD_DIR)/test-sample.o: $(TESTS_SRC_DIR)/test-sample.c \
# 		$(INCLUDE_DIR)/sample.h $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/error.h
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $(TESTING_CPPFLAGS) $(LDFLAGS) -c -o $@ $<

# $(TESTS_BUILD_DIR)/test-sample-replace.o: $(TESTS_SRC_DIR)/test-sample-replace.c \
# 		$(INCLUDE_DIR)/sample.h $(INCLUDE_DIR)/utils.h
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $(TESTING_CPPFLAGS) $(LDFLAGS) -c -o $@ $<

# $(TESTS_BUILD_DIR)/test-permute.o: $(TESTS_SRC_DIR)/test-permute.c \
# 		$(INCLUDE_DIR)/permute.h $(INCLUDE_DIR)/internal/permute.h \
# 		$(INCLUDE_DIR)/utils.h
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $(TESTING_CPPFLAGS) $(LDFLAGS) -c -o $@ $<

# $(TESTS_BUILD_DIR)/test-validate.o: $(TESTS_SRC_DIR)/test-validate.c \
# 		$(INCLUDE_DIR)/validate.h $(INCLUDE_DIR)/utils.h $(INCLUDE_DIR)/error.h
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $(TESTING_CPPFLAGS) $(LDFLAGS) -c -o $@ $<

# This is only for debugging...
$(TESTS_BIN_DIR)/test-validate: \
		$(TESTS_BUILD_DIR)/test-validate.o \
		$(BUILD_DIR)/utils.o \
		$(BUILD_DIR)/error.o
	$(CC) $(LDFLAGS) $(LDLIBS) $(TESTING_LDLIBS) -o $@ $^
	 chmod 777 $@

$(TESTS_BIN_DIR)/test-sample-replace: \
		$(TESTS_BUILD_DIR)/test-sample-replace.o \
		$(BUILD_DIR)/sample-replace.o \
		$(BUILD_DIR)/utils.o \
		$(BUILD_DIR)/error.o
	$(CC) $(LDFLAGS) $(LDLIBS) $(TESTING_LDLIBS) -o $@ $^
	 chmod 777 $@

$(TESTS_TARGET): $(OBJ_FILES) $(TESTS_OBJ_FILES) 
	$(CC) $(LDFLAGS) $(LDLIBS) $(TESTING_LDLIBS) -o $@ $^
	 chmod 777 $@


# $(info TEST_SRCS is $(TEST_SRCS))
# $(info TEST_OBJS is $(TEST_OBJS))
# $(info DEPS is $(DEPS))
# $(info TEST_DEPS is $(TEST_DEPS))

-include $(DEPS) $(TEST_DEPS)


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