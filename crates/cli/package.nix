{
  lib,
  src,
  rustPlatform,
  version,
  clang,
  libclang,
  cmake,
  pkg-config,
  nodejs_22,
  test-grammars,
  stdenv,
  installShellFiles,
}:
let
  isCross = stdenv.targetPlatform == stdenv.buildPlatform;
in
rustPlatform.buildRustPackage {
  pname = "tree-sitter-cli";

  inherit src version;

  cargoBuildFlags = [ "--all-features" ];

  nativeBuildInputs = [
    clang
    cmake
    pkg-config
    nodejs_22
  ]
  ++ lib.optionals (!isCross) [ installShellFiles ];

  cargoLock.lockFile = ../../Cargo.lock;

  env.LIBCLANG_PATH = "${libclang.lib}/lib";

  preBuild = ''
    rm -rf test/fixtures
    mkdir -p test/fixtures
    cp -r ${test-grammars}/fixtures/* test/fixtures/
    chmod -R u+w test/fixtures
  '';

  preCheck = "export HOME=$TMPDIR";
  doCheck = !isCross;

  postInstall = lib.optionalString (!isCross) ''
    installShellCompletion --cmd tree-sitter \
      --bash <($out/bin/tree-sitter complete --shell bash) \
      --zsh  <($out/bin/tree-sitter complete --shell zsh) \
      --fish <($out/bin/tree-sitter complete --shell fish)
  '';

  meta = {
    description = "Tree-sitter CLI - A tool for developing, testing, and using Tree-sitter parsers";
    longDescription = ''
      Tree-sitter is a parser generator tool and an incremental parsing library.
      It can build a concrete syntax tree for a source file and efficiently update
      the syntax tree as the source file is edited. This package provides the CLI
      tool for developing, testing, and using Tree-sitter parsers.
    '';
    homepage = "https://tree-sitter.github.io/tree-sitter";
    changelog = "https://github.com/tree-sitter/tree-sitter/releases/tag/v${version}";
    license = lib.licenses.mit;
    maintainers = with lib.maintainers; [ amaanq ];
    platforms = lib.platforms.all;
    mainProgram = "tree-sitter";
  };
}
