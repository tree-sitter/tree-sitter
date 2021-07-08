VERSION := 0.6.3

# install directory layout
PREFIX ?= /usr/local
INCLUDEDIR ?= $(PREFIX)/include
LIBDIR ?= $(PREFIX)/lib
PCLIBDIR ?= $(LIBDIR)/pkgconfig

# collect sources
ifneq ($(AMALGAMATED),1)
	SRC := $(wildcard lib/src/*.c)
	# do not double-include amalgamation
	SRC := $(filter-out lib/src/lib.c,$(SRC))
else
	# use amalgamated build
	SRC := lib/src/lib.c
endif
OBJ := $(SRC:.c=.lo)

# define default flags, and override to append mandatory flags
CFLAGS ?= -O3 -Wall -Wextra -Werror
override CFLAGS += -std=gnu99 -Ilib/src -Ilib/include

# ABI versioning
LT_CURRENT := 0
LT_REVISION := 0
LT_AGE := 0

# OS-specific bits
ifneq (,$(filter $(shell uname),FreeBSD NetBSD DragonFly))
	PCLIBDIR := $(PREFIX)/libdata/pkgconfig
endif

all: libtree-sitter.la

%.lo : %.c
	libtool --mode=compile --tag=CC $(CC) $(CFLAGS) -o $@ -c $^

libtree-sitter.la: $(OBJ)
	libtool --mode=link --tag=CC $(CC) $(LDFLAGS) \
		-rpath '$(LIBDIR)' -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
		-o $@ $^ $(LDLIBS)

install: all
	libtool --mode=install install -Dm644 libtree-sitter.la '$(DESTDIR)$(LIBDIR)'/libtree-sitter.la
	libtool --mode=finish '$(DESTDIR)$(LIBDIR)'
	install -Dm644 lib/include/tree_sitter/*.h -t '$(DESTDIR)$(INCLUDEDIR)'/tree_sitter/
	install -d '$(DESTDIR)$(PCLIBDIR)'
	sed -e 's|@LIBDIR@|$(LIBDIR)|;s|@INCLUDEDIR@|$(INCLUDEDIR)|;s|@VERSION@|$(VERSION)|' \
	    -e 's|=$(PREFIX)|=$${prefix}|' \
	    -e 's|@PREFIX@|$(PREFIX)|' \
	    tree-sitter.pc.in > '$(DESTDIR)$(PCLIBDIR)'/tree-sitter.pc

clean:
	libtool --mode=clean rm $(OBJ) libtree-sitter.la

.PHONY: all install clean
