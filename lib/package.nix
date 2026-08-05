{
  stdenv,
  cmake,
  pkg-config,
  src,
  version,
  lib,
}:
stdenv.mkDerivation {
  inherit src version;
  pname = "tree-sitter";

  nativeBuildInputs = [
    cmake
    pkg-config
  ];

  sourceRoot = "source";

  cmakeFlags = [
    "-DBUILD_SHARED_LIBS=ON"
    "-DCMAKE_INSTALL_LIBDIR=lib"
    "-DCMAKE_INSTALL_INCLUDEDIR=include"
    "-DTREE_SITTER_FEATURE_WASM=OFF"
  ];

  enableParallelBuilding = true;

  postInstall = ''
    mkdir -p $out/{lib/pkgconfig,share/tree-sitter}
    substituteInPlace $out/lib/pkgconfig/tree-sitter.pc \
      --replace-fail "\''${prefix}" "$out" 2>/dev/null
  '';

  meta = {
    description = "Tree-sitter incremental parsing library";
    longDescription = ''
      Tree-sitter is a parser generator tool and an incremental parsing library.
      It can build a concrete syntax tree for a source file and efficiently update
      the syntax tree as the source file is edited. This package provides the core
      C library that can be used to parse source code using Tree-sitter grammars.
    '';
    homepage = "https://tree-sitter.github.io/tree-sitter";
    changelog = "https://github.com/tree-sitter/tree-sitter/releases/tag/v${version}";
    license = lib.licenses.mit;
    maintainers = [ lib.maintainers.amaanq ];
    platforms = lib.platforms.all;
  };
}
