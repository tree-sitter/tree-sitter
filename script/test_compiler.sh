#!/usr/bin/env bash

set -e -u

make compiler_specs
source `dirname $0`/util/run_tests.sh
run_tests out/Default/compiler_specs "$@"
