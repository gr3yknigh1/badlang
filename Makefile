

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
CC      := clang++
CFLAGS  := -Wall -Wextra -pedantic -std=c++20 -I $(SRCROOT)/include
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


include $(SRCROOT)/make/os.mk
include $(SRCROOT)/make/tools.mk


# ================== [ BADCOMP ] ===================
#
#
BADCOMP_DIR   := $(SRCROOT)/src
BADCOMP_BIN   := badcomp

BADCOMP_SRCS  := \
	$(BADCOMP_DIR)/ast.cpp \
	$(BADCOMP_DIR)/badcomp.cpp \
	$(BADCOMP_DIR)/fs.cpp \
	$(BADCOMP_DIR)/lexer.cpp \
	$(BADCOMP_DIR)/str.cpp \
	$(BADCOMP_DIR)/memory.cpp \
	$(BADCOMP_DIR)/Token.cpp

BADCOMP_OBJS  := $(patsubst $(BADCOMP_DIR)/%.cpp, $(BADCOMP_DIR)/%.o, $(BADCOMP_SRCS))


$(BADCOMP_BIN): $(BADCOMP_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@


$(BADCOMP_DIR)/%.o: $(BADCOMP_DIR)/%.cpp
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
