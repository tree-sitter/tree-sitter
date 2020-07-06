# Fuzzing tree-sitter

The tree-sitter fuzzing support requires 1) the `libFuzzer` runtime library and 2) a recent version of clang

## libFuzzer

The main fuzzing logic is implemented by `libFuzzer` which is part of the compiler-rt project but is not shipped by distros. `libFuzzer` will need to be built from source, e.g.:

```
cd ~/src
git clone https://github.com/llvm-mirror/compiler-rt
cd compiler-rt/lib/fuzzer
./build.sh
```

## clang

Using libFuzzer requires at least version 7 of `clang` and may _not_ work with your system-installed version. If your system-installed version is too old, the easiest way to get started is to use the version provided by the Chromium team. Instructions are available at [libFuzzer.info](http://libfuzzer.info).

The fuzzers can then be built with:
```
export CLANG_DIR=$HOME/src/third_party/llvm-build/Release+Asserts/bin
CC="$CLANG_DIR/clang" CXX="$CLANG_DIR/clang++" LINK="$CLANG_DIR/clang++" \
  LIB_FUZZER_PATH=$HOME/src/compiler-rt/lib/fuzzer/libFuzzer.a \
  ./script/build-fuzzers
```

This will generate a separate fuzzer for each grammar defined in `test/fixtures/grammars` and will be instrumented with [AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html) and [UndefinedBehaviorSanitizer](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html). Individual fuzzers can be built with, for example, `./script/build-fuzzers python ruby`.

The `run-fuzzer` script handles running an individual fuzzer with a sensible default set of arguments:
```
./script/run-fuzzer <grammar-name> (halt|recover) <extra libFuzzer arguments...>
```

which will log information to stdout. Failing testcases and a fuzz corpus will be saved to `fuzz-results/<grammar-name>`. The most important extra `libFuzzer` options are `-jobs` and `-workers` which allow parallel fuzzing. This is can done with, e.g.:
```
./script/run-fuzzer <grammer-name> halt -jobs=32 -workers=32
```

The testcase can be used to reproduce the crash by running:
```
./script/reproduce <grammar-name> (halt|recover) <path-to-testcase>
```
