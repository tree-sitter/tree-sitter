#!/bin/bash

set -x
set -e

if [ "$CROSS" != 1 ]; then
    exit 111
fi

docker run --rm -v /home/runner:/home/runner -w "$PWD" "$CROSS_IMAGE" "$@"
