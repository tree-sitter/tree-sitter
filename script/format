#!/usr/bin/env bash

find                                             \
  src include                                    \
  -name '*.c' -or -name '*.cc' -or -name '*.h' | \
  xargs clang-format -i -style=file
