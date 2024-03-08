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

CC      := gcc
CFLAGS  := -Wall -Wextra -pedantic -std=c2x -I $(SRCROOT)/include
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

ifeq ($(USE_SANITIZE), LEAK)
    CFLAGS += -fsanitize=leak
endif


include $(SRCROOT)/mk/os.mk
include $(SRCROOT)/mk/tools.mk

BADCOMP_DIR   := $(SRCROOT)/src
BADCOMP_BIN   := badcomp

BADCOMP_SRCS  := \
	$(BADCOMP_DIR)/ast.c \
	$(BADCOMP_DIR)/badcomp.c \
	$(BADCOMP_DIR)/fs.c \
	$(BADCOMP_DIR)/lexer.c \
	$(BADCOMP_DIR)/str.c \
	$(BADCOMP_DIR)/memory.c \
	$(BADCOMP_DIR)/token.c

BADCOMP_OBJS  := $(patsubst $(BADCOMP_DIR)/%.c, $(BADCOMP_DIR)/%.o, $(BADCOMP_SRCS))


$(BADCOMP_BIN): $(BADCOMP_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@


$(BADCOMP_DIR)/%.o: $(BADCOMP_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@


ALL     += $(BADCOMP_BIN)
CLEAN   += $(BADCOMP_OBJS) $(BADCOMP_BIN)


all: $(ALL)


build: $(BADCOMP_BIN)


clean:
	$(RM) $(CLEAN)


lint: run-clang-format run-cppcheck

format fmt: run-clang-reformat

.PHONY: $(PHONY)
