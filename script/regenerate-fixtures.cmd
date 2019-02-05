@echo off

call:regenerate bash
call:regenerate c
call:regenerate cpp
call:regenerate embedded-template
call:regenerate go
call:regenerate html
call:regenerate javascript
call:regenerate json
call:regenerate python
call:regenerate rust
exit /B 0

:regenerate
setlocal
set tree_sitter=%cd%\target\release\tree-sitter
set grammar_dir=test\fixtures\grammars\%~1
pushd %grammar_dir%
%tree_sitter% generate src\grammar.json
popd
exit /B 0
