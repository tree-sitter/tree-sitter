{
  perSystem =
    {
      self',
      pkgs,
      lib,
      src,
      version,
      ...
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

      wasmTestGrammars = pkgs.stdenv.mkDerivation {
        inherit src version;

        pname = "wasm-test-grammars";

        nativeBuildInputs = [
          self'.packages.cli
          pkgs.pkgsCross.wasi32.stdenv.cc
          pkgs.nodejs_22
        ];

        buildPhase = ''
          export HOME=$TMPDIR
          export TREE_SITTER_WASI_SDK_PATH=${pkgs.pkgsCross.wasi32.stdenv.cc}
          export NIX_LDFLAGS=""

          cp -r ${self'.packages.test-grammars}/fixtures .
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
      };
    in
    {
      packages = {
        web-tree-sitter = pkgs.buildNpmPackage {
          inherit src version;

          pname = "web-tree-sitter";

          npmDepsHash = "sha256-y0GobcskcZTmju90TM64GjeWiBmPFCrTOg0yfccdB+Q=";

          nativeBuildInputs = [
            pkgs.rustPlatform.cargoSetupHook
            pkgs.cargo
            pkgs.pkg-config
            pkgs.emscripten
          ];

          cargoDeps = pkgs.rustPlatform.importCargoLock {
            lockFile = ../../Cargo.lock;
          };

          doCheck = true;

          postPatch = ''
            cp lib/binding_web/package{,-lock}.json .
          '';

          buildPhase = ''
            cd lib/binding_web
            CJS=true npm run build
            CJS=true npm run build:debug
            npm run build:debug
            npm run build
          '';

          checkPhase = ''
            cd ../../
            mkdir -p target/release

            for grammar in ${wasmTestGrammars}/*.wasm; do
              if [ -f "$grammar" ]; then
                cp "$grammar" target/release/
              fi
            done

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
            maintainers = [ lib.maintainers.amaanq ];
            platforms = lib.platforms.all;
          };
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

          meta = {
            description = "Lint check for web-tree-sitter TypeScript/JavaScript code";
          };
        };
      };
    };
}
