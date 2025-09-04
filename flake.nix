{
  description = "Tree-sitter - A parser generator tool and an incremental parsing library";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-parts.url = "github:hercules-ci/flake-parts";
  };

  outputs =
    inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];

      imports = [
        ./crates/cli/flake.nix
        ./lib/flake.nix
        ./lib/binding_web/flake.nix
        ./docs/flake.nix
      ];

      perSystem =
        {
          self',
          pkgs,
          lib,
          ...
        }:
        let
          version = "0.26.0";

          src = pkgs.lib.cleanSourceWith {
            src = ./.;
            filter =
              name: type:
              let
                baseName = baseNameOf name;
              in
              !(
                lib.elem baseName [
                  "target"
                  "node_modules"
                  ".git"
                  ".direnv"
                  "flake.lock"
                ]
                || lib.hasPrefix "result" baseName
              );
          };

          fixturesJson = lib.importJSON ./test/fixtures/fixtures.json;

          grammarHashes = {
            bash = "sha256-vRaN/mNfpR+hdv2HVS1bzaW0o+HGjizRFsk3iinICJE=";
            c = "sha256-gmzbdwvrKSo6C1fqTJFGxy8x0+T+vUTswm7F5sojzKc=";
            cpp = "sha256-tP5Tu747V8QMCEBYwOEmMQUm8OjojpJdlRmjcJTbe2k=";
            embedded-template = "sha256-nBQain0Lc21jOgQFfvkyq615ZmT8qdMxtqIoUcOcO3A=";
            go = "sha256-y7bTET8ypPczPnMVlCaiZuswcA7vFrDOc2jlbfVk5Sk=";
            html = "sha256-Pd5Me1twLGOrRB3pSMVX9M8VKenTK0896aoLznjNkGo=";
            java = "sha256-OvEO1BLZLjP3jt4gar18kiXderksFKO0WFXDQqGLRIY=";
            javascript = "sha256-2Jj/SUG+k8lHlGSuPZvHjJojvQFgDiZHZzH8xLu7suE=";
            jsdoc = "sha256-Azzb2zBjAfwbEmAEO1YqhpaxtzbXmRjfIzRla2Hx+24=";
            json = "sha256-DNZC2cTy1C8OaMOpEHM6NoRtOIbLaBf0CLXXWCKODlw=";
            php = "sha256-jI7yzcoHS/tNxUqJI4aD1rdEZV3jMn1GZD0J+81Dyf0=";
            python = "sha256-71Od4sUsxGEvTwmXX8hBvzqD55hnXkVJublrhp1GICg=";
            ruby = "sha256-iu3MVJl0Qr/Ba+aOttmEzMiVY6EouGi5wGOx5ofROzA=";
            rust = "sha256-y3sJURlSTM7LRRN5WGIAeslsdRZU522Tfcu6dnXH/XQ=";
            typescript = "sha256-CU55+YoFJb6zWbJnbd38B7iEGkhukSVpBN7sli6GkGY=";
          };

          grammarSpecs = lib.listToAttrs (
            map (fixture: {
              name = lib.elemAt fixture 0;
              value = {
                rev = lib.elemAt fixture 1;
                sha256 = grammarHashes.${lib.elemAt fixture 0};
              };
            }) fixturesJson
          );

          fetchGrammar =
            name: rev: sha256:
            pkgs.fetchFromGitHub {
              owner = "tree-sitter";
              repo = "tree-sitter-${name}";
              inherit rev sha256;
            };

          testGrammars = lib.mapAttrs (name: spec: fetchGrammar name spec.rev spec.sha256) grammarSpecs;
        in
        {
          _module.args = {
            inherit src version;
          };

          packages = {
            default = self'.packages.cli;

            test-grammars = pkgs.stdenv.mkDerivation {
              inherit src version;

              pname = "test-grammars";

              buildPhase = ''
                mkdir -p test/fixtures/grammars
                ${lib.concatMapStrings (name: ''
                  cp -r ${testGrammars.${name}} test/fixtures/grammars/${name}
                '') (lib.attrNames testGrammars)}
              '';

              installPhase = ''
                mkdir -p $out
                cp -r test/fixtures $out/fixtures
              '';
            };
          };

          apps = {
            default = self'.apps.cli;

            cli = {
              type = "app";
              program = "${self'.packages.cli}/bin/tree-sitter";
              meta.description = "Tree-sitter CLI for developing, testing, and using parsers";
            };

            docs = {
              type = "app";
              program = "${pkgs.writeShellScript "docs" ''
                echo "📚 Serving documentation at http://localhost:3000"
                cd docs && ${pkgs.mdbook}/bin/mdbook serve
              ''}";
              meta.description = "Serve Tree-sitter documentation locally";
            };

            format = {
              type = "app";
              program = toString (
                pkgs.writeShellScript "format-all" ''
                  set -e
                  echo "Formatting..."
                  echo ""
                  echo "→ Rust..."
                  ${pkgs.cargo}/bin/cargo fmt --all
                  echo "→ Nix..."
                  ${pkgs.nixfmt-rfc-style}/bin/nixfmt *.nix crates/cli/*.nix lib/*.nix lib/binding_web/*.nix docs/*.nix
                  echo "→ Web (TypeScript/JavaScript)..."
                  cd lib/binding_web && ${pkgs.nodejs_22}/bin/npm install --silent && ${pkgs.nodejs_22}/bin/npm run lint:fix
                  cd ../..
                  echo ""
                  echo "Formatting complete"
                ''
              );
              meta.description = "Format all Rust and Nix code";
            };

            lint = {
              type = "app";
              program = toString (
                pkgs.writeShellScript "lint-all" ''
                  set -e
                  echo "Linting code..."
                  echo ""
                  echo "→ Checking Rust formatting..."
                  ${pkgs.cargo}/bin/cargo fmt --all --check
                  echo "→ Running clippy..."
                  ${pkgs.cargo}/bin/cargo clippy --workspace --all-targets -- -D warnings
                  echo "→ Checking Nix formatting..."
                  ${pkgs.nixfmt-rfc-style}/bin/nixfmt --check *.nix crates/cli/*.nix lib/*.nix lib/binding_web/*.nix docs/*.nix
                  echo "→ Checking Web code..."
                  cd lib/binding_web && ${pkgs.nodejs_22}/bin/npm install --silent && ${pkgs.nodejs_22}/bin/npm run lint
                  cd ../..
                  echo ""
                  echo "Linting complete"
                ''
              );
              meta.description = "Run all linting checks";
            };
          };

          checks = {
            inherit (self'.packages)
              cli
              lib
              web-tree-sitter
              web-lint
              rust-fmt
              rust-clippy
              ;

            nix-fmt =
              pkgs.runCommand "nix-fmt-check"
                {
                  nativeBuildInputs = [ pkgs.nixfmt-rfc-style ];
                }
                ''
                  cd ${src}
                  nixfmt --check *.nix crates/cli/*.nix lib/*.nix lib/binding_web/*.nix docs/*.nix
                  touch $out
                '';
          };

          formatter = pkgs.nixfmt-rfc-style;

          devShells.default = pkgs.mkShell {
            buildInputs = [
              pkgs.cargo
              pkgs.rustc
              pkgs.clippy
              pkgs.rust-analyzer
              pkgs.rustfmt

              pkgs.cmake
              pkgs.gnumake
              pkgs.pkg-config
              pkgs.clang
              pkgs.libclang

              pkgs.nodejs_22
              pkgs.emscripten
              pkgs.pkgsCross.wasi32.stdenv.cc

              pkgs.mdbook
              pkgs.mdbook-admonish

              pkgs.git
              pkgs.nixfmt-rfc-style
            ];

            shellHook = ''
              echo "Tree-sitter Dev Environment"
              echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
              echo ""
              echo "Packages:"
              echo "  nix build .#cli              - Build CLI tool"
              echo "  nix build .#lib              - Build C library"
              echo "  nix build .#web-tree-sitter  - Build WASM bindings"
              echo "  nix build .#docs             - Build documentation"
              echo ""
              echo "Apps:"
              echo "  nix run .#cli                - Run tree-sitter CLI"
              echo "  nix run .#docs               - Serve docs locally"
              echo "  nix run .#format             - Format all code"
              echo "  nix run .#lint               - Run all linting checks"
              echo ""
              echo "Tests & Checks:"
              echo "  nix flake check              - Run all tests and checks"
              echo ""
              echo "Version: ${version}"
            '';

            RUST_BACKTRACE = 1;
            LIBCLANG_PATH = "${pkgs.libclang.lib}/lib";
          };
        };
    };
}
