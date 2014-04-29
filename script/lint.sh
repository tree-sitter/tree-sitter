#!/usr/bin/env bash

externals/cpplint.py \
  --root=src \
  --linelength=110 \
  --filter=-legal/copyright,-readability/namespace,-whitespace/indent,-whitespace/line_length \
  $(find src/compiler -type f) \
  2>&1
