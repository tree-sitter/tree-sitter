#!/usr/bin/env bash

set -e

git submodule update --init
externals/gyp/gyp tree_sitter.gyp --depth . --format=make $@

if [ "$1" == "-h" ]; then
  cat <<-HELP

Variables:

-D USE_BOOST_REGEX - Use boost regex library for tests, not the built-in regex
                     library. This is useful when linking against an older
                     version of the standard library. libboost_regex must be
                     installed.

HELP
fi
