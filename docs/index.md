---
title: Introduction
---

# Introduction

Tree-sitter is a parser generator tool and an incremental parsing library. It can build a concrete syntax tree for a source file and efficiently update the syntax tree as the source file is edited. Tree-sitter aims to be:

* **General** enough to parse any programming language
* **Fast** enough to parse on every keystroke in a text editor
* **Robust** enough to provide useful results even in the presence of syntax errors
* **Dependency-free** so that the runtime library (which is written in pure C) can be embedded in any application

### Language Bindings

There are currently bindings that allow Tree-sitter to be used from the following languages:

* [Haskell](https://github.com/tree-sitter/haskell-tree-sitter)
* [JavaScript (Node.js)](https://github.com/tree-sitter/node-tree-sitter)
* [JavaScript (Wasm)](https://github.com/tree-sitter/tree-sitter/tree/master/lib/binding_web)
* [Lua](https://github.com/euclidianAce/ltreesitter)
* [OCaml](https://github.com/returntocorp/ocaml-tree-sitter-core)
* [Python](https://github.com/tree-sitter/py-tree-sitter)
* [Ruby](https://github.com/tree-sitter/ruby-tree-sitter)
* [Rust](https://github.com/tree-sitter/tree-sitter/tree/master/lib/binding_rust)
* [Swift](https://github.com/ChimeHQ/SwiftTreeSitter)
* [Kotlin](https://github.com/oxisto/kotlintree)
* [Java](https://github.com/serenadeai/java-tree-sitter)

### Available Parsers

Parsers for these languages are fairly complete:

* [Bash](https://github.com/tree-sitter/tree-sitter-bash)
* [C](https://github.com/tree-sitter/tree-sitter-c)
* [C#](https://github.com/tree-sitter/tree-sitter-c-sharp)
* [C++](https://github.com/tree-sitter/tree-sitter-cpp)
* [Common Lisp](https://github.com/theHamsta/tree-sitter-commonlisp)
* [CSS](https://github.com/tree-sitter/tree-sitter-css)
* [CUDA](https://github.com/theHamsta/tree-sitter-cuda)
* [DOT](https://github.com/rydesun/tree-sitter-dot)
* [Elm](https://github.com/elm-tooling/tree-sitter-elm)
* [Emacs Lisp](https://github.com/Wilfred/tree-sitter-elisp)
* [Eno](https://github.com/eno-lang/tree-sitter-eno)
* [ERB / EJS](https://github.com/tree-sitter/tree-sitter-embedded-template)
* [Fennel](https://github.com/travonted/tree-sitter-fennel)
* [GLSL (OpenGL Shading Language)](https://github.com/theHamsta/tree-sitter-glsl)
* [Go](https://github.com/tree-sitter/tree-sitter-go)
* [HCL](https://github.com/MichaHoffmann/tree-sitter-hcl)
* [HTML](https://github.com/tree-sitter/tree-sitter-html)
* [Java](https://github.com/tree-sitter/tree-sitter-java)
* [JavaScript](https://github.com/tree-sitter/tree-sitter-javascript)
* [Lua](https://github.com/Azganoth/tree-sitter-lua)
* [Make](https://github.com/alemuller/tree-sitter-make)
* [Markdown](https://github.com/ikatyang/tree-sitter-markdown)
* [OCaml](https://github.com/tree-sitter/tree-sitter-ocaml)
* [PHP](https://github.com/tree-sitter/tree-sitter-php)
* [Python](https://github.com/tree-sitter/tree-sitter-python)
* [Ruby](https://github.com/tree-sitter/tree-sitter-ruby)
* [Rust](https://github.com/tree-sitter/tree-sitter-rust)
* [R](https://github.com/r-lib/tree-sitter-r)
* [S-expressions](https://github.com/AbstractMachinesLab/tree-sitter-sexp)
* [SPARQL](https://github.com/BonaBeavis/tree-sitter-sparql)
* [SystemRDL](https://github.com/SystemRDL/tree-sitter-systemrdl)
* [Svelte](https://github.com/Himujjal/tree-sitter-svelte)
* [TOML](https://github.com/ikatyang/tree-sitter-toml)
* [Turtle](https://github.com/BonaBeavis/tree-sitter-turtle)
* [TypeScript](https://github.com/tree-sitter/tree-sitter-typescript)
* [Verilog](https://github.com/tree-sitter/tree-sitter-verilog)
* [VHDL](https://github.com/alemuller/tree-sitter-vhdl)
* [Vue](https://github.com/ikatyang/tree-sitter-vue)
* [YAML](https://github.com/ikatyang/tree-sitter-yaml)
* [WASM](https://github.com/wasm-lsp/tree-sitter-wasm)
* [WGSL WebGPU Shading Language](https://github.com/mehmetoguzderin/tree-sitter-wgsl)

Parsers for these languages are in development:

* [Agda](https://github.com/tree-sitter/tree-sitter-agda)
* [Elixir](https://github.com/elixir-lang/tree-sitter-elixir)
* [Erlang](https://github.com/AbstractMachinesLab/tree-sitter-erlang/)
* [Dockerfile](https://github.com/camdencheek/tree-sitter-dockerfile)
* [Go mod](https://github.com/camdencheek/tree-sitter-go-mod)
* [Hack](https://github.com/slackhq/tree-sitter-hack)
* [Haskell](https://github.com/tree-sitter/tree-sitter-haskell)
* [Julia](https://github.com/tree-sitter/tree-sitter-julia)
* [Kotlin](https://github.com/fwcd/tree-sitter-kotlin)
* [Nix](https://github.com/cstrahan/tree-sitter-nix)
* [Objective-C](https://github.com/jiyee/tree-sitter-objc)
* [Perl](https://github.com/ganezdragon/tree-sitter-perl)
* [Protocol Buffers](https://github.com/mitchellh/tree-sitter-proto)
* [Scala](https://github.com/tree-sitter/tree-sitter-scala)
* [Sourcepawn](https://github.com/nilshelmig/tree-sitter-sourcepawn)
* [Swift](https://github.com/tree-sitter/tree-sitter-swift)
* [SQL](https://github.com/m-novikov/tree-sitter-sql)


### Talks on Tree-sitter

* [Strange Loop 2018](https://www.thestrangeloop.com/2018/tree-sitter---a-new-parsing-system-for-programming-tools.html)
* [FOSDEM 2018](https://www.youtube.com/watch?v=0CGzC_iss-8)
* [GitHub Universe 2017](https://www.youtube.com/watch?v=a1rC79DHpmY)

### Underlying Research

The design of Tree-sitter was greatly influenced by the following research papers:

- [Practical Algorithms for Incremental Software Development Environments](https://www2.eecs.berkeley.edu/Pubs/TechRpts/1997/CSD-97-946.pdf)
- [Context Aware Scanning for Parsing Extensible Languages](https://www-users.cse.umn.edu/~evw/pubs/vanwyk07gpce/vanwyk07gpce.pdf)
- [Efficient and Flexible Incremental Parsing](http://harmonia.cs.berkeley.edu/papers/twagner-parsing.pdf)
- [Incremental Analysis of Real Programming Languages](http://harmonia.cs.berkeley.edu/papers/twagner-glr.pdf)
- [Error Detection and Recovery in LR Parsers](http://what-when-how.com/compiler-writing/bottom-up-parsing-compiler-writing-part-13)
- [Error Recovery for LR Parsers](https://apps.dtic.mil/sti/pdfs/ADA043470.pdf)
