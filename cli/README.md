Tree-sitter CLI
===============

[![crates.io][crates-badge]][crates-package] [![npmjs.com][npmjs-badge]][npmjs-package]

[crates-package]: https://crates.io/crates/tree-sitter-cli
[npmjs-package]: https://www.npmjs.org/package/tree-sitter-cli
[crates-badge]: https://img.shields.io/crates/v/tree-sitter-cli.svg?color=%23B48723
[npmjs-badge]: https://img.shields.io/npm/v/tree-sitter-cli.svg?color=%23BF4A4A

The Tree-sitter CLI allows you to develop, test, and use Tree-sitter grammars from the command line. It works on MacOS, Linux, and Windows.

### Installation

You can install the `tree-sitter-cli` with `cargo`:

```sh
cargo install tree-sitter-cli
```

or with `npm`:

```sh
npm install tree-sitter-cli
```

You can also download a pre-built binary for your platform from [the releases page](https://github.com/tree-sitter/tree-sitter/releases/latest).

### Dependencies

The `tree-sitter` binary itself has no dependencies, but specific commands have dependencies that must be present at runtime:

* To generate a parser from a grammar, you must have [`node`](https://nodejs.org) on your PATH.
* To run and test parsers, you must have a C and C++ compiler on your system.

### Commands

* `generate` - The `tree-sitter generate` command will generate a Tree-sitter parser based on the grammar in the current working directory. See [the documentation](https://tree-sitter.github.io/tree-sitter/creating-parsers) for more information.

* `test` - The `tree-sitter test` command will run the unit tests for the Tree-sitter parser in the current working directory. See [the documentation](https://tree-sitter.github.io/tree-sitter/creating-parsers) for more information.

* `parse` - The `tree-sitter parse` command will parse a file (or list of files) using Tree-sitter parsers.
