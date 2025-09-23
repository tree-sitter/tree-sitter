{
  description = "Tree-sitter - A parser generator tool and an incremental parsing library";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs =
    inputs:
    let
      inherit (inputs.nixpkgs) lib;
      inherit (inputs) self;
      systems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];
      eachSystem = lib.genAttrs systems;
      pkgsFor = inputs.nixpkgs.legacyPackages;

      version = "0.26.0";

      fs = lib.fileset;
      src = fs.toSource {
        root = ./.;
        fileset = fs.difference (fs.gitTracked ./.) (
          fs.unions [
            ./.envrc
            ./flake.lock
            ./FUNDING.json
            ./README.md
            ./Dockerfile
            (fs.fileFilter (file: lib.strings.hasInfix ".git" file.name) ./.)
            (fs.fileFilter (file: file.hasExt "nix") ./.)
          ]
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
      filesWithExtension =
        ext:
        fs.toSource {
          root = ./.;
          fileset = fs.fileFilter (file: (file.hasExt ext) && file.type == "regular") ./.;
        };
    in
    {
      packages = eachSystem (
        system:
        let
          pkgs = pkgsFor.${system};
          crossTargets = {
            aarch64-linux = pkgs.pkgsCross.aarch64-multiplatform;
            armv7l-linux = pkgs.pkgsCross.armv7l-hf-multiplatform;
            x86_64-linux = pkgs.pkgsCross.gnu64;
            i686-linux = pkgs.pkgsCross.gnu32;
            loongarch64 = pkgs.pkgsCross.loongarch64-linux;
            mips = pkgs.pkgsCross.mips-linux-gnu;
            mips64 = pkgs.pkgsCross.mips64-linux-gnuabi64;
            musl64 = pkgs.pkgsCross.musl64;
            powerpc64-linux = pkgs.pkgsCross.ppc64;
            riscv32 = pkgs.pkgsCross.riscv32;
            riscv64 = pkgs.pkgsCross.riscv64;
            s390x = pkgs.pkgsCross.s390x;

            x86_64-windows = pkgs.pkgsCross.mingwW64;
          }
          // (lib.optionalAttrs pkgs.stdenv.isDarwin {
            x86_64-darwin = pkgs.pkgsCross.x86_64-darwin;
            aarch64-darwin = pkgs.pkgsCross.aarch64-darwin;
          });

        in
        {
          default = self.packages.${system}.cli;

          docs = pkgs.callPackage ./docs/package.nix { inherit version; };

          test-grammars =
            let
              fetchGrammar =
                name: rev: sha256:
                pkgs.fetchFromGitHub {
                  owner = "tree-sitter";
                  repo = "tree-sitter-${name}";
                  inherit rev sha256;
                };

              testGrammars = lib.mapAttrs (name: spec: fetchGrammar name spec.rev spec.sha256) grammarSpecs;
            in
            pkgs.stdenv.mkDerivation {
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

          wasm-test-grammars = pkgs.callPackage ./lib/binding_web/wasm-test-grammars.nix {
            inherit src version;
            inherit (self.packages.${system}) cli test-grammars;
          };

          web-tree-sitter = pkgs.callPackage ./lib/binding_web/package.nix {
            inherit src version;
            inherit (self.packages.${system}) wasm-test-grammars;
          };

          lib = pkgs.callPackage ./lib/package.nix {
            inherit src version;
          };

          cli = pkgs.callPackage ./crates/cli/package.nix {
            inherit src version;
            inherit (self.packages.${system}) test-grammars;
          };
        }
        // (lib.mapAttrs' (arch: pkg: {
          name = "cli-${arch}";
          value = pkg.callPackage ./crates/cli/package.nix {
            inherit src version;
            inherit (self.packages.${system}) test-grammars;
          };
        }) crossTargets)
        // (lib.mapAttrs' (arch: pkg: {
          name = "lib-${arch}";
          value = pkg.callPackage ./lib/package.nix {
            inherit src version;
          };
        }) crossTargets)
      );

      apps = eachSystem (
        system:
        let
          pkgs = pkgsFor.${system};
        in
        {
          default = self.apps.${system}.cli;

          cli = {
            type = "app";
            program = "${lib.getExe self.packages.${system}.cli}";
            meta.description = "Tree-sitter CLI for developing, testing, and using parsers";
          };

          docs = {
            type = "app";
            program = lib.getExe (
              pkgs.writeShellScriptBin "docs" ''
                echo "📚 Serving documentation at http://localhost:3000"
                cd docs && ${lib.getExe pkgs.mdbook} serve
              ''
            );
            meta.description = "Serve Tree-sitter documentation locally";
          };

          format = {
            type = "app";
            program = lib.getExe (
              pkgs.writeShellScriptBin "format-all" ''
                set -e
                echo "Formatting..."
                echo ""
                echo "→ Rust..."
                ${lib.getExe pkgs.cargo} fmt --all
                echo "→ Nix..."
                ${lib.getExe pkgs.nixfmt} ${filesWithExtension "nix"}
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
            program = lib.getExe (
              pkgs.writeShellScriptBin "lint-all" ''
                set -e
                echo "Linting code..."
                echo ""
                echo "→ Checking Rust formatting..."
                ${lib.getExe pkgs.cargo} fmt --all --check
                echo "→ Running clippy..."
                ${lib.getExe pkgs.cargo} clippy --workspace --all-targets -- -D warnings
                echo "→ Checking Nix formatting..."
                ${lib.getExe pkgs.nixfmt} --check ${filesWithExtension "nix"}
                echo "→ Checking Web code..."
                cd lib/binding_web && ${lib.getExe' pkgs.nodejs_22 "npm"} install --silent && ${lib.getExe' pkgs.nodejs_22 "npm"} run lint
                cd ../..
                echo ""
                echo "Linting complete"
              ''
            );
            meta.description = "Run all linting checks";
          };
        }
      );

      checks = eachSystem (
        system:
        let
          pkgs = pkgsFor.${system};
        in
        {
          inherit (self.packages.${system})
            cli
            lib
            web-tree-sitter
            ;

          nix-fmt = pkgs.runCommandNoCC "nix-fmt-check" { } ''
            ${lib.getExe self.formatter.${system}} --check ${filesWithExtension "nix"}
            touch $out
          '';
          rust-fmt = pkgs.runCommandNoCC "rust-fmt-check" { } ''
            ${lib.getExe pkgs.rustfmt} --check
            touch $out
          '';

          rust-clippy = pkgs.rustPlatform.buildRustPackage {
            inherit src version;

            pname = "rust-clippy-check";

            cargoLock.lockFile = ./Cargo.lock;

            nativeBuildInputs = with pkgs; [
              pkg-config
              clippy
              cmake
              clang
              libclang
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

          web-lint = pkgs.buildNpmPackage {
            inherit src version;

            pname = "web-tree-sitter-lint";

            npmDepsHash = "sha256-y0GobcskcZTmju90TM64GjeWiBmPFCrTOg0yfccdB+Q=";

            postPatch = ''
              cp lib/binding_web/package{,-lock}.json .
            '';

            buildPhase = ''
              cd lib/binding_web
              npm run lint
            '';

            installPhase = ''
              touch $out
            '';

            meta.description = "Lint check for web-tree-sitter TypeScript/JavaScript code";
          };
        }
      );

      formatter = eachSystem (system: pkgsFor.${system}.nixfmt);

      devShells = eachSystem (
        system:
        let
          pkgs = pkgsFor.${system};
        in
        {
          default = pkgs.mkShell {
            buildInputs = with pkgs; [
              cargo
              rustc
              clippy
              rust-analyzer
              rustfmt
              cargo-llvm-cov

              cmake
              gnumake
              pkg-config
              llvm
              clang
              libclang

              nodejs_22
              nodePackages.typescript
              emscripten
              pkgsCross.wasi32.stdenv.cc

              mdbook
              mdbook-admonish

              git
              nixfmt
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
              echo "Cross-compilation:"
              echo "  Build for other platforms using .#cli-<target> for the CLI,"
              echo "  and .#lib-<target> for the library (e.g. nix build .#cli-aarch64-linux)."
              echo ""
              echo "  Available targets:"
              echo "    aarch64-linux    - ARM64 Linux"
              echo "    armv7l-linux     - ARMv7 Linux"
              echo "    x86_64-linux     - x86_64 Linux"
              echo "    i686-linux       - i686 Linux"
              echo "    loongarch64      - LoongArch64 Linux"
              echo "    mips             - MIPS Linux"
              echo "    mips64           - MIPS64 Linux"
              echo "    musl64           - x86_64 MUSL Linux"
              echo "    powerpc64-linux  - PowerPC64 Linux"
              echo "    riscv32          - RISC-V 32-bit Linux"
              echo "    riscv64          - RISC-V 64-bit Linux"
              echo "    s390x            - s390x Linux"
              echo "    x86_64-windows   - x86_64 Windows"
              echo "    x86_64-darwin    - x86_64 macOS (Darwin only)"
              echo "    aarch64-darwin   - ARM64 macOS (Darwin only)"
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

            env = {
              RUST_BACKTRACE = 1;
              LIBCLANG_PATH = "${pkgs.libclang.lib}/lib";
              LLVM_COV = "${pkgs.llvm}/bin/llvm-cov";
              LLVM_PROFDATA = "${pkgs.llvm}/bin/llvm-profdata";
              TREE_SITTER_WASI_SDK_PATH = "${pkgs.pkgsCross.wasi32.stdenv.cc}";
            };
          };
        }
      );
    };
}
