---
title: Syntax Highlighting
permalink: syntax-highlighting
---

# Syntax Highlighting

Syntax highlighting is a very common feature in applications that deal with code. Tree-sitter has built-in support for syntax highlighting, via the [`tree-sitter-highlight`](https://github.com/tree-sitter/tree-sitter/tree/master/highlight) library. This system is currently used on GitHub.com for highlighting code written in several langauges.

**Note - If you are working on syntax highlighting in the [Atom](https://atom.io/) text editor, you should consult [this page](https://flight-manual.atom.io/hacking-atom/sections/creating-a-grammar/) in the Atom Flight Manual. Atom currently uses a different syntax highlighting system that is also based on Tree-sitter, but is older than the one described in this document.**
