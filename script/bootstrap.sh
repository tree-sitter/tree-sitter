#!/usr/bin/env bash

set -e

git submodule update --init
externals/gyp/gyp tree_sitter.gyp --depth .
externals/gyp/gyp tree_sitter.gyp --depth . --format=make
