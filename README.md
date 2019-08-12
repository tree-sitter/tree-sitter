# tree-sitter

[![Build Status](https://dev.azure.com/onivim/oni2/_apis/build/status/onivim.esy-tree-sitter?branchName=master)](https://dev.azure.com/onivim/oni2/_build/latest?definitionId=7&branchName=master)

Tree-sitter is a parser generator tool and an incremental parsing library. It can build a concrete syntax tree for a source file and efficiently update the syntax tree as the source file is edited. Tree-sitter aims to be:

* **General** enough to parse any programming language
* **Fast** enough to parse on every keystroke in a text editor
* **Robust** enough to provide useful results even in the presence of syntax errors
* **Dependency-free** so that the runtime library (which is written in pure C) can be embedded in any application

[Documentation](https://tree-sitter.github.io/tree-sitter/)
