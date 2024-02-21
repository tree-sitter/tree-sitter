VERSION := 0.0.1

LANGUAGE_NAME := tree-sitter-PARSER_NAME

# repository
SRC_DIR := src

PARSER_REPO_URL := $(shell git -C $(SRC_DIR) remote get-url origin 2>/dev/null)

ifeq ($(PARSER_URL),)
	PARSER_URL := $(subst .git,,$(PARSER_REPO_URL))
ifeq ($(shell echo $(PARSER_URL) | grep '^[a-z][-+.0-9a-z]*://'),)
	PARSER_URL := $(subst :,/,$(PARSER_URL))
	PARSER_URL := $(subst git@,https://,$(PARSER_URL))
endif
endif

# ABI versioning
SONAME_MAJOR := $(word 1,$(subst ., ,$(VERSION)))
SONAME_MINOR := $(word 2,$(subst ., ,$(VERSION)))

# install directory layout
PREFIX ?= /usr/local
INCLUDEDIR ?= $(PREFIX)/include
LIBDIR ?= $(PREFIX)/lib
PCLIBDIR ?= $(LIBDIR)/pkgconfig

# object files
OBJS := $(patsubst %.c,%.o,$(wildcard $(SRC_DIR)/*.c))

# flags
ARFLAGS := rcs
override CFLAGS += -I$(SRC_DIR) -std=c11

# OS-specific bits
ifeq ($(shell uname),Darwin)
	SOEXT = dylib
	SOEXTVER_MAJOR = $(SONAME_MAJOR).dylib
	SOEXTVER = $(SONAME_MAJOR).$(SONAME_MINOR).dylib
	LINKSHARED := $(LINKSHARED)-dynamiclib -Wl,
	ifneq ($(ADDITIONAL_LIBS),)
	LINKSHARED := $(LINKSHARED)$(ADDITIONAL_LIBS),
	endif
	LINKSHARED := $(LINKSHARED)-install_name,$(LIBDIR)/lib$(LANGUAGE_NAME).$(SONAME_MAJOR).dylib,-rpath,@executable_path/../Frameworks
else ifneq ($(filter $(shell uname),Linux FreeBSD NetBSD DragonFly),)
	SOEXT = so
	SOEXTVER_MAJOR = so.$(SONAME_MAJOR)
	SOEXTVER = so.$(SONAME_MAJOR).$(SONAME_MINOR)
	LINKSHARED := $(LINKSHARED)-shared -Wl,
	ifneq ($(ADDITIONAL_LIBS),)
	LINKSHARED := $(LINKSHARED)$(ADDITIONAL_LIBS)
	endif
	LINKSHARED := $(LINKSHARED)-soname,lib$(LANGUAGE_NAME).so.$(SONAME_MAJOR)
else ifeq ($(OS),Windows_NT)
	$(error "Windows is not supported")
endif
ifneq ($(filter $(shell uname),FreeBSD NetBSD DragonFly),)
	PCLIBDIR := $(PREFIX)/libdata/pkgconfig
endif

all: lib$(LANGUAGE_NAME).a lib$(LANGUAGE_NAME).$(SOEXT) $(LANGUAGE_NAME).pc

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $^ -o $@

lib$(LANGUAGE_NAME).a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

lib$(LANGUAGE_NAME).$(SOEXT): $(OBJS)
	$(CC) -fPIC $(LDFLAGS) $(LINKSHARED) $^ $(LDLIBS) -o $@

$(LANGUAGE_NAME).pc:
	sed > $@ bindings/c/$(LANGUAGE_NAME).pc.in \
		-e 's|@URL@|$(PARSER_URL)|' \
		-e 's|@VERSION@|$(VERSION)|' \
		-e 's|@LIBDIR@|$(LIBDIR)|;' \
		-e 's|@INCLUDEDIR@|$(INCLUDEDIR)|;' \
		-e 's|=$(PREFIX)|=$${prefix}|' \
		-e 's|@PREFIX@|$(PREFIX)|' \
		-e 's|@REQUIRES@|$(REQUIRES)|' \
		-e 's|@ADDITIONAL_LIBS@|$(ADDITIONAL_LIBS)|'

install: all
	install -Dm644 bindings/c/$(LANGUAGE_NAME).h '$(DESTDIR)$(INCLUDEDIR)'/tree_sitter/$(LANGUAGE_NAME).h
	install -Dm644 $(LANGUAGE_NAME).pc '$(DESTDIR)$(PCLIBDIR)'/$(LANGUAGE_NAME).pc
	install -Dm755 lib$(LANGUAGE_NAME).a '$(DESTDIR)$(LIBDIR)'/lib$(LANGUAGE_NAME).a
	install -Dm755 lib$(LANGUAGE_NAME).$(SOEXT) '$(DESTDIR)$(LIBDIR)'/lib$(LANGUAGE_NAME).$(SOEXTVER)
	ln -sf lib$(LANGUAGE_NAME).$(SOEXTVER) '$(DESTDIR)$(LIBDIR)'/lib$(LANGUAGE_NAME).$(SOEXTVER_MAJOR)
	ln -sf lib$(LANGUAGE_NAME).$(SOEXTVER_MAJOR) '$(DESTDIR)$(LIBDIR)'/lib$(LANGUAGE_NAME).$(SOEXT)

clean:
	$(RM) $(OBJS) $(LANGUAGE_NAME).pc lib$(LANGUAGE_NAME).a lib$(LANGUAGE_NAME).$(SOEXT)

.PHONY: all install clean
