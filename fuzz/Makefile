# Makefile for tree-sitter fuzz targets
#
# Prerequisites:
#   - Build tree-sitter: make -C .. (produces libtree-sitter.a)
#   - Optionally build grammar libraries for richer coverage
#
# Usage:
#   make                  # build all fuzz targets
#   make fuzz_parser      # build just the parser fuzzer
#   ./fuzz_parser corpus/ # run with a corpus directory
#
# For OSS-Fuzz / ClusterFuzz integration, the targets are built via
# the OSS-Fuzz build.sh script which handles compiler flags, sanitizers,
# and grammar linking automatically.

CC      ?= clang
CFLAGS  ?= -g -fsanitize=fuzzer,address
CFLAGS  += -I../lib/include -D_DEFAULT_SOURCE
LDFLAGS ?=

# Path to libtree-sitter.a (built via 'make' in the repo root)
TS_LIB  ?= ../libtree-sitter.a

# Optional: grammar libraries for richer fuzz coverage
# Set these to the paths of the built grammar .a files
JSON_LIB ?=
HTML_LIB ?=
JS_LIB   ?=

GRAMMAR_CFLAGS :=
GRAMMAR_LIBS   :=

ifneq ($(JSON_LIB),)
  GRAMMAR_CFLAGS += -DFUZZ_HAS_JSON
  GRAMMAR_LIBS   += $(JSON_LIB)
endif
ifneq ($(HTML_LIB),)
  GRAMMAR_CFLAGS += -DFUZZ_HAS_HTML
  GRAMMAR_LIBS   += $(HTML_LIB)
endif
ifneq ($(JS_LIB),)
  GRAMMAR_CFLAGS += -DFUZZ_HAS_JAVASCRIPT
  GRAMMAR_LIBS   += $(JS_LIB)
endif

TARGETS := fuzz_parser fuzz_query

.PHONY: all clean

all: $(TARGETS)

fuzz_parser: fuzz_parser.c $(TS_LIB)
	$(CC) $(CFLAGS) $(GRAMMAR_CFLAGS) $< $(TS_LIB) $(GRAMMAR_LIBS) $(LDFLAGS) -o $@

fuzz_query: fuzz_query.c $(TS_LIB)
	$(CC) $(CFLAGS) $(GRAMMAR_CFLAGS) $< $(TS_LIB) $(GRAMMAR_LIBS) $(LDFLAGS) -o $@

clean:
	rm -f $(TARGETS)
