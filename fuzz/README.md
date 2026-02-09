# Fuzz Testing for tree-sitter

This directory contains fuzz targets for tree-sitter's core parsing engine,
designed for use with [libFuzzer](https://llvm.org/docs/LibFuzzer.html)
and [OSS-Fuzz](https://github.com/google/oss-fuzz).

## Fuzz targets

| Target | Description |
|--------|-------------|
| `fuzz_parser` | Parses arbitrary input with multiple grammars, walks the resulting syntax tree, and tests incremental re-parsing |
| `fuzz_query` | Compiles fuzz-generated S-expression query patterns and executes them against parsed syntax trees |

## Building locally

```bash
# 1. Build tree-sitter from the repository root
make -C ..

# 2. Build fuzz targets (requires clang with libFuzzer support)
make

# 3. Run a fuzzer
./fuzz_parser corpus/
```

### With grammar libraries (recommended)

For better coverage, link grammar libraries so the fuzzer can exercise
real language parsing:

```bash
# Build grammar libraries (example with tree-sitter-json)
git clone https://github.com/tree-sitter/tree-sitter-json /tmp/ts-json
cd /tmp/ts-json && cc -c -I../lib/include src/parser.c -o parser.o && ar rcs libtree-sitter-json.a parser.o

# Build fuzz targets with grammar support
make JSON_LIB=/tmp/ts-json/libtree-sitter-json.a
```

## OSS-Fuzz integration

These targets are continuously fuzzed via Google's OSS-Fuzz infrastructure.
The integration configuration lives in the
[oss-fuzz repository](https://github.com/google/oss-fuzz/tree/master/projects/tree-sitter).
