@echo off

cargo bench benchmark -p tree-sitter-cli
exit /b %errorlevel%
