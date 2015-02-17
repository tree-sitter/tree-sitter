#!/usr/bin/env bash

set -e

git submodule update --init --recursive
externals/gyp/gyp project.gyp --depth . --format=make $@
externals/gyp/gyp tests.gyp --depth . --format=make $@

if [ "$1" == "-h" ]; then
  cat <<-HELP

Variables:

-D USE_BOOST_REGEX=true
  Use boost regex library for tests, not the built-in regex library. This is
  useful when linking against an older version of the standard library.
  libboost_regex must be installed.

-D USE_LIBPROFILER=false
  Don't link libprofiler into the test binaries. This flag is needed on systems
  where libprofiler (from the google-perftools package) is not installed.

HELP
fi
