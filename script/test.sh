#!/usr/bin/env bash

set -e

make compiler_specs
out/Default/compiler_specs

make runtime_specs
out/Default/runtime_specs
