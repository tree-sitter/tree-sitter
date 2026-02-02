# Tree-Sitter AI Coding Agent Instructions

## Project Architecture

Tree-sitter is an incremental parsing library and grammar-to-parser compiler. The codebase spans multiple languages:

- **C library** (`lib/src/`) - core incremental parser engine
- **Rust crates** (`crates/`) - CLI, bindings, and utilities
- **Parser generation** (`crates/generate/`) - grammar.js → parser.c compiler
- **Web bindings** (`lib/binding_web/`) - WASM and JavaScript support

## Critical Workflows

### Parser Generation Pipeline
This is the core feature - transform grammar definitions into C parsers:

1. User writes `grammar.js` (DSL for language syntax)
2. `tree-sitter generate` reads it and outputs:
   - `src/parser.c` - generated parser implementation
   - `src/grammar.json` - intermediate structured grammar (reusable if JS runtime unavailable)
   - `src/node-types.json` - type information for syntax nodes

**Key commands:**
- `cargo build --release` - build CLI
- `cargo xtask fetch-fixtures` - download test grammars
- `cargo xtask generate-fixtures` - regenerate parsers from grammars
- `cargo xtask test` - run all tests

### Testing Architecture
Tests are structured by parser feature:

- **Corpus tests** - `test/corpus/` - grammar files with expected parse trees (updated via `tree-sitter test --update`)
- **Highlight tests** - `test/highlight/` - syntax highlighting validation
- **Query tests** - query files with assertions about capture results
- **Tag tests** - `test/tags/` - symbol extraction validation

The CLI (`crates/cli/`) contains the test runner that validates these corpus formats.

## Rust Workspace Organization

Use workspace features:
```bash
cargo build -p tree-sitter-cli  # Single crate
cargo xtask test --language=<name>  # Test specific grammar
```

**Crates:**
- `lib` - Rust bindings to C library
- `crates/cli` - primary command-line interface
- `crates/generate` - parser generation logic
- `crates/loader` - grammar discovery and compilation
- `crates/xtask` - build automation tasks

## Key Patterns & Conventions

### Grammar Definition (grammar.js)
```javascript
export default grammar({
  name: "language_name",
  rules: {
    source_file: $ => repeat($.statement),
    statement: $ => choice($.assignment, $.expression)
  }
});
```

### Parser Compilation Steps
1. Load `grammar.js` via Node.js or QuickJS
2. Transform to `grammar.json` (JSON AST)
3. Parse grammar to build LR parse tables
4. Render C code using template system

The `OptLevel` enum controls conflict resolution and state merging optimizations.

### ABI Versioning
- `LANGUAGE_VERSION` in `lib/binding_rust/lib.rs` - current C API version
- Grammars specify `tree-sitter.json` with version to match language changes
- CLI defaults to `DEFAULT_GENERATE_ABI_VERSION`; can override with `--abi=latest`

### Incremental Parsing
The core parser uses a tree with edit tracking:
- `InputEdit` captures source changes (rows, columns, bytes)
- Parser caches parse states for unchanged ranges
- Critical for editor integration - parsing happens on keystroke

### C Library Structure
- `lib/src/parser.c` - generated parser state machine
- `lib/src/lexer.c` - scanner token matching
- `lib/src/subtree.c` - cached parse tree nodes
- `lib/src/query.c` - S-expression query execution
- Includes macros in `lib/src/portable/` for platform compatibility

## Build Configuration

### Makefile (C Library)
```makefile
CFLAGS += -std=c11 -fPIC -fvisibility=hidden
# OS-specific: SOEXT varies (.dylib, .dll, .so)
make test  # Runs `cargo xtask test`
```

### Cargo Profiles
- `release` - production binaries (LTO enabled)
- `release-dev` - faster iteration (no LTO, debug info)
- `optimize` - maximum size/performance
- Workspace uses shared dependency versions in `[workspace.dependencies]`

## Testing & Debugging

**Corpus test format** (in grammar's `test/corpus/`):
```
==================
Test name
==================

source code here
---

(expected_tree [0, 0] - [1, 0])
```

**Debug parsing:**
```bash
tree-sitter parse --debug <file>          # Print parse events
tree-sitter parse --debug-graph <file>    # Generate log.html
tree-sitter test --include <pattern>      # Filter by test name
tree-sitter test --update                 # Regenerate expected trees
```

**Wasm testing:**
```bash
cargo xtask test-wasm  # Compile to Wasm, run tests
```

## External Scanners
Grammars can use custom C tokenizers (`src/scanner.c`) for complex tokens:
- Indentation tracking (Python)
- Heredocs (Bash)
- String interpolation

The `tree-sitter init` command generates binding templates for multiple languages (Rust, JS, Go, Swift, Python).

## Common Files to Know

- [crates/cli/src/main.rs](crates/cli/src/main.rs#L1) - CLI argument parsing and command dispatch
- [crates/generate/src/generate.rs](crates/generate/src/generate.rs#L252) - entry point for `tree-sitter generate`
- [lib/binding_rust/lib.rs](lib/binding_rust/lib.rs#L62) - public Rust API (Parser, Language, Tree structures)
- [docs/src/6-contributing.md](docs/src/6-contributing.md) - development setup guide
- [docs/src/5-implementation.md](docs/src/5-implementation.md#L16) - architecture deep-dive

## Development Tips

1. **Incremental testing** - modify a single grammar, then `tree-sitter test --update` to capture new behavior
2. **Conflict resolution** - run `tree-sitter generate --json-summary` to diagnose ambiguities
3. **Performance** - use `cargo xtask benchmark --language=<name>` for parser speed tests
4. **Cross-language** - tree-sitter-cli detects parser language by file extension; use `--lang-name` flag for custom paths
5. **WASI/Wasm** - set `TREE_SITTER_WASI_SDK_PATH` environment variable to compile to Wasm
