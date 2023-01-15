@echo off

setlocal EnableDelayedExpansion
set tree_sitter="%cd%\target\release\tree-sitter"

IF "%~1" == "--build" set build="--build"

for /f "tokens=*" %%f in ('dir test\fixtures\grammars\grammar.js /b/s') do (
  pushd "%%f\.."
  echo Regenerating parser !cd!
  %tree_sitter% generate src\grammar.json --no-bindings --abi=latest !build!
  popd
)

exit /B 0
