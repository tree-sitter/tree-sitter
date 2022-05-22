@echo off

setlocal
set RUST_TEST_THREADS=1
set RUST_BACKTRACE=full
cargo test "%~1"
endlocal
