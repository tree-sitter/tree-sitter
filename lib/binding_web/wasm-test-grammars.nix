{
  cli,
  lib,
  nodejs_22,
  pkgsCross,
  src,
  stdenv,
  test-grammars,
  version,
}:
let
  grammars = [
    "bash"
    "c"
    "cpp"
    "embedded-template"
    "html"
    "javascript"
    "json"
    "python"
    "rust"
    "typescript"
  ];
in
stdenv.mkDerivation {
  inherit src version;

  pname = "wasm-test-grammars";

  nativeBuildInputs = [
    cli
    pkgsCross.wasi32.stdenv.cc
    nodejs_22
  ];

  buildPhase = ''
    export HOME=$TMPDIR
    export TREE_SITTER_WASI_SDK_PATH=${pkgsCross.wasi32.stdenv.cc}
    export NIX_LDFLAGS=""

    cp -r ${test-grammars}/fixtures .
    chmod -R u+w fixtures

    for grammar in ${lib.concatStringsSep " " grammars}; do
      if [ -d "fixtures/grammars/$grammar" ]; then
        echo "Building WASM for $grammar"

        if [ "$grammar" = "typescript" ]; then
          tree-sitter build --wasm -o "tree-sitter-typescript.wasm" "fixtures/grammars/$grammar/typescript"
          tree-sitter build --wasm -o "tree-sitter-tsx.wasm" "fixtures/grammars/$grammar/tsx"
        else
          tree-sitter build --wasm -o "tree-sitter-$grammar.wasm" "fixtures/grammars/$grammar"
        fi
      fi
    done
  '';

  installPhase = ''
    mkdir -p $out
    for wasm in *.wasm; do
      if [ -f "$wasm" ]; then
        echo "Installing $wasm"
        cp "$wasm" $out/
      fi
    done
  '';
}
