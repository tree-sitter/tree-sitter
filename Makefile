VERSION := 0.20.10

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
OBJ := $(SRC:.c=.o)

# define default flags, and override to append mandatory flags
override CFLAGS := -O3 -std=gnu99 -fPIC -fvisibility=hidden -Wall -Wextra -Wshadow $(CFLAGS)
override CFLAGS += -Ilib/src -Ilib/include

# ABI versioning
SONAME_MAJOR := 0
SONAME_MINOR := 0

# OS-specific bits
ifeq ($(shell uname),Darwin)
	SOEXT = dylib
	SOEXTVER_MAJOR = $(SONAME_MAJOR).dylib
	SOEXTVER = $(SONAME_MAJOR).$(SONAME_MINOR).dylib
	LINKSHARED += -dynamiclib -Wl,-install_name,$(LIBDIR)/libtree-sitter.$(SONAME_MAJOR).dylib
else
	SOEXT = so
	SOEXTVER_MAJOR = so.$(SONAME_MAJOR)
	SOEXTVER = so.$(SONAME_MAJOR).$(SONAME_MINOR)
	LINKSHARED += -shared -Wl,-soname,libtree-sitter.so.$(SONAME_MAJOR)
endif
ifneq (,$(filter $(shell uname),FreeBSD NetBSD DragonFly))
	PCLIBDIR := $(PREFIX)/libdata/pkgconfig
endif

all: libtree-sitter.a libtree-sitter.$(SOEXTVER)

libtree-sitter.a: $(OBJ)
	$(AR) rcs $@ $^

libtree-sitter.$(SOEXTVER): $(OBJ)
	$(CC) $(LDFLAGS) $(LINKSHARED) $^ $(LDLIBS) -o $@
	ln -sf $@ libtree-sitter.$(SOEXT)
	ln -sf $@ libtree-sitter.$(SOEXTVER_MAJOR)
ifneq ($(STRIP),)
	$(STRIP) $@
endif

install: all
	sed -e 's|@LIBDIR@|$(LIBDIR)|;s|@INCLUDEDIR@|$(INCLUDEDIR)|;s|@VERSION@|$(VERSION)|' \
	    -e 's|=$(PREFIX)|=$${prefix}|' \
	    -e 's|@PREFIX@|$(PREFIX)|' \
	    tree-sitter.pc.in > tree-sitter.pc

	install -d '$(DESTDIR)$(LIBDIR)'
	install -m644 libtree-sitter.a '$(DESTDIR)$(LIBDIR)'/
	install -m755 libtree-sitter.$(SOEXTVER) '$(DESTDIR)$(LIBDIR)'/
	ln -sf libtree-sitter.$(SOEXTVER) '$(DESTDIR)$(LIBDIR)'/libtree-sitter.$(SOEXTVER_MAJOR)
	ln -sf libtree-sitter.$(SOEXTVER) '$(DESTDIR)$(LIBDIR)'/libtree-sitter.$(SOEXT)

	install -d '$(DESTDIR)$(INCLUDEDIR)'/tree_sitter
	install -m644 lib/include/tree_sitter/api.h '$(DESTDIR)$(INCLUDEDIR)'/tree_sitter/

	install -d '$(DESTDIR)$(PCLIBDIR)'
	install -m644 tree-sitter.pc '$(DESTDIR)$(PCLIBDIR)'/

clean:
	rm -f lib/src/*.o libtree-sitter.a libtree-sitter.$(SOEXT) libtree-sitter.$(SOEXTVER_MAJOR) libtree-sitter.$(SOEXTVER)

.PHONY: all install clean
