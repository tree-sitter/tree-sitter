---
title: Code Navigation Systems
permalink: code-navigation-systems
---

# Code Navigation Systems

Tree-sitter can be used in conjunction with its [tree query language](https://tree-sitter.github.io/tree-sitter/using-parsers#pattern-matching-with-queries) as a part of code navigation systems. An example of such a system can be seen in the `tree-sitter tag` command, which emits a textual dump of the interesting syntactic nodes in its file argument. This document exists to provide guidelines on the design and use of tree-sitter concepts to implement such systems.

## Tagging and captures

Code navigation systems using Tree-sitter need to use queries and captures to categorize and label different syntactic nodes, such as functions, built-ins, operators, and variables. A reverse-DNS-style notation is recommendedfor these captures, and provide guidelines below for naming captures of a given syntax node. User applications may extend (or only recognize a subset of) these capture names, but it is desirable to standardize on the names below when supported by a given system or language.

| Category                 | Tag                         |
|--------------------------|-----------------------------|
| Class definitions        | `@definition.class`         |
| Function definitions     | `@definition.function`      |
| Interface definitions    | `@definition.interface`     |
| Method definitions       | `@definition.method`        |
| Module definitions       | `@definition.module`        |
| Function/method calls    | `@reference.call`           |
| Class reference          | `@reference.class`          |
| Interface implementation | `@reference.implementation` |

To communicate the associated identifier inside one of these syntactic classes, capture the identifier within as `@name`.

## `tree-sitter graph`

Coming soon!
