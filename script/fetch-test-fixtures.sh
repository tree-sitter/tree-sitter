#!/bin/bash

grammar_dir='fixtures/tree-sitter-rust'
grammar_url='https://github.com/tree-sitter/tree-sitter-rust'

if [ ! -d $grammar_dir ]; then
  git clone $grammar_url $grammar_dir --depth=1
fi

(
  cd $grammar_dir;
  git fetch origin master --depth=1
  git reset --hard origin/master;
)
