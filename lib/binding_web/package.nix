{
  wasm-test-grammars,
  lib,
  buildNpmPackage,
  rustPlatform,
  cargo,
  pkg-config,
  emscripten,
  src,
  version,
}:
buildNpmPackage {
  inherit src version;

  pname = "web-tree-sitter";

  npmDepsHash = "sha256-y0GobcskcZTmju90TM64GjeWiBmPFCrTOg0yfccdB+Q=";

  nativeBuildInputs = [
    rustPlatform.cargoSetupHook
    cargo
    pkg-config
    emscripten
  ];

  cargoDeps = rustPlatform.importCargoLock {
    lockFile = ../../Cargo.lock;
  };

  doCheck = true;

  postPatch = ''
    cp lib/binding_web/package{,-lock}.json .
  '';

  buildPhase = ''
    pushd lib/binding_web

    CJS=true npm run build
    CJS=true npm run build:debug
    npm run build:debug
    npm run build

    popd

    mkdir -p target/release

    for grammar in ${wasm-test-grammars}/*.wasm; do
      if [ -f "$grammar" ]; then
        cp "$grammar" target/release/
      fi
    done
  '';

  checkPhase = ''
    cd lib/binding_web && npm test
  '';

  meta = {
    description = "web-tree-sitter - WebAssembly bindings to the Tree-sitter parsing library.";
    longDescription = ''
      web-tree-sitter provides WebAssembly bindings to the Tree-sitter parsing library.
      It can build a concrete syntax tree for a source file and efficiently update
      the syntax tree as the source file is edited. This package provides the WebAssembly bindings
      and a JavaScript API for using them in web browsers
    '';
    homepage = "https://tree-sitter.github.io/tree-sitter";
    changelog = "https://github.com/tree-sitter/tree-sitter/releases/tag/v${version}";
    license = lib.licenses.mit;
    maintainers = with lib.maintainers; [ amaanq ];
    platforms = lib.platforms.all;
  };
}
