#!/bin/bash

# set -x
set -e

if [ -z "$ROOT" ]; then
    echo "The ROOT env var should be set to absolute path of a repo root folder" >&2
    exit 111
fi

if [ -z "$TARGET" ]; then
    echo "The TARGET env var should be equal to a \`cargo build --target <TARGET>\` command value" >&2
    exit 111
fi

tree_sitter="$ROOT"/target/"$TARGET"/release/tree-sitter

if [ "$BUILD_CMD" == "cross" ]; then
    if [ -z "$CROSS_RUNNER" ]; then
        echo "The CROSS_RUNNER env var should be set to a CARGO_TARGET_*_RUNNER env var value" >&2
        echo "that is available in a docker image used by the cross tool under the hood" >&2
        exit 111
    fi

    cross.sh $CROSS_RUNNER "$tree_sitter" "$@"
else
    "$tree_sitter" "$@"
fi
