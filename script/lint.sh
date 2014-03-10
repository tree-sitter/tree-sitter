#!/usr/bin/env bash

filters=-whitespace,-readability/namespace,-legal/copyright
cpplint=externals/cpplint.py

find src -type f | xargs $cpplint --root=src --filter=$filters 2>&1
find include -type f | xargs $cpplint --root=include --filter=$filters 2>&1
