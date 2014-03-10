#!/usr/bin/env bash

find src -type f | xargs externals/cpplint.py \
  --root=src \
  --filter=-whitespace,-readability/namespace,-legal/copyright \
  2>&1
