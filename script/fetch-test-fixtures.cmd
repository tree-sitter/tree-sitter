@Echo off
SETLOCAL

Set grammar_dir=fixtures\tree-sitter-rust
Set grammar_url=https://github.com/tree-sitter/tree-sitter-rust

@IF NOT EXIST  %grammar_dir% (
  git clone %grammar_url% %grammar_dir% --depth=1
)

pushd %grammar_dir%
git fetch origin master --depth=1
git reset --hard origin/master
popd

ENDLOCAL
