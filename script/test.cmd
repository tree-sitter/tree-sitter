@echo off

setlocal
set TREE_SITTER_TEST=1
set RUST_TEST_THREADS=1
set RUST_BACKTRACE=full
cargo test -p tree-sitter-cli "%~1" -- --nocapture
endlocal
