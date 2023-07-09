#!/bin/bash

# set -x
set -e

if [ "$BUILD_CMD" != "cross" ]; then
    echo "cross.sh - is a helper to assist only in cross compiling environments" >&2
    echo "To use this tool set the BUILD_CMD env var to the \"cross\" value" >&2
    exit 111
fi

if [ -z "$CROSS_IMAGE" ]; then
    echo "The CROSS_IMAGE env var should be provided" >&2
    exit 111
fi

docker run --rm -v /home/runner:/home/runner -w "$PWD" "$CROSS_IMAGE" "$@"
