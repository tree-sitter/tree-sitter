#!/bin/bash

# set -x
set -e

if [ "$BUILD_CMD" == "cross" ]; then
    if [ -z "$CC" ]; then
        echo "make.sh: CC is not set" >&2
        exit 111
    fi
    if [ -z "$AR" ]; then
        echo "make.sh: AR is not set" >&2
        exit 111
    fi

    cross.sh make CC=$CC AR=$AR "$@"
else
    make "$@"
fi
