# tree-sitter

[![CICD badge]][CICD]
[![DOI](https://zenodo.org/badge/14164618.svg)](https://zenodo.org/badge/latestdoi/14164618)

[CICD badge]: https://github.com/tree-sitter/tree-sitter/actions/workflows/CICD.yml/badge.svg
[CICD]: https://github.com/tree-sitter/tree-sitter/actions/workflows/CICD.yml

Tree-sitter is a parser generator tool and an incremental parsing library. It can build a concrete syntax tree for a source file and efficiently update the syntax tree as the source file is edited. Tree-sitter aims to be:

- **General** enough to parse any programming language
- **Fast** enough to parse on every keystroke in a text editor
- **Robust** enough to provide useful results even in the presence of syntax errors
- **Dependency-free** so that the runtime library (which is written in pure C) can be embedded in any application

## Editors

The following editors are making use of tree-sitter for syntax highlighting and other features:

- [Neovim](https://github.com/neovim/neovim): a Vim-fork focused on extensibility and usability.
- [helix](https://github.com/helix-editor/helix): a post-modern modal text editor.
- [emacs-tree-sitter](https://github.com/emacs-tree-sitter/elisp-tree-sitter): bindings for Emacs.
- [lapce](https://github.com/lapce/lapce): an IDE written in pure Rust leveraging OpenGL.

## Links

- [Documentation](https://tree-sitter.github.io)
- [Rust binding](lib/binding_rust/README.md)
- [WASM binding](lib/binding_web/README.md)
- [Command-line interface](cli/README.md)
