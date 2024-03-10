VERSION := 0.22.0

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
ARFLAGS := rcs
CFLAGS := -O3 -Wall -Wextra -Wshadow -pedantic
override CFLAGS += -std=c11 -fPIC -fvisibility=hidden
override CFLAGS += -Ilib/src -Ilib/src/wasm -Ilib/include

# ABI versioning
SONAME_MAJOR := $(word 1,$(subst ., ,$(VERSION)))
SONAME_MINOR := $(word 2,$(subst ., ,$(VERSION)))

# OS-specific bits
ifeq ($(OS),Windows_NT)
	$(error "Windows is not supported")
else ifeq ($(shell uname),Darwin)
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
ifneq ($(filter $(shell uname),FreeBSD NetBSD DragonFly),)
	PCLIBDIR := $(PREFIX)/libdata/pkgconfig
endif

all: libtree-sitter.a libtree-sitter.$(SOEXT) tree-sitter.pc

libtree-sitter.a: $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

libtree-sitter.$(SOEXT): $(OBJ)
	$(CC) $(LDFLAGS) $(LINKSHARED) $^ $(LDLIBS) -o $@
ifneq ($(STRIP),)
	$(STRIP) $@
endif

tree-sitter.pc: tree-sitter.pc.in
	sed -e 's|@VERSION@|$(VERSION)|' \
		-e 's|@LIBDIR@|$(LIBDIR)|' \
		-e 's|@INCLUDEDIR@|$(INCLUDEDIR)|' \
		-e 's|=$(PREFIX)|=$${prefix}|' \
		-e 's|@PREFIX@|$(PREFIX)|' $< > $@

clean:
	$(RM) $(OBJ) tree-sitter.pc libtree-sitter.a libtree-sitter.$(SOEXT)

install: all
	install -Dm644 lib/include/tree_sitter/api.h '$(DESTDIR)$(INCLUDEDIR)'/tree_sitter/api.h
	install -Dm644 tree-sitter.pc '$(DESTDIR)$(PCLIBDIR)'/tree-sitter.pc
	install -Dm644 libtree-sitter.a '$(DESTDIR)$(LIBDIR)'/libtree-sitter.a
	install -m755 libtree-sitter.$(SOEXT) '$(DESTDIR)$(LIBDIR)'/libtree-sitter.$(SOEXTVER)
	ln -sf libtree-sitter.$(SOEXTVER) '$(DESTDIR)$(LIBDIR)'/libtree-sitter.$(SOEXTVER_MAJOR)
	ln -sf libtree-sitter.$(SOEXTVER_MAJOR) '$(DESTDIR)$(LIBDIR)'/libtree-sitter.$(SOEXT)

uninstall:
	$(RM) '$(DESTDIR)$(LIBDIR)'/libtree-sitter.a \
		'$(DESTDIR)$(LIBDIR)'/libtree-sitter.$(SOEXTVER) \
		'$(DESTDIR)$(LIBDIR)'/libtree-sitter.$(SOEXTVER_MAJOR) \
		'$(DESTDIR)$(LIBDIR)'/libtree-sitter.$(SOEXT) \
		'$(DESTDIR)$(INCLUDEDIR)'/tree_sitter/api.h \
		'$(DESTDIR)$(PCLIBDIR)'/tree-sitter.pc

.PHONY: all install uninstall clean


##### Dev targets #####

test:
	script/fetch-fixtures
	script/generate-fixtures
	script/test

test_wasm:
	script/generate-fixtures-wasm
	script/test-wasm

lint:
	cargo update --workspace --locked --quiet
	cargo check --workspace --all-targets
	cargo fmt --all --check
	cargo clippy --workspace --all-targets -- -D warnings

format:
	cargo fmt --all

changelog:
	@git-cliff --config script/cliff.toml --output CHANGELOG.md --latest --github-token $(shell gh auth token)

.PHONY: test test_wasm lint format changelog
