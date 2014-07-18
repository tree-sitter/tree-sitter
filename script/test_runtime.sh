#!/usr/bin/env bash

set -e -u

make runtime_specs
source `dirname $0`/util/run_tests.sh
run_tests out/Default/runtime_specs "$@"
