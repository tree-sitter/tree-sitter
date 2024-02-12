@echo off

setlocal
set RUST_TEST_THREADS=1
set RUST_BACKTRACE=full
cargo test "%~1"
if %errorlevel% NEQ 0 (
  exit /b %errorlevel%
)
endlocal
