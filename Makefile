

PHONY := \
	default all build \
	format fmt lint \
	test tests \
	clean

ALL   :=
CLEAN :=

THIS_MAKE_FILE     := $(abspath $(lastword $(MAKEFILE_LIST)))
THIS_MAKE_FILE_DIR := $(realpath $(patsubst %/,%,$(dir $(THIS_MAKE_FILE))))

SRCROOT  := $(THIS_MAKE_FILE_DIR)


default: all


# ============== [ COMPILATION ] ==============
#
CC      := gcc
CFLAGS  := -Wall -Wextra -pedantic -std=c11 -I $(SRCROOT)/include
LDFLAGS :=

ifeq ($(BUILD_CONFIG), DEBUG)
    CFLAGS += -O0 -g -D CONFIG_DEBUG
else
    CFLAGS += -Werror -O2 -D CONFIG_RELEASE
endif

ifeq ($(USE_SANITIZE), ADDRESS)
   CFLAGS += -fsanitize=address
endif

ifeq ($(USE_SANITIZE), UNDEFINE)
    CFLAGS += -fsanitize=undefine
endif


include $(SRCROOT)/make/os.mk
include $(SRCROOT)/make/tools.mk


# ================== [ BADCOMP ] ===================
#
#
BADCOMP_DIR   := $(SRCROOT)/src
BADCOMP_BIN   := badcomp

BADCOMP_SRCS  := \
	$(BADCOMP_DIR)/badcomp.c \
	$(BADCOMP_DIR)/fs.c \
	$(BADCOMP_DIR)/lexer.c \
	$(BADCOMP_DIR)/str.c \
	$(BADCOMP_DIR)/token.c

BADCOMP_OBJS  := $(patsubst $(BADCOMP_DIR)/%.c, $(BADCOMP_DIR)/%.o, $(BADCOMP_SRCS))


$(BADCOMP_BIN): $(BADCOMP_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@


$(BADCOMP_DIR)/%.o: $(BADCOMP_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@


ALL     += $(BADCOMP_BIN)
CLEAN   += $(BADCOMP_OBJS) $(BADCOMP_BIN)


# ================== [ UNIT TESTING ] ===================
#
#
TEST_DIR  := $(BADCOMP_DIR)/tests
TEST_SRCS :=

TEST_BINS := $(patsubst $(TEST_DIR)/%.c, $(TEST_DIR)/%.bin, $(TEST_SRCS))

CLEAN += $(TEST_BINS)

TEST_CFLAGS := $(shell pkg-config --cflags --libs check)

$(TEST_DIR)/%: $(TEST_DIR)/%.c $(BADCOMP_BIN)
	$(CC) $(CFLAGS) $^ -o $@ $(TEST_CFLAGS)


all: $(ALL)


build: $(BADCOMP_BIN)


tests: $(TEST_BINS)


test: $(TEST_BINS)
	@for test in $(TEST_BINS); do $$test ; done


clean:
	$(RM) $(CLEAN)


lint: run-clang-format run-cppcheck

format fmt: run-clang-reformat

.PHONY: $(PHONY)
