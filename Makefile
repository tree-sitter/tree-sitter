.PHONY: all clean install install-dev test test-c test-scm valgrind

### install configuration ###
CPP       = c++
RM        ?= rm -f
INSTALL   ?= install
MKDIR     ?= $(INSTALL) -d
SYMLINK   ?= ln -s

PREFIX    ?= /usr/local
BINDIR    ?= $(PREFIX)/bin
LIBDIR    ?= $(PREFIX)/lib
SOLIBDIR  ?= $(PREFIX)/lib
INCDIR    ?= $(PREFIX)/include
MODDIR    ?= $(PREFIX)/share
BINMODDIR ?= $(PREFIX)/lib
MANDIR    ?= $(PREFIX)/share/man/man1

### library configuration ###
LIB_NAME    = tree_sitter
DIR         = $(shell pwd)
HEADERS     = $(wildcard include/*.h)
SOURCES     = $(wildcard src/*.cpp)
TESTS       = $(wildcard spec/*.cpp)
OBJECTS     = $(foreach file, $(C_SOURCES), $(basename $(file)).o)
LIB_FILE    = lib$(LIB_NAME)$(SO)
TEST_BIN    = spec/run.out

### build configuration ###
CFLAGS ?= -Wall -std=c++11 -stdlib=libc++ -g -m64

### targets ###
all: $(LIB_FILE)

src/%.o: src/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

test: $(TEST_BIN)
	./$<

$(TEST_BIN): $(TESTS) $(SOURCES)
	$(CPP) $(CFLAGS) -Ispec/externals/igloo -Isrc -L. $^ -o $@

# $(TEST_BIN): $(LIB_FILE) $(C_TESTS)
	# $(CPP) $(CFLAGS) -Ispec/externals/igloo -Isrc -L. -l$(LIB_NAME) test/c/_runner.cc -o $@

debug: $(TEST_BIN)
	gdb $<

valgrind: $(TEST_BIN)
	valgrind --track-origins=yes $(TEST_BIN)

clean:
	$(RM) $(OBJECTS) $(LIB_FILE) $(TEST_BIN)

