@echo off

setlocal
set RUST_TEST_THREADS=1
set RUST_BACKTRACE=full
cargo test --features logging_parser --features logging_lexer "%~1" -- --nocapture
endlocal
