#!/usr/bin/env bash

filters=-whitespace,-readability/namespace,-legal/copyright
cpplint=externals/cpplint.py

find src/compiler -type f | xargs $cpplint --root=src --filter=$filters 2>&1
