#!/bin/bash

set -x
set -e

tree_sitter="$ROOT"/target/"$TARGET"/release/tree-sitter

if [ "$CROSS" = 1 ]; then
    cross.sh $CROSS_RUNNER "$tree_sitter" "$@"
else
    "$tree_sitter" "$@"
fi
