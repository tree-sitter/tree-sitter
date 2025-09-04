{
  perSystem =
    {
      self',
      pkgs,
      lib,
      src,
      version,
      crossTargets,
      ...
    }:
    let
      buildCliFor =
        targetPkgs:
        let
          isCross = targetPkgs.stdenv.hostPlatform != pkgs.stdenv.buildPlatform;
        in
        targetPkgs.rustPlatform.buildRustPackage {
          inherit src version;
          pname = "tree-sitter-cli";

          nativeBuildInputs = [
            pkgs.pkg-config
            pkgs.nodejs_22
          ]
          ++ lib.optionals (!isCross) [ pkgs.installShellFiles ];

          cargoLock.lockFile = ../../Cargo.lock;

          preBuild = ''
            rm -rf test/fixtures
            mkdir -p test/fixtures
            cp -r ${self'.packages.test-grammars}/fixtures/* test/fixtures/
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

          meta = with lib; {
            description = "Tree-sitter CLI - A tool for developing, testing, and using Tree-sitter parsers";
            longDescription = ''
              Tree-sitter is a parser generator tool and an incremental parsing library.
              It can build a concrete syntax tree for a source file and efficiently update
              the syntax tree as the source file is edited. This package provides the CLI
              tool for developing, testing, and using Tree-sitter parsers.
            '';
            homepage = "https://tree-sitter.github.io/tree-sitter";
            changelog = "https://github.com/tree-sitter/tree-sitter/releases/tag/v${version}";
            license = licenses.mit;
            maintainers = [ maintainers.amaanq ];
            platforms = platforms.all;
            mainProgram = "tree-sitter";
          };
        };

      crossPackages = lib.mapAttrs (name: targetPkgs: buildCliFor targetPkgs) crossTargets;
    in
    {
      packages = {
        cli = buildCliFor pkgs;
      }
      // (lib.mapAttrs' (name: pkg: lib.nameValuePair "cli-${name}" pkg) crossPackages)
      // {
        rust-fmt =
          pkgs.runCommand "rust-fmt-check"
            {
              nativeBuildInputs = [
                pkgs.cargo
                pkgs.rustfmt
              ];
            }
            ''
              cd ${src}
              cargo fmt --all --check
              touch $out
            '';

        rust-clippy = pkgs.rustPlatform.buildRustPackage {
          inherit src version;

          pname = "rust-clippy-check";

          cargoLock.lockFile = ../../Cargo.lock;

          nativeBuildInputs = [
            pkgs.pkg-config
            pkgs.clippy
            pkgs.cmake
            pkgs.clang
            pkgs.libclang
          ];

          buildPhase = ''
            export HOME=$TMPDIR
            export LIBCLANG_PATH="${pkgs.libclang.lib}/lib"
            cargo xtask clippy
          '';

          installPhase = ''
            touch $out
          '';

          doCheck = false;
        };
      };
    };
}
