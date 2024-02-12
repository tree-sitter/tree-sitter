---
title: Contributing
permalink: contributing
---

# Contributing

## Code of Conduct

Contributors to Tree-sitter should abide by the [Contributor Covenant](https://www.contributor-covenant.org/version/1/4/code-of-conduct).

## Developing Tree-sitter

### Prerequisites

To make changes to Tree-sitter, you should have:

1. A C compiler, for compiling the core library and the generated parsers.
2. A [Rust toolchain](https://rustup.rs/), for compiling the Rust bindings, the highlighting library, and the CLI.
3. Node.js and NPM, for generating parsers from `grammar.js` files.
4. Either [Emscripten](https://emscripten.org/), [Docker](https://www.docker.com/), or [podman](https://podman.io/) for compiling the library to WASM.

### Building

Clone the repository:

```sh
git clone https://github.com/tree-sitter/tree-sitter
cd tree-sitter
```

Optionally, build the WASM library. If you skip this step, then the `tree-sitter playground` command will require an internet connection. If you have emscripten installed, this will use your `emcc` compiler. Otherwise, it will use Docker or Podman:

```sh
./script/build-wasm
```

Build the Rust libraries and the CLI:

```sh
cargo build --release
```

This will create the `tree-sitter` CLI executable in the `target/release` folder.

### Testing

Before you can run the tests, you need to clone some grammars that are used for testing:

```sh
script/fetch-fixtures
```

To test any changes you've made to the CLI, you can regenerate these parsers using your current CLI code:

```sh
script/generate-fixtures
```

Then you can run the tests:

```sh
script/test
```

Similarly, to test the WASM binding, you need to compile these parsers to WASM:

```sh
script/generate-fixtures-wasm
script/test-wasm
```

### Debugging

The test script has a number of useful flags. You can list them all by running `script/test -h`. Here are some of the main flags:

If you want to run a specific unit test, pass its name (or part of its name) as an argument:

```sh
script/test test_does_something
```

You can run the tests under the debugger (either `lldb` or `gdb`) using the `-g` flag:

```sh
script/test test_does_something -g
```

Part of the Tree-sitter test suite involves parsing the _corpus_ tests for several different languages and performing randomized edits to each example in the corpus. If you just want to run the tests for a particular _language_, you can pass the `-l` flag. And if you want to run a particular _example_ from the corpus, you can pass the `-e` flag:

```sh
script/test -l javascript -e Arrays
```

## Published Packages

The main [`tree-sitter/tree-sitter`](https://github.com/tree-sitter/tree-sitter) repository contains the source code for several packages that are published to package registries for different languages:

* Rust crates on [crates.io](https://crates.io):
  * [`tree-sitter`](https://crates.io/crates/tree-sitter) - A Rust binding to the core library
  * [`tree-sitter-highlight`](https://crates.io/crates/tree-sitter-highlight) - The syntax-highlighting library
  * [`tree-sitter-cli`](https://crates.io/crates/tree-sitter-cli) - The command-line tool
* JavaScript modules on [npmjs.com](https://npmjs.com):
  * [`web-tree-sitter`](https://www.npmjs.com/package/web-tree-sitter) - A WASM-based JavaScript binding to the core library
  * [`tree-sitter-cli`](https://www.npmjs.com/package/tree-sitter-cli) - The command-line tool

There are also several other dependent repositories that contain other published packages:

* [`tree-sitter/node-tree-sitter`](https://github.com/tree-sitter/node-tree-sitter) - Node.js bindings to the core library, published as [`tree-sitter`](https://www.npmjs.com/package/tree-sitter) on npmjs.com
* [`tree-sitter/py-tree-sitter`](https://github.com/tree-sitter/py-tree-sitter) - Python bindings to the core library, published as [`tree-sitter`](https://pypi.org/project/tree-sitter) on [PyPI.org](https://pypi.org).

## Publishing New Releases

Publishing a new release of the CLI requires these steps:

1. Commit and push all outstanding changes and verify that CI passes:

   ```sh
   git commit -m "Fix things"
   git push
   ```

2. Create a new tag:

   ```sh
   script/version patch
   ```

   This will determine the current version, increment the _patch_ version number, and update the `Cargo.toml` and `package.json` files for the Rust and Node CLI packages. It will then create a commit and a tag for the new version. For more information about the arguments that are allowed, see the documentation for the [`npm version`](https://docs.npmjs.com/cli/version) command.

3. Push the commit and the tag:

   ```sh
   git push
   git push --tags
   ```

4. Wait for CI to pass. Because of the git tag, the CI jobs will publish artifacts to [a GitHub release](https://github.com/tree-sitter/tree-sitter/releases). The npm module of `tree-sitter-cli` works by downloading the appropriate binary from the corresponding GitHub release during installation. So it's best not to publish the npm package until the binaries are uploaded.

5. Publish the npm package:

   ```sh
   cd cli/npm
   npm publish
   ```
