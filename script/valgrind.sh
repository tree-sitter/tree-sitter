#!/usr/bin/env bash

valgrind $@ \
  --suppressions=./etc/valgrind.supp \
  --dsymutil=yes \
  out/Default/runtime_specs
