{
  stdenv,
  lib,
  version,
  mdbook,
  mdbook-admonish,
}:
stdenv.mkDerivation {
  inherit version;

  src = ./.;
  pname = "tree-sitter-docs";

  nativeBuildInputs = [
    mdbook
    mdbook-admonish
  ];

  buildPhase = ''
    mdbook build
  '';

  installPhase = ''
    mkdir -p $out/share/doc
    cp -r book $out/share/doc/tree-sitter
  '';

  meta = {
    description = "Tree-sitter documentation";
    homepage = "https://tree-sitter.github.io/tree-sitter";
    license = lib.licenses.mit;
  };
}
