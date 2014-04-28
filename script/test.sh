#!/usr/bin/env bash

set -e

make compiler_specs
time out/Default/compiler_specs

make runtime_specs
time out/Default/runtime_specs
