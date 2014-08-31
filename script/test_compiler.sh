#!/usr/bin/env bash

set -e -u

source `dirname $0`/util/run_tests.sh
run_tests compiler_specs "$@"
