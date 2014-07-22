#!/usr/bin/env bash

CPPLINT=externals/cpplint.py
CPPLINT_URL=http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py

if [[ ! -f $CPPLINT ]]; then
  curl $CPPLINT_URL > $CPPLINT
  chmod +x $CPPLINT
fi

FILTERS='--filter=-legal/copyright,-readability/todo'

$CPPLINT --root=include $FILTERS include/tree_sitter/compiler.h 2>&1
$CPPLINT --root=src $FILTERS $(find src/compiler -type f) 2>&1
