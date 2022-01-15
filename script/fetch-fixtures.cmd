@echo off

call:fetch_grammar tree-sitter bash              master
call:fetch_grammar tree-sitter c                 master
call:fetch_grammar tree-sitter cpp               master
call:fetch_grammar tree-sitter embedded-template master
call:fetch_grammar tree-sitter go                master
call:fetch_grammar tree-sitter html              master
call:fetch_grammar tree-sitter java              master
call:fetch_grammar tree-sitter javascript        partial-order-precedences
call:fetch_grammar tree-sitter jsdoc             master
call:fetch_grammar tree-sitter json              master
call:fetch_grammar tree-sitter php               master
call:fetch_grammar tree-sitter python            master
call:fetch_grammar tree-sitter ruby              master
call:fetch_grammar tree-sitter rust              master
call:fetch_grammar tree-sitter typescript        master
call:fetch_grammar elixir-lang elixir            de20391afe5cb03ef1e8a8e43167e7b58cc52869
call:fetch_grammar fwcd        kotlin            0.2.11
call:fetch_grammar alex-pinkus swift             0.1.1-with-static-grammar.json
exit /B 0

:fetch_grammar
setlocal
set organization=%~1
set grammar_dir=test\fixtures\grammars\%~2
set grammar_url=https://github.com/%organization%/tree-sitter-%~2
set grammar_ref=%~3
@if not exist %grammar_dir% (
  git clone %grammar_url% %grammar_dir% --depth=1
)
pushd %grammar_dir%
git fetch origin %grammar_ref% --depth=1
git reset --hard FETCH_HEAD
popd
exit /B 0
