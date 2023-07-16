@echo off

call:fetch_grammar bash              master
call:fetch_grammar c                 master
call:fetch_grammar cpp               670404d7c689be1c868a46f919ba2a3912f2b7ef
call:fetch_grammar embedded-template master
call:fetch_grammar go                master
call:fetch_grammar html              master
call:fetch_grammar java              master
call:fetch_grammar javascript        partial-order-precedences
call:fetch_grammar jsdoc             master
call:fetch_grammar json              master
call:fetch_grammar php               master
call:fetch_grammar python            master
call:fetch_grammar ruby              master
call:fetch_grammar rust              master
call:fetch_grammar typescript        master
exit /B 0

:fetch_grammar
setlocal
set grammar_dir=test\fixtures\grammars\%~1
set grammar_url=https://github.com/tree-sitter/tree-sitter-%~1
set grammar_branch=%~2
@if not exist %grammar_dir% (
  git clone %grammar_url% %grammar_dir% --depth=1
)
pushd %grammar_dir%
git fetch origin %2 --depth=1
git reset --hard FETCH_HEAD
popd
exit /B 0
