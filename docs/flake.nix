{
  perSystem =
    {
      pkgs,
      lib,
      src,
      version,
      ...
    }:
    {
      packages.docs = pkgs.stdenv.mkDerivation {
        inherit src version;

        pname = "tree-sitter-docs";

        nativeBuildInputs = [
          pkgs.mdbook
          pkgs.mdbook-admonish
        ];

        buildPhase = ''
          cd docs
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
      };
    };
}
