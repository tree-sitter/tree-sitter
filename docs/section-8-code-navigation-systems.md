---
title: Code Navigation Systems
permalink: code-navigation-systems
---

# Code Navigation Systems

Tree-sitter can be used in conjunction with its [tree query language](https://tree-sitter.github.io/tree-sitter/using-parsers#pattern-matching-with-queries) as a part of code navigation systems. An example of such a system can be seen in the `tree-sitter tag` command, which emits a textual dump of the interesting syntactic nodes in its file argument. This document exists to provide guidelines on the design and use of tree-sitter concepts to implement such systems.

## Tagging and captures

*Tagging* is the act of identifying the entities that can be named in a program. We use Tree-sitter queries to find those entities. Having found them, you use a syntax capture to label the entity and its name.

The essence of a given tag lies in two pieces of data: the _kind_ of entity that is matched (usually a definition or a reference) and the _role_ of that entity, which describes how the entity is used (i.e. whether it's a class definition, function call, variable reference, and so on). Our convention is to use a syntax capture following the `@role.kind` capture name format, and another inner capture, always called `@name`, that pulls out the name of a given identifier.

The below table describes a standard vocabulary for kinds and roles during the tagging process. User applications may extend (or only recognize a subset of) these capture names, but it is desirable to standardize on the names below when supported by a given system or language. Language communities that write tagging rules using these names can work out-of-the-box with a steadily increasing set of analysis tools

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

Documentation forthcoming.
