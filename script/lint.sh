#!/usr/bin/env bash

cpplint=externals/cpplint.py

find src/compiler -type f | xargs $cpplint \
  --root=src \
  --linelength=110 \
  --filter=-readability/namespace,-legal/copyright \
  2>&1
