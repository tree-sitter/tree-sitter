#!/bin/bash

output_path=src/ffi.rs
header_path='vendor/tree-sitter/include/tree_sitter/runtime.h'

bindgen                         \
  --no-layout-tests             \
  --whitelist-type '^TS.*'      \
  --whitelist-function '^ts_.*' \
  --opaque-type FILE            \
  $header_path > $output_path

echo "" >> $output_path
version_constant='TREE_SITTER_LANGUAGE_VERSION'
version_number=$(egrep "#define $version_constant (.*)" $header_path | cut -d' ' -f3)
echo "pub const $version_constant: usize = $version_number;" >> $output_path
