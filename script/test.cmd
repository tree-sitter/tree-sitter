@echo off

setlocal
set RUST_TEST_THREADS=1
set RUST_BACKTRACE=full
cargo test -p tree-sitter-cli "%~1" -- --nocapture
endlocal
